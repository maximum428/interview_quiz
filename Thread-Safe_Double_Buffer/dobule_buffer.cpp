/*
請設計並實作一個 thread-safe 的 Double Buffer 類別，用於支援以下場景：

* 一個 writer thread 持續寫入最新資料
* 多個 reader threads 可以隨時讀取「最新完整資料」
* reader 不能讀到不完整（部分更新）的資料
* 系統應該支援 高頻讀取（low latency read）
* 請避免在 read path 上使用 heavyweight locking（例如全域 mutex）
*/

#include <atomic>
#include <chrono>
#include <iostream>
#include <optional>
#include <string>
#include <thread>

using namespace std;

template<typename T>
class DoubleBuffer {
public:
  struct Snapshot {
    T value{};
    chrono::steady_clock::time_point ts{};
    bool valid = false;
  };

  DoubleBuffer() : read_index_(0) {}

  // Single-writer
  void publish(const T& value) {
    int front = read_index_.load(memory_order_acquire);
    int back = 1 - front;

    buffers_[back].value = value;
    buffers_[back].ts = chrono::steady_clock::now();
    buffers_[back].valid = true;

    read_index_.store(back, memory_order_release);
  }

  optional<T> latest() const {
    int front = read_index_.load(memory_order_acquire);
    const Snapshot& s = buffers_[front];
    if (!s.valid) {
      return nullopt;
    }
    return s.value;
  }

  optional<T> latestIfFresh(chrono::milliseconds max_age) const {
    int front = read_index_.load(memory_order_acquire);
    const Snapshot& s = buffers_[front];

    if (!s.valid) {
      return nullopt;
    }

    auto now = chrono::steady_clock::now();
    if (now - s.ts > max_age) {
      return nullopt;
    }
    return s.value;
  }
private:
  Snapshot buffers_[2];
  atomic<int> read_index_;
};

struct SensorData {
  int id = 0;
  double temerature = 0.0;
};

int main() {
  DoubleBuffer<SensorData> db;
  atomic<bool> done = false;

  thread producer([&] {
    for (int i = 1; i <= 5; i++) {
      db.publish(SensorData{i, 20.0 + i});
      this_thread::sleep_for(chrono::milliseconds(100));
    }
    done = true;
  });

  thread consumer([&] {
    while (!done.load()) {
      auto data = db.latestIfFresh(chrono::milliseconds(300));
      if (data) {
        cout << "id=" << data->id << ", temp=" << data->temerature << endl;
      } else {
        cout << "no fresh data\n";
      }
      this_thread::sleep_for(chrono::milliseconds(50));
    }
  });

  producer.join();
  consumer.join();

  return 0;
}
