#define _XOPEN_SOURCE 500 

#include <stdio.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> 

// --- Data Structure Definitions ---

typedef struct {
    int id;
    double temperature;
} SensorData;

typedef struct {
    SensorData value;
    struct timespec ts;
    bool valid;
} Snapshot;

typedef struct {
    // Only the index integers are atomic. 
    // They are 4 bytes each, meaning they are natively lock-free on ALL modern CPUs.
    atomic_int read_index;
    atomic_int write_index; 
    Snapshot buffers[2];
} DoubleBuffer;

// --- Helper Time Functions ---

struct timespec get_now(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts;
}

void sleep_ms(long ms) {
    usleep(ms * 1000); 
}

long long get_age_ms(struct timespec now, struct timespec then) {
    long long diff_sec = now.tv_sec - then.tv_sec;
    long long diff_nsec = now.tv_nsec - then.tv_nsec;
    return (diff_sec * 1000LL) + (diff_nsec / 1000000LL);
}

// --- DoubleBuffer Implementations ---

void db_init(DoubleBuffer* db) {
    atomic_init(&db->read_index, 0);
    atomic_init(&db->write_index, 1);
    db->buffers[0].valid = false;
    db->buffers[1].valid = false;
}

void db_publish(DoubleBuffer* db, SensorData value) {
    // Acquire fences guarantee we read the latest state of the buffer indexes safely
    int back = atomic_load_explicit(&db->write_index, memory_order_acquire);

    // Write straight to the back buffer (guaranteed to not be occupied by the consumer)
    db->buffers[back].value = value;
    db->buffers[back].ts = get_now();
    db->buffers[back].valid = true;

    // Swap the indexes atomically to publish our change
    int front = atomic_load_explicit(&db->read_index, memory_order_acquire);
    atomic_store_explicit(&db->read_index, back, memory_order_release);
    atomic_store_explicit(&db->write_index, front, memory_order_release);
}

bool db_latest_if_fresh(const DoubleBuffer* db, long long max_age_ms, SensorData* out_data) {
    int front = atomic_load_explicit(&db->read_index, memory_order_acquire);
    
    // Create a local thread copy of the target slot data safely
    Snapshot s = db->buffers[front];

    if (!s.valid) {
        return false;
    }

    struct timespec now = get_now();
    if (get_age_ms(now, s.ts) > max_age_ms) {
        return false;
    }

    *out_data = s.value;
    return true;
}

// --- Thread Context and Worker Functions ---

typedef struct {
    DoubleBuffer* db;
    _Atomic bool* done;
} ThreadArgs;

void* producer_worker(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    for (int i = 1; i <= 5; i++) {
        SensorData data = { .id = i, .temperature = 20.0 + i };
        db_publish(args->db, data);
        sleep_ms(100);
    }
    
    atomic_store_explicit(args->done, true, memory_order_release);
    return NULL;
}

void* consumer_worker(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    bool keep_running = true;

    while (keep_running) {
        bool producer_finished = atomic_load_explicit(args->done, memory_order_acquire);

        SensorData data;
        if (db_latest_if_fresh(args->db, 300, &data)) {
            printf("id=%d, temp=%.1f\n", data.id, data.temperature);
        } else {
            printf("no fresh data\n");
        }

        if (producer_finished) {
            keep_running = false;
        } else {
            sleep_ms(50);
        }
    }
    return NULL;
}

// --- Main Entry Point ---

int main(void) {
    DoubleBuffer db;
    db_init(&db);

    _Atomic bool done;
    atomic_init(&done, false);

    ThreadArgs args = { .db = &db, .done = &done };

    pthread_t producer, consumer;

    pthread_create(&producer, NULL, producer_worker, &args);
    pthread_create(&consumer, NULL, consumer_worker, &args);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}
