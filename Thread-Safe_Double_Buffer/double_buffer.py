import time
import threading
from typing import Optional, NamedTuple


class SensorData(NamedTuple):
    id: int
    temperature: float

class Snapshot:
    def __init__(self):
        self.value: Optional[SensorData] = None
        self.ts: float = 0.0
        self.valid: bool = False

class DoubleBuffer:
    def __init__(self):
        self.buffers = [Snapshot(), Snapshot()]
        self.read_index: int = 0
        self.write_index: int = 1

    def publish(self, value: SensorData) -> None:
        back = self.write_index

        self.buffers[back].value = value
        self.buffers[back].ts = time.steady_clock() if hasattr(time, 'steady_clock') else time.monotonic()
        self.buffers[back].valid = True

        front = self.read_index
        self.read_index = back
        self.write_index = front

    def latest_if_fresh(self, max_age_ms: float) -> Optional[SensorData]:
        front = self.read_index
        s = self.buffers[front]

        if not s.valid:
            return None

        now = time.steady_clock() if hasattr(time, 'steady_clock') else time.monotonic()
        age_ms = (now - s.ts) * 1000.0

        if age_ms > max_age_ms:
            return None

        return s.value

def producer_worker(db: DoubleBuffer, context: dict) -> None:
    for i in range(1, 6):
        data = SensorData(id=i, temperature=20.0 + i)
        db.publish(data)
        time.sleep(0.1)

    context["done"] = True

def consumer_worker(db: DoubleBuffer, context: dict) -> None:
    keep_running = True
    
    while keep_running:
        producer_finished = context["done"]

        data = db.latest_if_fresh(max_age_ms=300)
        if data is not None:
            print(f"id={data.id}, temp={data.temperature:.1f}")
        else:
            print("no fresh data")

        if producer_finished:
            keep_running = False
        else:
            time.sleep(0.05)

def main() -> None:
    db = DoubleBuffer()

    context = {"done": False}

    producer = threading.Thread(target=producer_worker, args=(db, context))
    consumer = threading.Thread(target=consumer_worker, args=(db, context))

    producer.start()
    consumer.start()

    producer.join()
    consumer.join()

if __name__ == "__main__":
    main()
