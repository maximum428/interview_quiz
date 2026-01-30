/*** Example 1: Write to a file, then read it (using fprintf / fgets) ***/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE *fp;
    char buffer[100];
    
    fp = fopen("example.txt", "w");  // write mode
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return 1;
    }
    fprintf(fp, "Hello, File I/O in C!\n");
    fprintf(fp, "This is a second line.\n");
    fclose(fp);
    
    fp = fopen("example.txt", "r");  // read mode
    if (fp == NULL) {
        perror("Failed to open file for reading");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);
    return 0;
}
/*************************************************************************/
/*** Example 2: Binary read/write (important for embedded / systems) ***/
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fp;
    int data_out = 1234;
    int data_in = 0;
    
    fp = fopen("data.bin", "wb");
    fwrite(&data_out, sizeof(int), 1, fp);
    fclose(fp);
    
    fp = fopen("data.bin", "rb");
    fread(&data_in, sizeof(int), 1, fp);
    fclose(fp);
    
    printf("Read value : %d\n", data_in);
    return 0;
}
/*************************************************************************/
/*** Example 3: Write & Read a Text File (C++ fstream) ***/
#include <iostream>
#include <fstream>
#include <string>

int main(int argc char** argv) {
    std::ofstream out("example.txt");
    if (!out.is_open()) {
        std::cerr << "Failed to open file for writing\n";
        return 1;
    }
    
    out << "Hello, C++ FILE I/O\n";
    out << "This is a second line.\n";
    out.close();
    
    std::ifstream in("example.txt");
    if (!in.is_open()) {
        std::cerr << "Failed to open file for reading.\n";
        return 1;
    }
    
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << std::endl;
    }
    in.close();
    return 0;
}

/*************************************************************************/
/*** Example 4: Read & Write Using fstream (Read + Write) ***/
#include <iostream>
#include <fsteam>

int main() {
    std::fstream file("data.txt", std::ios::in | std::ios::out | std::ios::trunc);
    
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    
    file << "123\n";
    file << "456\n";
    
    file.seekg(0);   // move read pointer to begining
    
    int x;
    while (file >> x) {
        std::cout << x << std::endl;
    }
    file.close();
    return 0;
}
/*************************************************************************/
/*** Example 5: Binary Read/Write (Important for Embedded / OTA) ***/
#include <iostream>
#include <fstream>

struct Data {
    int id;
    float value;
};

int main() {
    Data outData{1, 3.14f};
    Data inData{};
    
    std::ofstream out("data.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(&outData), sizeof(Data));
    out.close();
    
    std::ifstream in("data.bin", std::ios::binary);
    in.read(reinterpret_cast<char*>(&inData), sizeof(Data));
    in.close();
    
    std::cout << inData.id << " " << inData.value << endl;
    return 0;
}

/***********************************************************************/
/*** Embedded-safe C/C++ Example (POSIX)
  Write → Flush → Rename (Atomic Commit)

1️⃣ Write new data to a temporary file
2️⃣ Flush data to storage (fsync)
3️⃣ Atomically rename temp file over old file

👉 POSIX guarantees rename() is atomic ***/

#inlcude <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

bool safe_write(const char* path, const char* data, size_t len) {
    char tmp[256];
    snprintf(tmp, sizeof(tmp, "%s.tmp", path));
    
    // 1. Create temp file
    int fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return false;
    
    // 2. Write data
    ssize_t written = write(fd, data, len);
    if (written != (ssize_t)len) {
        close(fd);
        return false;
    }
    
    // 3. Flush data to disk
    fsync(fd);
    close(fd);
    
    // 4 Atomic replace
    if (rename(tmp, path) != 0) {
        unlink(tmp);
        return false;
    }
    return true;
}

/***********************************************************************/
/*** Flash / EEPROM power-safe write 
Why Flash / EEPROM is special

Unlike filesystems:

❌ No atomic write

❌ Cannot overwrite bits from 0 → 1

❌ Erase happens in blocks / sectors

❌ Power loss = half-written data

So we must design our own atomicity.

Core principles (must know)

1️⃣ Write-once direction
Flash bits: 1 → 0 only (erase resets to 1)

2️⃣ Never overwrite in place

3️⃣ Commit last
Write data → verify → set valid flag at the very end

Pattern 1️⃣: Valid Flag (Most Common)
Memory layout
| DATA ............ | CRC | VALID |
|  64 bytes         | 4B  | 1B    |


VALID = 0xFF → invalid (erased state)

VALID = 0x00 → valid (written last)  ***/

#define VALID_FLAG      0x00
#define INVALID_FLAG    0xFF

struct Record {
    uint8_t data[64];
    uint32_t crc;
    uint8_t valid;
};

void flash_write_safe(struct Record* flash, struct Record* src) {
    //  1. Erase sector beforehand
    
    // 2. Write data
    memcpy(flash->data, src->data, sizeof(src->data));
    
    // 3. Write CRC
    flash->crc = calc_crc(src->data, sizeof(src->data));
    
    // 4. Commit LAST
    flash->valid = VALID_FLAG;
}

/***********************************************************************/
/*** Using EEPROM on STM32
#include <stdint.h>
#include <stdbool.h>
#include <eeprom.h> // MCU-specific EEPROM

typedef struct {
    uint32_t counter;
    uint16_t temperature;
} critical_data_t;

volatile critical_data_t g_data;

// Simulate EEPROM write function
bool eeprom_write(volatile void *addr, const void *data, size_t len);

void save_critical_data(void) {
    // This must complete < 1ms
    eeprom_write((void*)0x08080000, &g_data, sizeof(g_data));
}

// Example: Power fail ISR
void POWER_FAIL_IRQHandler(void) {
    save_critical_data();  // flush data immediately
}

int main(void) {
    while (1) {
        g_data.counter++;
        g_data.temperature = 25;
        
        // Normal processing
    }
}

/***********************************************************************/
/***  Example:  1. Use non-volatile FRAM. 2. Use double-buffering 
                3. Detect power failure.  4. Make writes atomic ***/

#include <cstring>
#include <cstdint>
#include <iostream> 

// Simulated FRAM storage
uint8_t FRAM[2][64];  // double buffer
bool power_lost = false;

// Critical data struct
struct CriticalData {
    uint32_t counter;
    uint16_t temperature;
    uint16_t checksum;  // simple checksum for integrity
};

// Compute simple checksum
uint16_t compute_checksum(const CriticalData &data) {
    return data.counter ^ data.temperature;
}

// Write data to FRAM double buffer atomically
void write_fram_atomic(int buf_index, const CriticalData &data) {
    CriticalData tmp = data;
    tmp.checksum = compute_checksum(data);
    std::memcpy(FRAM[buf_index], &tmp, sizeof(tmp));
}

// Read data from FRAM and validate checksum
bool read_fram(int buf_index, CriticalData &data) {
    std::memcpy(&data, FRAM[buf_index], sizeof(data));
    return data.checksum == compute_checksum(data);
}

// Presistent storage manager
class PersistentManager {
    int active_buf = 0;  // toggle between 0 and 1
public:
    CriticalData current_data;
    
    PersistentManager() {
        // On boot, restore latest valid data
        CriticalData d0, d1;
        bool valid0 = read_fram(0, d0);
        bool valid1 = read_fram(1, d1);
        
        if (valid1 && (!valid0 || d1.counter >= d0.counter)) {
            current_data = d1;
            active_buf = 1;
        } else if (valid0) {
            current_data = d0;
            active_buf = 0;
        } else {
            current_data = {0, 0, 0}; // first boot
        }
    }
    
    // Flush data to FRAM
    void flush() {
        active_buf = 1 - active_buf; // toggle buffer
        write_fram_atomic(active_buf, current_data);
    }
    
    void increment_counter() {
        current_data.counter++;
    }
    
    void set_temperature(uint16_t temp) {
        current_data.temperature = temp;
    }
};

// Simulated power fial interrupt
void POWER_FAIL_ISR(PersistentManager &pm) {
    pm.flush();  // flush immediately
}

int main() {
    PersistentManager pm;
    
    // Normal operation
    for (int i = 0; i < 5; i++) {
        pm.increment_counter();
        pm.set_temperature(25 +i);
        
        // Simulate power fail at iteration 3
        if (i == 3) {
            std::cout << "Power fail detected! Flushing data...\n";
            POWER_FAIL_ISR(pm);
        }
    }
    
    // Simulate reboot
    PersistentManager pm_reboot;
    std::cout << "Recovered counter: " << pm_reboot.current_data.counter << "\n";
    std::cout << "Recovered temperature: " << pm_reboot.current_data.temperature << "\n";
    
    return 0;
}

/***********************************************************************/
/***   Ring buffer  ***/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define RING_BUFFER_SIZE 8 // must be power of 2 for optimization
// optimization
#define RING_BUFFER_MASK (RING_BUFFER_SIZE - 1)

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
} ring_buffer_t;

void rb_init(ring_buffer_t *rb) {
    rb->head = rb->tail = 0;
}

bool rb_is_empty(ring_buffer_t *rb) {
    return rb->head == rb->tail;
}

bool rb_is_full(ring_buffer_t *rb) {
    //return ((rb->head + 1) % RING_BUFFER_SIZE) == rb->tail;
    //optimation 
    return ((rb->head + 1) & RING_BUFFER_MASK) == rb->tail;
}

bool rb_write(ring_buffer_t *rb, uint8_t data) {
    if (rb_is_full(rb)) {
        return false;  // buffer full
    }
    rb->buffer[rb->head] = data;
    //rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
    // optimization
    rb->head = (rb->head + 1) & RING_BUFFER_MASK;
    return true;
}

bool rb_read(ring_buffer_t *rb, uint8_t *data) {
    if (rb_is_empty(rb)) {
        return false;  // buffer empty
    }
    
    *data = rb->buffer[rb->tail];
    //rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
    // optimization
    rb->tail = (rb->tail + 1) & RING_BUFFER_MASK;
    return true;
}

int main(void) {
    ring_buffer_t rb;
    uint8_t value;
    
    rb_init(&rb);
    
    rb_write(&rb, 10);
    rb_write(&rb, 20);
    rb_write(&rb, 30);
    
    while (rb_read(&rb, &value)) {
        printf("%d\n", value);
    }
    
    return 0;
}



