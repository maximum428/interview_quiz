/*
The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable. 
Strategy lets the algorithm vary independently from clients that use it.

一句話白話解釋

👉 把「一組可互換的演算法（行為）」各自包成獨立物件，讓使用它們的物件不需要改程式碼，就能自由切換行為。

Strategy Pattern 的核心價值（面試重點）

✅ 消除大量 if/else
✅ 行為可以在執行期切換
✅ Client 與演算法解耦
✅ 符合單一職責 & 開放封閉原則

再濃縮一句（考試／面試用）

Strategy Pattern 將可變的行為抽離成獨立策略物件，使行為可以在不修改使用者的情況下被替換或擴充。

核心結構總圖（必背）
Client
  │
  │ uses
  ▼
┌──────────────────┐
│    Context       │   ← 使用策略的人
│──────────────────│
│ Strategy* strat  │───┐
│──────────────────│   │
│ execute()        │   │ delegates
└──────────────────┘   ▼
                   ┌───────────────┐
                   │   Strategy    │  ← 抽象策略
                   │───────────────│
                   │ algorithm()   │
                   └──────┬────────┘
                          │
        ┌─────────────────┼─────────────────┐
        ▼                 ▼                 ▼
  StrategyA          StrategyB          StrategyC
 (算法A)              (算法B)              (算法C)
*/

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


/*******************************************************************************************
************************************* Smart Pointer Version ********************************
********************************************************************************************/

#include <iostream>
#include <memory>

using namespace std;

class WeaponBehavior {
public:
    virtual ~WeaponBehavior() {}
    virtual void useWeapon() = 0;
};

class BlasterBehavior : public WeaponBehavior {
public:
    void useWeapon() override {
        cout << "I am using my blaster!\n";
    }
};

class LightSaberBehavior : public WeaponBehavior {
public:
    void useWeapon() override {
        cout << "I am using my light saber!\n";
    }
};

class CrossBowBehavior : public WeaponBehavior {
public:
    void useWeapon() override {
        cout << "I am using my cross bow!\n";
    }
};

class StarWarsCharacter {
protected:
    shared_ptr<WeaponBehavior> m_WeaponBehavior;
    string m_name;
public:
    StarWarsCharacter(string name, shared_ptr<WeaponBehavior> weaponBehavior) : m_WeaponBehavior(weaponBehavior), m_name(name) {}
    virtual ~StarWarsCharacter() {}
    virtual void Fight() {
        cout << m_name << ": ";
        m_WeaponBehavior->useWeapon();
    }
    virtual void SetWeaponBehavior(shared_ptr<WeaponBehavior> weaponBehavior) {
        m_WeaponBehavior = weaponBehavior;
    }
};

int main(int argc, char** argv) {
    auto blasterBehavior = make_shared<BlasterBehavior>();
    auto lightSaberBehavior = make_shared<LightSaberBehavior>();
    auto crossBowBehavior = make_shared<CrossBowBehavior>();
    
    auto hanSolo = make_shared<StarWarsCharacter>("Han Solo", blasterBehavior);
    auto lukeSkyWalker = make_shared<StarWarsCharacter>("Luke Skywalker", lightSaberBehavior);
    auto chewy = make_shared<StarWarsCharacter>("Chewy", crossBowBehavior);
    
    hanSolo->Fight();
    lukeSkyWalker->Fight();
    chewy->Fight();
    
    hanSolo->SetWeaponBehavior(lightSaberBehavior);
    lukeSkyWalker->SetWeaponBehavior(crossBowBehavior);
    chewy->SetWeaponBehavior(blasterBehavior);
    
    hanSolo->Fight();
    lukeSkyWalker->Fight();
    chewy->Fight();
    
    return 0;
}
