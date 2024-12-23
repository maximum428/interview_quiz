#include <iostream>
#include <mutex>
#include <chrono>
#include <future>
#include <thread>

constexpr auto tenMill = 10000000;

using namespace std;

class MySingleton {
public:
    static MySingleton& getInstance() {
        std::call_once(initInstanceFlag, &MySingleton::initSingleton);
        return *instance;
    }
private:
    MySingleton() = default;
    //~MySingleton() = default;
    //MySingleton(const MySingleton &) = delete;
    MySingleton& operator=(const MySingleton &) = delete;

    static MySingleton *instance;
    static std::once_flag initInstanceFlag;
    static void initSingleton() {
        instance = new MySingleton();
    }
};

MySingleton *MySingleton::instance = nullptr;
std::once_flag MySingleton::initInstanceFlag;

std::chrono::duration<double> getTime() {
    auto begin = chrono::system_clock::now();
    for (size_t i = 0; i < tenMill; i++) {
        MySingleton::getInstance();
    }
    return chrono::system_clock::now() - begin;
}

class Singleton {
public:
    static Singleton *GetInstance() {
        std::lock_guard<std::mutex> guard(mutex);
        if (instance == 0) {
            instance = new Singleton();
        }
        return instance;
    }
private:
    Singleton() {}
    virtual ~Singleton() {}
    static Singleton *instance;
    static std::mutex mutex;
};

Singleton *Singleton::instance = 0;
std::mutex Singleton::mutex;

int main() {
    Singleton *singleton = Singleton::GetInstance();
    
    auto fut1= std::async(std::launch::async,getTime);
    auto fut2= std::async(std::launch::async,getTime);
    auto fut3= std::async(std::launch::async,getTime);
    auto fut4= std::async(std::launch::async,getTime);
    
    auto total= fut1.get() + fut2.get() + fut3.get() + fut4.get();
    
    std::cout << total.count() << std::endl;
    
    return 0;
}
