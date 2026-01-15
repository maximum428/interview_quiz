/*
The Adapter Pattern converts the interface of a class into another interface clients expect. Adapter lets classes work together 
that couldn’t otherwise because of incompatible interfaces.
一句人話版總結

Adapter = 轉接頭
就像 USB-C → HDMI 轉接頭
👉 裝置沒改
👉 使用者也不用改
👉 中間加一個「轉接器」

軟體版核心結構圖（一定要會畫）
Client
  │
  │  Target Interface
  ▼
+------------------+
|   Adapter        |
|------------------|
| request()        |
+------------------+
          │
          │ calls
          ▼
+------------------+
|   Adaptee        |
|------------------|
| specificRequest()|
+------------------+
*/
#include <iostream>

using namespace std;

class Dog {
public:
    virtual ~Dog() {}
    virtual void Bark() = 0;
};

class LivingDog : public Dog {
public:
    LivingDog(string name) : m_name(name) {}
    virtual ~LivingDog() {}
    virtual void Bark() {
        cout << m_name << " is barking!\n";
    }
private:
    string m_name;
};

class RobotDog {
public:
    RobotDog(string name) : m_name(name) {}
    virtual ~RobotDog() {}
    void PlayBarkingSound() {
        cout << m_name << " is playing barking sound\n";
    }
private:
    string m_name;
};

class RobotDogAdapter : public Dog {
public:
    RobotDogAdapter(RobotDog *robotDog) : m_RobotDog(robotDog) {}
    virtual ~RobotDogAdapter() {}
    virtual void Bark() { m_RobotDog->PlayBarkingSound(); }
private:
    RobotDog *m_RobotDog;
};

int main() {
    Dog *livingDog = new LivingDog(string("Chester"));
    livingDog->Bark();
    
    RobotDog *robotDog = new RobotDog(string("Sony's Aibo"));
    Dog *robotDogAdapter = new RobotDogAdapter(robotDog);
    robotDogAdapter->Bark();
    
    delete livingDog;
    delete robotDogAdapter;
    delete robotDog;
    return 0;
}


/**************************************************************************
 *****************   Smart Pointer Version *****************
 **************************************************************************/

#include <iostream>
#include <memory>
#include <string>

using namespace std;
using namespace std::string_literals;

class Dog {
public:
    virtual ~Dog() = default;
    virtual void Bark() = 0;
};

class LivingDog : public Dog {
    string m_name;
public:
    LivingDog(string name) : m_name(move(name)) {}
    void Bark() override {
        cout << m_name << " is barking!\n";
    }
};

class RobotDog {
    string m_name;
public:
    RobotDog(string name) : m_name(move(name)) {}
    virtual ~RobotDog() {}
    void PlayBarkingSound() {
        cout << m_name << " is playing barking sound.\n";
    }
};

class RobotDogAdapter : public Dog {
    unique_ptr<RobotDog> m_RobotDog;
public:
    explicit RobotDogAdapter(unique_ptr<RobotDog> robotDog) : m_RobotDog(move(robotDog)) {}
    virtual void Bark() override {
        m_RobotDog->PlayBarkingSound();
    }
};

int main(int argc, char** argv) {
    unique_ptr<Dog> livingDog = make_unique<LivingDog>("Chester"s);
    livingDog->Bark();
    
    unique_ptr<Dog> robotDog = make_unique<RobotDogAdapter>(make_unique<RobotDog>("Sony's Aibo"s));
    robotDog->Bark();
    
    return 0;
}
