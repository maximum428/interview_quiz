#include <iostream>
#include <chrono>
#include <future>
#include <mutex>

using namespace std;

constexpr auto tenMill = 10000000;

class MySingleton {
public:
    static MySingleton& getInstance() {
        //call_once(initInstanceFlag, &MySingleton::initSingleton);
        static MySingleton instance;
        return instance;
    }
private:
    MySingleton() = default;
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;
    
    static MySingleton *instance;
    static once_flag initInstanceFlag;
    static void initSingleton() {
        instance = new MySingleton();
    }
};

MySingleton *MySingleton::instance = nullptr;
once_flag MySingleton::initInstanceFlag;

chrono::duration<double> getTime() {
    auto begin = chrono::steady_clock::now();
    for (size_t i = 0; i < tenMill; i++) {
        MySingleton::getInstance();
    }
    return chrono::steady_clock::now() - begin;
}

class Singleton {
public:
    static Singleton *GetInstance() {
        lock_guard guard(m_mutex);
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
private:
    Singleton() {}
    virtual ~Singleton() {}
    static Singleton *instance;
    static mutex m_mutex;
};

Singleton *Singleton::instance = nullptr;
mutex Singleton::m_mutex;

int main(int argc, char** argv) {
    Singleton *singleton = Singleton::GetInstance();
    
    auto future1 = async(launch::async, getTime);
    auto future2 = async(launch::async, getTime);
    auto future3 = async(launch::async, getTime);
    auto future4 = async(launch::async, getTime);
    
    auto total = future1.get() + future2.get() + future3.get() + future4.get();
    
    cout << total.count() << endl;
    return 0;
}
