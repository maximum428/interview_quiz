/*
The Adapter Pattern converts the interface of a class into another interface clients expect. Adapter lets classes work together 
that couldn’t otherwise because of incompatible interfaces.
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
