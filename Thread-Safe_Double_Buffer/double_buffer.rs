use std::sync::atomic::{AtomicBool, AtomicUsize, Ordering};
use std::sync::Arc;
use std::thread;
use std::time::{Duration, Instant};

#[derive(Debug, Clone, Copy)]
struct SensorData {
    id: i32,
    temperature: f64,
}

#[derive(Clone, Copy)]
struct Snapshot {
    value: Option<SensorData>,
    ts: Instant,
    valid: bool,
}

impl Snapshot {
    fn new() -> Self {
        Self {
            value: None,
            ts: Instant::now(),
            valid: false,
        }
    }
}

struct DoubleBuffer {
    read_index: AtomicUsize,
    write_index: AtomicUsize,
    buffers: [std::cell::UnsafeCell<Snapshot>; 2],
}

unsafe impl Sync for DoubleBuffer {}
unsafe impl Send for DoubleBuffer {}

impl DoubleBuffer {
    fn new() -> Self {
        Self {
            read_index: AtomicUsize::new(0),
            write_index: AtomicUsize::new(1),
            buffers: [
                std::cell::UnsafeCell::new(Snapshot::new()),
                std::cell::UnsafeCell::new(Snapshot::new()),
            ],
        }
    }

    fn publish(&self, value: SensorData) {
        let back = self.write_index.load(Ordering::Acquire);

        unsafe {
            let slot = &mut *self.buffers[back].get();
            slot.value = Some(value);
            slot.ts = Instant::now();
            slot.valid = true;
        }

        let front = self.read_index.load(Ordering::Acquire);
        self.read_index.store(back, Ordering::Release);
        self.write_index.store(front, Ordering::Release);
    }

    fn latest_if_fresh(&self, max_age: Duration) -> Option<SensorData> {
        let front = self.read_index.load(Ordering::Acquire);

        let s = unsafe { *self.buffers[front].get() };

        if !s.valid {
            return None;
        }

        if s.ts.elapsed() > max_age {
            return None;
        }
        s.value
    }
}

fn main() {
    let db = Arc::new(DoubleBuffer::new());
    let done = Arc::new(AtomicBool::new(false));

    let db_producer = Arc::clone(&db);
    let done_producer = Arc::clone(&done);

    let producer = thread::spawn(move || {
        for i in 1..=5 {
            let data = SensorData {
                id: i,
                temperature: 20.0 + (i as f64),
            };
            db_producer.publish(data);
            thread::sleep(Duration::from_millis(100));
        }
        done_producer.store(true, Ordering::Release);
    });

    let db_consumer = Arc::clone(&db);
    let done_consumer = Arc::clone(&done);

    let consumer = thread::spawn(move || {
        let mut keep_running = true;

        while keep_running {
            let producer_finished = done_consumer.load(Ordering::Acquire);

            if let Some(data) = db_consumer.latest_if_fresh(Duration::from_millis(300)) {
                println!("id={}, temp={:.1}", data.id, data.temperature);
            } else {
                println!("no fresh data");
            }

            if producer_finished {
                keep_running = false;
            } else {
                thread::sleep(Duration::from_millis(50));
            }
        }
    });

    producer.join().unwrap();
    consumer.join().unwrap();
}
