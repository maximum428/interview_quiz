#include <iostream>

using namespace std;

class WeaponBehavior {
public:
    virtual ~WeaponBehavior() {}
    virtual void useWeapon() = 0;
};

class BlasterBehavior : public WeaponBehavior {
public:
    BlasterBehavior() {}
    virtual ~BlasterBehavior() {}
    virtual void useWeapon() {
        cout << "I am using my blaster!\n";
    }
};

class LightSaberBehavior : public WeaponBehavior {
public:
    LightSaberBehavior() {}
    virtual ~LightSaberBehavior() {}
    virtual void useWeapon() {
        cout << "I am using my light saber!\n";
    }
};

class CrossBowBehavior : public WeaponBehavior {
public:
    CrossBowBehavior() {}
    virtual ~CrossBowBehavior() {}
    virtual void useWeapon() {
        cout << "I am using my cross bow!\n";
    }
};

class StarWarsCharacter {
public:
    StarWarsCharacter(string name, WeaponBehavior *weaponBehavior) : m_pWeaponBehavior(weaponBehavior), m_name(name) {}
    virtual ~StarWarsCharacter() {}
    virtual void Fight() {
        cout << m_name << ": ";
        m_pWeaponBehavior->useWeapon();
    }
    virtual void SetWeaponBehavior(WeaponBehavior *weaponBehavior) {
        m_pWeaponBehavior = weaponBehavior;
    }
protected:
    WeaponBehavior *m_pWeaponBehavior;
    string m_name;
};

int main() {
    WeaponBehavior *blasterBehavior = new BlasterBehavior();
    WeaponBehavior *lightSaberBehavior = new LightSaberBehavior();
    WeaponBehavior *crossBowBehavior = new CrossBowBehavior();
    
    StarWarsCharacter *hanSolo = new StarWarsCharacter(string("Han Solo"), blasterBehavior);
    StarWarsCharacter *lukeSkyWalker = new StarWarsCharacter(string("Luke Skywalker"), lightSaberBehavior);
    StarWarsCharacter *chewy = new StarWarsCharacter(string("Chewy"), crossBowBehavior);
    
    hanSolo->Fight();
    lukeSkyWalker->Fight();
    chewy->Fight();
    
    hanSolo->SetWeaponBehavior(lightSaberBehavior);
    lukeSkyWalker->SetWeaponBehavior(crossBowBehavior);
    chewy->SetWeaponBehavior(blasterBehavior);
    
    hanSolo->Fight();
    lukeSkyWalker->Fight();
    chewy->Fight();
    
    delete hanSolo;
    delete lukeSkyWalker;
    delete chewy;
    
    delete blasterBehavior;
    delete lightSaberBehavior;
    delete crossBowBehavior;
    
    return 0;
}
