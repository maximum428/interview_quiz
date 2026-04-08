/*
Security cameras often have an Ambient Light Sensor (ALS) which measures the amount of light around the camera and triggers a "night mode" 
when the ambient light is too low. You've been given an ALS that reports sensor readings using the following 
struct: 
  struct SensorReading {
    int status; 
    float lux; 
    uint64_t timestamp; // time of reading 
  }; 
To get a sensor reading, call: 
  SensorReading read_next_sample(); 
This function will do one of two things: The amount of light does not change within one second, the sensor returns NO_CHANGE in the status field. 
A total of one second elapses before the function unblocks. The amount of light does change within one second, the sensor returns VALID in the 
status field and populates the lux and timestamp. A variable amount of time elapses before the function unblocks, between 0 and 1 seconds. 
  
NOTE: 
  The first call to read_next_sample will always return a valid value without blocking. Working with blocking functions is hard and not thread-friendly, 
  so we want to wrap the ALS function in a non-blocking, thread-safe way. Tasks Design and implement an API that allows users to read the most recent valid lux value. 
  The API should be non-blocking and thread-safe. Design and implement an API that allows users to read lux values from any time within the last 10 minutes. 
  Your API should be non-blocking and thread-safe. 
  
  Expected Output lux [1] = 3.94383, should be 3.94383 
                  lux [2] = 3.35223, should be 3.35223 
                  lux [3] = 5.5397, should be 5.5397 
                  t: 0, lux: -1 
                  t: 1, lux: 3.94383 
                  t: 2, lux: 3.35223 
                  t: 3, lux: 5.5397 
                  t: 4, lux: -2 
  [execution time limit] 20 seconds (cpp) 
  [memory limit] 2g
  */
/*
這題的核心不是 ALS 本身，而是：

把 blocking 的 read_next_sample() 包成 non-blocking
讓它 thread-safe
同時支援
讀取「最新有效 lux」
查詢「過去 10 分鐘內某個時間點的 lux」

解題思路
1. 用背景執行緒持續讀 sensor

因為 read_next_sample() 會 block，所以不能讓使用者直接呼叫它。

做法：

啟一個 background thread
這個 thread 不斷呼叫 read_next_sample()
一旦拿到 VALID sample，就存進內部資料結構
API 只讀快取資料，不直接碰 blocking function

這樣對外 API 就是 non-blocking

2. 最新值：用一份 latest valid sample

維護：

latest_valid_lux
latest_valid_timestamp
has_latest

查詢最新值時只要加鎖讀這幾個欄位即可，時間複雜度 O(1)。

3. 歷史查詢：保留最近 10 分鐘有效樣本

因為只需要查最近 10 分鐘，所以不需要無限存。

維護：

deque<Sample>，只存 VALID 的資料
每次插入新 sample 時，把超過 10 分鐘的舊資料 prune 掉

查詢某個 timestamp 時：

因為資料按時間遞增，可用 lower_bound / binary search
時間複雜度 O(log n)

設計兩個 non-blocking API：

std::optional<float> getLatestLux() const;
int getLuxAt(uint64_t timestamp, float& out) const;

其中：

getLatestLux()
有值就回傳 lux
沒有就回傳 std::nullopt
getLuxAt(timestamp, out)
回傳狀態碼：
0：找到
-1：比目前最早資料還早
-2：該 timestamp 沒有有效 sample / 比最新資料還晚
*/

#include <atomic>
#include <cstdint>
#include <deque>
#include <mutex>
#include <optional>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

// Assume these are provided by the platform
constexpr int NO_CHANGE = 0;
constexpr int VALID = 1;

struct SensorReading {
    int status;
    float lux;
    uint64_t timestamp; // time of reading
};

// Provided by platform
SensorReading read_next_sample();

class ALSWrapper {
public:
    ALSWrapper() : stop_(false), has_latest_(false) {
        worker_ = std::thread(&ALSWrapper::run, this);
    }

    ~ALSWrapper() {
        stop_.store(true, std::memory_order_release);
        if (worker_.joinable()) {
            worker_.join();
        }
    }

    // Non-blocking, thread-safe
    std::optional<float> getLatestLux() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!has_latest_) return std::nullopt;
        return latest_lux_;
    }

    // Non-blocking, thread-safe
    // Returns:
    //   0  -> found exact timestamp match
    //  -1  -> requested time is older than our retained history / before first known valid sample
    //  -2  -> no valid sample exactly at timestamp, or timestamp is newer than latest known sample
    int getLuxAt(uint64_t timestamp, float& out) const {
        std::lock_guard<std::mutex> lock(mutex_);

        if (history_.empty()) {
            return -1;
        }

        if (timestamp < history_.front().timestamp) {
            return -1;
        }

        if (timestamp > history_.back().timestamp) {
            return -2;
        }

        auto it = std::lower_bound(
            history_.begin(), history_.end(), timestamp,
            [](const Entry& e, uint64_t ts) {
                return e.timestamp < ts;
            }
        );

        if (it != history_.end() && it->timestamp == timestamp) {
            out = it->lux;
            return 0;
        }

        return -2;
    }

private:
    struct Entry {
        uint64_t timestamp;
        float lux;
    };

    static constexpr uint64_t TEN_MINUTES = 10ull * 60ull;

    void run() {
        while (!stop_.load(std::memory_order_acquire)) {
            SensorReading sample = read_next_sample();

            if (sample.status != VALID) {
                continue;
            }

            std::lock_guard<std::mutex> lock(mutex_);

            latest_lux_ = sample.lux;
            latest_timestamp_ = sample.timestamp;
            has_latest_ = true;

            history_.push_back({sample.timestamp, sample.lux});

            // Keep only the last 10 minutes of valid samples
            uint64_t cutoff = (sample.timestamp > TEN_MINUTES)
                ? (sample.timestamp - TEN_MINUTES)
                : 0;

            while (!history_.empty() && history_.front().timestamp < cutoff) {
                history_.pop_front();
            }
        }
    }

    mutable std::mutex mutex_;
    std::deque<Entry> history_;

    float latest_lux_ = 0.0f;
    uint64_t latest_timestamp_ = 0;
    bool has_latest_;

    std::atomic<bool> stop_;
    std::thread worker_;
};

/*
很多面試官會追問：

如果某個 timestamp 沒有剛好對應 sample，要不要回傳「該時間點之前最近的一筆有效值」？

這在 real-time / time-series 更常見。

可以加一個 API：

int getMostRecentLuxAtOrBefore(uint64_t timestamp, float& out) const {
    std::lock_guard<std::mutex> lock(mutex_);

    if (history_.empty()) return -1;
    if (timestamp < history_.front().timestamp) return -1;

    auto it = std::upper_bound(
        history_.begin(), history_.end(), timestamp,
        [](uint64_t ts, const Entry& e) {
            return ts < e.timestamp;
        }
    );

    if (it == history_.begin()) return -1;
    --it;

    out = it->lux;
    return 0;
}

這版語意是：

查詢時間 t
回傳 <= t 的最後一筆有效 sample

這通常比 exact match 更實用。


為什麼這樣設計是對的
Non-blocking

對外 API 完全不會呼叫 read_next_sample()，只讀快取。

Thread-safe

所有共享資料：

latest_lux_
history_

都由 mutex_ 保護。

不會無限長大

history_ 只保留 10 分鐘。

查詢效率好
最新值：O(1)
歷史查詢：O(log n)
prune：總攤銷 O(1)
面試時要主動講的 tradeoff
1. 為什麼不用 lock-free？

可以做，但這題沒必要。

最新值其實可以做成 atomic snapshot
但歷史查詢仍然需要同步保護
用 mutex 更簡單、可讀性更高、風險更低
2. 為什麼只存 VALID？

因為題目要求的是：

most recent valid lux value

NO_CHANGE 沒有新 lux 值，不需要存成新的 sample。

3. 為什麼用 deque？

因為：

尾端插入快
前端 prune 快
很適合 sliding window
*/

int main() {
    ALSWrapper als;

    // wait until some samples are ingested in the background
    // (depends on judge / mock environment)

    auto latest = als.getLatestLux();
    if (latest) {
        // print latest
    }

    float lux = 0.0f;
    int rc = als.getLuxAt(2, lux);
    if (rc == 0) {
        // print lux
    } else {
        // print rc
    }

    return 0;
}
/*
白板面試版答題話術

你可以這樣講：

我會把 blocking 的 ALS 呼叫放到背景執行緒中，讓它持續 ingest sensor sample。
每次收到 VALID sample，就更新 latest snapshot，並追加到一個只保留最近 10 分鐘資料的 deque。
對外提供兩個 non-blocking API：一個 O(1) 取得最新有效 lux，另一個透過 binary search 在 O(log n) 查詢指定時間點。
整體 thread safety 用 mutex 保護共享狀態，這在正確性、可讀性與效能之間是合理取捨。
*/
