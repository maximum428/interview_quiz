#include <iostream>

using namespace std;

class Sub {
public:
    virtual ~Sub() {}
    virtual double GetCost() = 0;
    virtual string GetDescription() = 0;
};

class SmallSub : public Sub {
public:
    SmallSub() {}
    virtual ~SmallSub() {}
    virtual double GetCost() { return 5.99; }
    virtual string GetDescription() { return string("Small Sub"); }
};

class LargeSub : public Sub {
public:
    LargeSub() {}
    virtual ~LargeSub() {}
    virtual double GetCost() { return 8.99; }
    virtual string GetDescription() { return string("Large Sub"); }
};

class SubItemsDecorator : public Sub {
public:
    SubItemsDecorator(Sub *sub) : m_pSub(sub) {}
    virtual ~SubItemsDecorator() {}
    virtual double GetCost() { return m_pSub->GetCost(); }
    virtual string GetDescription() { return m_pSub->GetDescription(); }
    
protected:
    Sub *m_pSub;
};

class Turkey : public SubItemsDecorator {
public:
    Turkey(Sub *sub) : SubItemsDecorator(sub) {}
    virtual ~Turkey() {}
    virtual string GetDescription() {
        return m_pSub->GetDescription() + ", Turkey";
    }
};

class Bacon : public SubItemsDecorator {
public:
    Bacon(Sub *sub) : SubItemsDecorator(sub) {}
    virtual ~Bacon() {}
    virtual double GetCost() { return m_pSub->GetCost() + 1.00; }
    virtual string GetDescription() { return m_pSub->GetDescription() + string(", Bacon"); }
};

class Lettuce : public SubItemsDecorator {
public:
    Lettuce(Sub *sub) : SubItemsDecorator(sub) {}
    virtual ~Lettuce() {}
    virtual double GetCost() { return m_pSub->GetCost() + 0.5; }
    virtual string GetDescription() { return m_pSub->GetDescription() + string(", Lettuce"); }
};

int main() {
    SmallSub smallSub;
    Turkey smallTurkey(&smallSub);
    Bacon  smallBacon(&smallTurkey);
    Sub *sub1 = &smallBacon;
    
    cout << "Description: " << sub1->GetDescription() << endl;
    cout << "Cost       : " << sub1->GetCost() << endl;
    
    LargeSub largeSub;
    Turkey largeTurkey(&largeSub);
    Lettuce largeLettuce(&largeTurkey);
    Bacon  largeBacon(&largeLettuce);
    
    Sub *sub2 = &largeBacon;
    
    cout << "Description: " << sub2->GetDescription() << endl;
    cout << "Cost       : " << sub2->GetCost() << endl;
    
    return 0;
}
