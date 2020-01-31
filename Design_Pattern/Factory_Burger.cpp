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
