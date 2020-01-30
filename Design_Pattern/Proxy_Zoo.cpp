/*
The Proxy Pattern provides a surrogate or placeholder for another object to control access to it.
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
