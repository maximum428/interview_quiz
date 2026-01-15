/* Factory Method lets subclasses decide what to create, 
while the base class defines when and how the object is used.

一句話版本（面試先講這句）

Factory Method Pattern 定義一個用來建立物件的介面，但讓子類別決定要實例化哪一個具體類別。

或更白話一點：

把「new 什麼物件」這件事，延遲到子類別來決定。

Q1：Factory Method 解決什麼問題？

It decouples object creation from usage and allows subclasses to decide which concrete class to instantiate.

Q2：什麼時候用 Factory Method？

When object creation logic varies by context and you want to follow the Open–Closed Principle.


✅ 用 Factory Method（正確版）
          ┌───────────────┐
          │   BaseClass   │
          │───────────────│
          │ template()    │  ← 定義「什麼時候用」
          │   └─ create() │  ← Factory Method（抽象）
          └───────▲───────┘
                  │
     ┌────────────┼────────────┐
     │            │            │
┌─────────┐  ┌─────────┐  ┌─────────┐
│ Sub A   │  │ Sub B   │  │ Sub C   │
│─────────│  │─────────│  │─────────│
│ create()│  │ create()│  │ create()│
│ new A   │  │ new B   │  │ new C   │
└─────────┘  └─────────┘  └─────────┘


👉 Base class：

不知道 new 什麼

只負責「流程」

👉 Subclass：

決定「new 哪一個」
*/



#include <iostream>

using namespace std;

class Burger {
public:
    Burger() {}
    virtual ~Burger() {}
    void Grill() {
        cout << "Grill for 5 minutes... done\n";
    }
    void Prepare() {
        cout << "Preparing " << m_name << "\n";
        cout << "Add bottom half of " << m_bun << "...\n";
        cout << "Add grilled burger patty...\n";
        cout << "Adding condiments :\n";
        vector<string>::iterator condimentsIter;
        for (condimentsIter = m_condiments.begin(); condimentsIter != m_condiments.end(); condimentsIter++) {
            string condiment = *condimentsIter;
            cout << "    " << condiment << "\n";
        }
        cout << "Adding top " << m_bun << "\n";
    }
    
    void Wrap() {
        cout << "Wrapping your " << GetName() << "\n";
    }
    string GetName() { return m_name; }
protected:
    string m_name;
    string m_bun;
    vector<string> m_condiments;
};

class McDonaldsBurger : public Burger {
public:
    McDonaldsBurger() {
        m_name = string("McDonald's Burger");
        m_bun  = string("Plain Bun");
        m_condiments.push_back("Ketchup");
        m_condiments.push_back("Mustard");
        m_condiments.push_back("Onions");
        m_condiments.push_back("Pickle");
    }
    virtual ~McDonaldsBurger() {}
};

class McDonaldsCheeseBurger : public Burger {
public:
    McDonaldsCheeseBurger() {
        m_name = string("McDonald's Cheese Burger");
        m_bun  = string("Plain Bun");
        m_condiments.push_back("Ketchup");
        m_condiments.push_back("Mustard");
        m_condiments.push_back("Onions");
        m_condiments.push_back("Pickle");
        m_condiments.push_back("Cheese");
    }
    virtual ~McDonaldsCheeseBurger() {}
};

class BurgerKingBurger : public Burger {
public:
    BurgerKingBurger() {
        m_name = string("Burger King Burger");
        m_bun  = string("Sesame Seed Bun");
        m_condiments.push_back("Ketchup");
        m_condiments.push_back("Mustard");
        m_condiments.push_back("Pickle");
    }
    virtual ~BurgerKingBurger() {}
};

class BurgerKingCheeseBurger : public Burger {
public:
    BurgerKingCheeseBurger() {
        m_name = string("Burger King Cheese Burger");
        m_bun  = string("Sesame Seed Bun");
        m_condiments.push_back("Ketchup");
        m_condiments.push_back("Mustard");
        m_condiments.push_back("Pickle");
        m_condiments.push_back("Cheese");
    }
    virtual ~BurgerKingCheeseBurger() {}
};

class BurgerJoint {
public:
    BurgerJoint() {}
    virtual ~BurgerJoint() {}
    virtual Burger *CreateBurger(string type) = 0;
    virtual Burger *OrderBurger(string type) {
        Burger *burger = CreateBurger(type);
        burger->Grill();
        burger->Prepare();
        burger->Wrap();
        
        return burger;
    }
};

class McDonalds : public BurgerJoint {
public:
    McDonalds() {}
    virtual ~McDonalds() {}
    virtual Burger *CreateBurger(string type) {
        if (type.compare("cheeseburger") == 0) {
            return new McDonaldsCheeseBurger();
        } else {
            return new McDonaldsBurger();
        }
    }
};

class BurgerKing : public BurgerJoint {
public:
    BurgerKing() {}
    virtual ~BurgerKing() {}
    virtual Burger *CreateBurger(string type) {
        if (type.compare("cheeseburger") == 0)
            return new BurgerKingCheeseBurger();
        else
            return new BurgerKingBurger();
    }
};

int main() {
    BurgerJoint *mcDonalds = new McDonalds();
    Burger *mcDonaldsCheeseBurger = mcDonalds->OrderBurger(string("cheeseburger"));
    cout << "I just ordered a " << mcDonaldsCheeseBurger->GetName() << "\n\n";
    delete mcDonaldsCheeseBurger;
    
    Burger *mcDonaldsBurger = mcDonalds->OrderBurger(string("burger"));
    cout << "I just ordered a " << mcDonaldsBurger->GetName() << "\n\n";
    delete mcDonaldsBurger;
    delete mcDonalds;

    BurgerJoint *burgerKing = new BurgerKing();
    
    Burger *burgerKingCheeseBurger = burgerKing->OrderBurger(string("cheeseburger"));
    cout << "I just ordered a " << burgerKingCheeseBurger->GetName() << "\n\n";
    delete burgerKingCheeseBurger;
    
    Burger *burgerKingBurger = burgerKing->OrderBurger(string("burger"));
    cout << "I just ordered a " << burgerKingBurger->GetName() << "\n\n";
    delete burgerKingBurger;
    delete burgerKing;
    
    return 0;
}


/***************************************************************************************
********************************* Smart Pointer Version ********************************
****************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
using namespace std::string_literals;

class Burger {
protected:
    string m_name, m_bun;
    vector<string> m_condiments;
public:
    virtual ~Burger() = default;
    void Grill() {
        cout << "Grill for 5 minutes... done\n";
    }
    void Prepare() {
        cout << "Preparing " << m_name << endl;
        cout << "Add bottom half of " << m_bun << "...\n";
        cout << "Add grilled burger patty...\n";
        cout << "Add condiments :\n";
        for (const auto& condiment : m_condiments) {
            cout << "   " << condiment << endl; 
        }
        cout << "Adding top " << m_bun << endl;
    }
    void Wrap() {
        cout << "Wrapping your " << GetName() << "\n";
    }
    string GetName() { return m_name; }
};

class McDonaldsBurger : public Burger {
public:
    McDonaldsBurger() {
        m_name = "McDonald's Burger"s;
        m_bun  = "Plain Bun"s;
        m_condiments = { "ketchup", "Mustard", "Onions", "Pickle" };
    }
};

class McDonaldsCheeseBurger : public Burger {
public:
    McDonaldsCheeseBurger() {
        m_name = "McDonald's Cheese Burger"s;
        m_bun  = "Plain Bun";
        m_condiments = { "Ketchup", "Mustard", "Onions", "Pickle", "Cheese" };
    }
};

class BurgerKingBurger : public Burger {
public:
    BurgerKingBurger() {
        m_name = "Burger King Burger"s;
        m_bun  = "Sesame Seed Bun"s;
        m_condiments = { "Ketchup", "Mustard", "Pickle" };
    }
};

class BurgerKingCheeseBurger : public Burger {
public:
    BurgerKingCheeseBurger() {
        m_name = "Burger King Cheese Burger"s;
        m_bun  = "Sesame Seed Bun"s;
        m_condiments = { "Ketchup", "Mustard", "Pickle", "Cheese" };
    }
};

class BurgerJoint {
public:
    virtual ~BurgerJoint() = default;
    virtual unique_ptr<Burger> CreateBurger(const string& type) = 0;
    unique_ptr<Burger> OrderBurger(const string& type) {
        auto burger = CreateBurger(type);
        burger->Grill();
        burger->Prepare();
        burger->Wrap();
        
        return burger;
    }
};

class McDonalds : public BurgerJoint {
public:
    unique_ptr<Burger> CreateBurger(const string& type) override {
        if (type == "cheeseburger") {
            return make_unique<McDonaldsCheeseBurger>();
        }
        return make_unique<McDonaldsBurger>();
    }
};

class BurgerKing : public BurgerJoint {
public:
    unique_ptr<Burger> CreateBurger(const string& type) override {
        if (type == "cheeseburger")
            return make_unique<BurgerKingCheeseBurger>();
        return make_unique<BurgerKingBurger>();
    }
};

int main(int argc, char** argv) {
    unique_ptr<BurgerJoint> mcDonalds = make_unique<McDonalds>();
    
    auto mcDonaldsCheeseBurger = mcDonalds->OrderBurger("cheeseburger");
    cout << "I just ordered a " << mcDonaldsCheeseBurger->GetName() << "\n\n";
    
    auto mcDonaldsBurger = mcDonalds->OrderBurger("burger");
    cout << "I just ordered a " << mcDonaldsBurger->GetName() << "\n\n";
    
    unique_ptr<BurgerJoint> burgerKing = make_unique<BurgerKing>();
    
    auto burgerKingCheeseBurger = burgerKing->OrderBurger("cheeseburger");
    cout << "I just ordered a " << burgerKingCheeseBurger->GetName() << "\n\n";
    
    auto burgerKingBurger = burgerKing->OrderBurger("burger");
    cout << "I just ordered a " << burgerKingBurger->GetName() << "\n\n";
    
    return 0;
}
