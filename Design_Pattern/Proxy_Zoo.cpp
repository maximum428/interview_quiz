/*
The Proxy Pattern provides a surrogate or placeholder for another object to control access to it.

1. Proxy = 代理、替身、佔位符

    - Proxy 本身不是最終物件，而是一個「替身」。

    - 它可以站在真正物件前面，決定何時或怎麼使用它。

2. 控制對真實物件的存取

    - Proxy 可以在存取真實物件前做一些額外操作，例如：

    - 權限檢查（只有授權的使用者可以呼叫方法）

    - 延遲初始化 / 懶加載（只有真正需要時才創建重資源物件）

    - 日誌紀錄 / 計數 / 緩存

    - 例如：在你的 Zoo 範例中，ZooProxy 會檢查使用者是否有 HasEarlyAccess 或 HasAnimalShowAccess，決定是否讓它進入 Zoo 或看動物秀。

3. 代理與真實物件的相同介面

    - Proxy 通常跟真實物件實現相同的接口，對客戶端來說，使用 Proxy 和使用真實物件沒有差別。

    - 這樣客戶端就不需要知道背後有 Proxy 存在。

簡單比喻：

真實物件：Zoo（動物園）

Proxy：ZooProxy（動物園門口的門衛）

客戶端：ZooMember / ZooGuest（參觀者）

門衛會檢查你是否有早鳥票（權限檢查），才允許你進入；對參觀者來說，看起來就像直接進入 Zoo 一樣，但實際上 Proxy 控制了訪問。

總結一句話：

Proxy 是「站在真實物件前的守門人」，它提供控制、保護或延遲存取，而對使用者看起來像直接操作真實物件。


整體結構圖（核心）
Client
   │
   │ calls
   ▼
┌──────────────┐
│    Proxy     │  ← 代理 / 看門人
│──────────────│
│ + request()  │
└───────┬──────┘
        │ decides if / how
        ▼
┌──────────────┐
│ RealObject   │  ← 真正幹活的對象
│──────────────│
│ + request()  │
└──────────────┘
*/
#include <iostream>

using namespace std;

class ZooCustomer {
public:
    ZooCustomer(string name) : m_Name(name) {}
    virtual ~ZooCustomer() {}
    string GetName() { return m_Name; }
    virtual bool HasAnimalShowAccess() = 0;
    virtual bool HasEarlyAccess() = 0;
private:
    string m_Name;
};

class ZooMember : public ZooCustomer {
public:
    ZooMember(string name): ZooCustomer(name) {}
    virtual ~ZooMember() {}
    virtual bool HasAnimalShowAccess() {
        return true;
    }
    virtual bool HasEarlyAccess() {
        return false;
    }
};

class ZooGuest : public ZooCustomer {
public:
    ZooGuest(string name) : ZooCustomer(name) {}
    virtual ~ZooGuest() {}
    virtual bool HasAnimalShowAccess() {
        return false;
    }
    virtual bool HasEarlyAccess() {
        return true;
    }
};

class ZooInterface {
public:
    virtual void EnterZooEarly(ZooCustomer *customer) {}
    virtual void AttenAnimalShow(ZooCustomer *customer) {}
};

class Zoo : public ZooInterface {
public:
    Zoo() {}
    ~Zoo() {}
    void EnterZooEarly(ZooCustomer *customer) {
        cout << "Welcome, " << customer->GetName() << ", to our early access zoo hours\n";
    }
    void AttendAnimalShow(ZooCustomer *customer) {
        cout << "Welcome, " << customer->GetName() << ", to our animal show\n";
    }
};

class ZooProxy : public ZooInterface {
public:
    ZooProxy(Zoo *zoo) : m_Zoo(zoo) {}
    ~ZooProxy() {}
    void EnterZooEarly(ZooCustomer *customer) {
        if (customer->HasEarlyAccess()) {
            m_Zoo->EnterZooEarly(customer);
        } else {
            cout << "Sorry, " << customer->GetName() << ", you don't have early zoo access privileges\n";
        }
    }
    void AttendAnimalShow(ZooCustomer *customer) {
        if (customer->HasAnimalShowAccess()) {
            m_Zoo->AttendAnimalShow(customer);
        } else {
            cout << "Sorry, " << customer->GetName() << ", you don't have access to the animal show\n";
        }
    }
private:
    Zoo *m_Zoo;
};

int main() {
    ZooMember member(string("Niclas"));
    ZooGuest guest(string("Bob"));
    
    Zoo zoo;
    ZooProxy zooProxy(&zoo);
    
    zooProxy.EnterZooEarly(&member);
    zooProxy.EnterZooEarly(&guest);
    zooProxy.AttendAnimalShow(&member);
    zooProxy.AttendAnimalShow(&guest);
    
    return 0;
}


/****************************************************************************************
*********************************** Smart Pointer Version *******************************
*****************************************************************************************/

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class ZooCustomer {
    string m_Name;
public:
    ZooCustomer(string name) : m_Name(name) {}
    virtual ~ZooCustomer() {}
    string GetName() const {
        return m_Name;
    }
    virtual bool HasAnimalShowAccess() = 0;
    virtual bool HasEarlyAccess() = 0;
};

class ZooMember : public ZooCustomer {
public:
    ZooMember(string name) : ZooCustomer(name) {}
    virtual ~ZooMember() {}
    virtual bool HasAnimalShowAccess() override {
        return true;
    }
    virtual bool HasEarlyAccess() override {
        return false;
    }
};

class ZooGuest : public ZooCustomer {
public:
    ZooGuest(string name) : ZooCustomer(name) {}
    virtual ~ZooGuest() {}
    virtual bool HasAnimalShowAccess() override {
        return false;
    }
    virtual bool HasEarlyAccess() override {
        return true;
    }
};

class ZooInterface {
public:
    virtual void EnterZooEarly(ZooCustomer *customer) {}
    virtual void AttendAnimalShow(ZooCustomer *customer) {}
};

class Zoo : public ZooInterface {
public:
    Zoo() {}
    virtual ~Zoo() {}
    void EnterZooEarly(ZooCustomer *customer) override {
        cout << "Welcome, " << customer->GetName() << ", to our early access zoo hours\n";
    }
    void AttendAnimalShow(ZooCustomer *customer) override {
        cout << "Welcome, " << customer->GetName() << ", to our animal show\n";
    }
};

class ZooProxy : public ZooInterface {
    Zoo *m_Zoo;
public:
    ZooProxy(Zoo *zoo) : m_Zoo(zoo) {}
    virtual ~ZooProxy() {}
    void EnterZooEarly(ZooCustomer *customer) override {
        if (customer->HasEarlyAccess()) {
            m_Zoo->EnterZooEarly(customer);
        } else {
            cout << "Sorry, " << customer->GetName() << ", you don't have early zoo access privileges\n";
        }
    }
    void AttendAnimalShow(ZooCustomer *customer) override {
        if (customer->HasAnimalShowAccess())
            m_Zoo->AttendAnimalShow(customer);
        else
            cout << "Sorry, " << customer->GetName() << ", you don't have access to the animal show\n";
    }
};

int main(int argc, char** argv) {
    auto member = make_unique<ZooMember>("Niclas");
    auto guest  = make_unique<ZooGuest>("Bob");
    
    auto zoo = make_unique<Zoo>();
    ZooProxy zooProxy(zoo.get());  // Proxy 不擁有 Zoo，只暫時引用
    
    zooProxy.EnterZooEarly(member.get());
    zooProxy.EnterZooEarly(guest.get());
    zooProxy.AttendAnimalShow(member.get());
    zooProxy.AttendAnimalShow(guest.get());
    
    return 0;
}
