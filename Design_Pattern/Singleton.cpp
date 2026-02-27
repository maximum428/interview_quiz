#include <iostream>
#include <chrono>
#include <future>
#include <mutex>

using namespace std;

constexpr size_t tenMill = 10'000'000;

class MySingleton {
    MySingleton() = default;
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;
public:
    static MySingleton& getInstance() {
        static MySingleton instance;
        return instance;
    }
};

chrono::duration<double> getTimeMeyers() {
    auto begin = chrono::steady_clock::now();

    volatile const MySingleton* sink = nullptr;
    for (size_t i = 0; i < tenMill; i++) {
        sink = &MySingleton::getInstance();
    }

    return chrono::steady_clock::now() - begin;
}

class Singleton {
private:
    static mutex m_mutex;
    static Singleton* instance;
    Singleton() = default;
public:
    static Singleton* getInstance() {
        lock_guard<mutex> guard(m_mutex); // ✅ 更穩
        if (!instance) instance = new Singleton();
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::m_mutex;

chrono::duration<double> getTimeLocked() {
    auto begin = chrono::steady_clock::now();

    volatile const Singleton* sink = nullptr;
    for (size_t i = 0; i < tenMill; i++) {
        sink = Singleton::getInstance();
    }

    return chrono::steady_clock::now() - begin;
}

int main() {
    cout << "Single-thread Meyers: " << getTimeMeyers().count() << " s\n";
    cout << "Single-thread Locked: " << getTimeLocked().count() << " s\n";

    // wall-clock for 4 threads (Meyers)
    auto t0 = chrono::steady_clock::now();
    auto f1 = async(launch::async, getTimeMeyers);
    auto f2 = async(launch::async, getTimeMeyers);
    auto f3 = async(launch::async, getTimeMeyers);
    auto f4 = async(launch::async, getTimeMeyers);
    (void)(f1.get() + f2.get() + f3.get() + f4.get());
    auto wallMeyers = chrono::steady_clock::now() - t0;
    cout << "4-thread wall Meyers: " << chrono::duration<double>(wallMeyers).count() << " s\n";

    // wall-clock for 4 threads (Locked)
    t0 = chrono::steady_clock::now();
    auto g1 = async(launch::async, getTimeLocked);
    auto g2 = async(launch::async, getTimeLocked);
    auto g3 = async(launch::async, getTimeLocked);
    auto g4 = async(launch::async, getTimeLocked);
    (void)(g1.get() + g2.get() + g3.get() + g4.get());
    auto wallLocked = chrono::steady_clock::now() - t0;
    cout << "4-thread wall Locked: " << chrono::duration<double>(wallLocked).count() << " s\n";

    return 0;
}
