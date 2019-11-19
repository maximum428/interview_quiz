#include <iostream>

using namespace std;

class ZooPatron {
public:
    ZooPatron(string name) : m_name(name) {}
    virtual ~ZooPatron() {}
    string GetName() { return m_name; }
    virtual bool HasAnimalShowAccess() = 0;
    virtual bool HasEarlyAccess() = 0;
private:
    string m_name;
};

class ZooMember : public ZooPatron {
public:
    ZooMember(string name) : ZooPatron(name) {}
    virtual ~ZooMember() {}
    virtual bool HasAnimalShowAccess() { return true; }
    virtual bool HasEarlyAccess() { return true; }
};

class ZooGuest : public ZooPatron {
public:
    ZooGuest(string name) : ZooPatron(name) {}
    virtual ~ZooGuest() {}
    virtual bool HasAnimalShowAccess() { return false; }
    virtual bool HasEarlyAccess() { return false; }
};

class ZooIF {
public:
    virtual void EnterZooEarly(ZooPatron *patron) = 0;
    virtual void AttendAnimalShow(ZooPatron *patron) = 0;
};

class Zoo {
public:
    Zoo() {}
    virtual ~Zoo() {}
    virtual void EnterZooEarly(ZooPatron *patron) {
        cout << "Welcome, " << patron->GetName() << ", to our early access zoo hours\n";
    }
    virtual void AttendAnimalShow(ZooPatron *patron) {
        cout << "Welcome, " << patron->GetName() << ", to our animal show\n";
    }
};

class ZooProxy {
public:
    ZooProxy(Zoo *zoo) : m_pZoo(zoo) {}
    virtual ~ZooProxy() {}
    virtual void EnterZooEarly(ZooPatron *patron) {
        if (patron->HasEarlyAccess()) {
            m_pZoo->EnterZooEarly(patron);
        } else {
            cout << "Sorry, " << patron->GetName() << ", you don't have early zoo access privileges\n";
        }
    }
    
    virtual void AttendAnimalShow(ZooPatron *patron) {
        if (patron->HasAnimalShowAccess()) {
            m_pZoo->AttendAnimalShow(patron);
        } else {
            cout << "Sorry, " << patron->GetName() << ", you don't have access to the animal show\n";
        }
    }
private:
    Zoo *m_pZoo;
};

int main() {
    ZooMember member(string("Nicklas"));
    ZooGuest guest(string("Bob"));
    
    Zoo zoo;
    ZooProxy zooProxy(&zoo);
    
    zooProxy.EnterZooEarly(&member);
    zooProxy.EnterZooEarly(&guest);
    zooProxy.AttendAnimalShow(&member);
    zooProxy.AttendAnimalShow(&guest);
    
    return 0;
}
