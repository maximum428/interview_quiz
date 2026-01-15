/*
The Template Method Pattern defines a skeleton of an algorithm in a method deferring some steps to subclasses. 
Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm’s structure

一句話版

Template Method Pattern 是：

父類別先把「做事情的流程」寫好，但把某些步驟留給子類別自己實作。

流程不變，細節可變。

核心結構總圖（一定要會畫）
        AbstractClass
        ┌─────────────────────────┐
        │ templateMethod()  ★     │  ← 演算法骨架
        │─────────────────────────│
        │ step1()   (implemented) │
        │ step2()   (abstract)    │  ← 子類實作
        │ step3()   (abstract)    │
        │ hook()    (optional)    │
        └───────────┬─────────────┘
                    │
        ┌───────────┴───────────┐
        ▼                       ▼
   ConcreteClassA         ConcreteClassB
   ─ step2() A            ─ step2() B
   ─ step3() A            ─ step3() B
*/
#include <iostream>

using namespace std;

class Pizza {
public:
    Pizza(string description) : m_description(description) {}
    virtual ~Pizza() {}
    void Prepare() {
        cout << "Preparing a " << m_description << "...\n";
        PrepareDough();
        AddSauce();
        AddToppings();
        Bake();
        cout << "\n";
    }
protected:
    virtual void PrepareDough() {
        cout << "adding sauce\n";
    }
    virtual void AddSauce() {
        cout << "adding sauce\n";
    }
    virtual void AddToppings() = 0;
    virtual void Bake() {
        cout << "bake pizza\n";
    }
private:
    string m_description;
};

class CheesePizza : public Pizza {
public:
    CheesePizza() : Pizza(string("Cheese Pizza")) {}
    virtual ~CheesePizza() {}
protected:
    virtual void AddToppings() {
        cout << "adding cheese topping\n";
    }
};

class MeatLoversPizza : public Pizza {
public:
    MeatLoversPizza() : Pizza(string("Meat Lover's Pizza")) {}
    virtual ~MeatLoversPizza() {}
protected:
    virtual void AddToppings() {
        cout << "adding cheese, pepperoni, sausage and bacon toppings\n";
    }
};

int main() {
    CheesePizza cheesePizza;
    cheesePizza.Prepare();
    
    MeatLoversPizza meatLoversPizza;
    meatLoversPizza.Prepare();
    return 0;
}
