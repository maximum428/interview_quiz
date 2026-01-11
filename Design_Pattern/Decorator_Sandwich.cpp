/* The Decorator Pattern allows behavior to be added to individual objects dynamically without modifying their class.
It works by wrapping objects in decorator classes that implement the same interface and delegate calls while adding extra functionality.
This avoids class explosion and follows the Open–Closed Principle.

Decorator Pattern 讓你在不修改原本類別、不用繼承爆炸的情況下，
動態地替物件加上新功能（責任）。

八、Decorator Pattern 的優點

✅ 遵守 Open–Closed Principle
✅ 可動態加功能
✅ 避免繼承爆炸
✅ 功能可自由組合

九、Decorator Pattern 的缺點（一定要說）

⚠️ 物件數量多
⚠️ Debug 比較困難（一層包一層）
⚠️ 結構不直觀（對新手）
*/

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


/****************************************************************************************
******************************** Smart Pointer Version **********************************
*****************************************************************************************/

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace std::string_literals;

class Sub {
public:
    virtual ~Sub() = default;
    virtual double GetCost() = 0;
    virtual string GetDescription() = 0;
};

class SmallSub : public Sub {
public:
    double GetCost() override { return 5.99; }
    string GetDescription() override { return "Small Sub"s; }
};

class LargeSub : public Sub {
public:
    double GetCost() override { return 8.99; }
    string GetDescription() override { return "Large Sub"s; }
};

class SubItemsDecorator : public Sub {
protected:
    unique_ptr<Sub> m_Sub;
public:
    explicit SubItemsDecorator(unique_ptr<Sub> sub) : m_Sub(move(sub)) {}
    double GetCost() override { return m_Sub->GetCost(); }
    string GetDescription() override { return m_Sub->GetDescription(); }
};

class Turkey : public SubItemsDecorator {
public:
    explicit Turkey(unique_ptr<Sub> sub) : SubItemsDecorator(move(sub)) {}
    string GetDescription() override {
        return m_Sub->GetDescription() + ", Turkey";
    }
};

class Bacon : public SubItemsDecorator {
public:
    explicit Bacon(unique_ptr<Sub> sub) : SubItemsDecorator(move(sub)) {}
    double GetCost() override { return m_Sub->GetCost() + 1.00; }
    string GetDescription() override { return m_Sub->GetDescription() + ", Bacon"s; }
};

class Lettuce : public SubItemsDecorator {
public:
    explicit Lettuce(unique_ptr<Sub> sub) : SubItemsDecorator(move(sub)) {}
    double GetCost() override { return m_Sub->GetCost() + 0.5; }
    string GetDescription() override { return m_Sub->GetDescription() + ", Lettuce"s; }
};

int main(int argc, char** argv) {
    auto sub1 = 
        make_unique<Bacon>(
            make_unique<Turkey>(
                make_unique<SmallSub>()
            )
        );
    
    cout << "Description: " << sub1->GetDescription() << endl;
    cout << "Cost.      : " << sub1->GetCost() << endl;
    cout << "\n";
    
    auto sub2 = 
        make_unique<Bacon>(
            make_unique<Lettuce>(
                make_unique<Turkey>(
                    make_unique<LargeSub>()
                )
            )
        );
    
    cout << "Description: " << sub2->GetDescription() << endl;
    cout << "Cost.      : " << sub2->GetCost() << endl;
    
    return 0;
}
