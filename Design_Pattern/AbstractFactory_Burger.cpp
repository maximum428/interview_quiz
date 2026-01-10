/*
"The Abstract Factory Pattern provides an interface for creating families of related or dependent 
objects without specifying their concrete classes"
*/
#include <iostream>

using namespace std;

class Bun {
public:
    virtual ~Bun() {}
    virtual void Prepare() = 0;
};

class Pattie {
public:
    virtual ~Pattie() {}
    virtual void Prepare() = 0;
};

class Pickle {
public:
    virtual ~Pickle() {}
    virtual void Prepare() = 0;
};

class Onions {
public:
    virtual ~Onions() {}
    virtual void Prepare() = 0;
};

class Ketchup {
public:
    virtual ~Ketchup() {}
    virtual void Prepare() = 0;
};

class Mustard {
public:
    virtual ~Mustard() {}
    virtual void Prepare() = 0;
};

class SesameSeedBun : public Bun {
public:
    SesameSeedBun() {}
    virtual ~SesameSeedBun() {}
    virtual void Prepare() {
        cout << "Preparing Sesame Seed Bun\n";
    }
};

class SeedlessBun : public Bun {
public:
    SeedlessBun() {}
    virtual ~SeedlessBun() {}
    virtual void Prepare() {
        cout << "Prepareing Seedless Bun\n";
    }
};

class FlameBroiledPattie : public Pattie {
public:
    FlameBroiledPattie() {}
    virtual ~FlameBroiledPattie() {}
    virtual void Prepare() {
        cout << "Preparing Flame Broiled Burger\n";
    }
};

class GrilledPattie : public Pattie {
public:
    GrilledPattie() {}
    virtual ~GrilledPattie() {}
    virtual void Prepare() {
        cout << "Preparing Grilled Pattie\n";
    }
};

class SweetPickles : public Pickle {
public:
    SweetPickles() {}
    virtual ~SweetPickles() {}
    virtual void Prepare() {
        cout << "Preparing Sweet Pickles\n";
    }
};

class SourDillPickles : public Pickle {
public:
    SourDillPickles() {}
    virtual ~SourDillPickles() {}
    virtual void Prepare() {
        cout << "Preparing Sour Dill Pickles\n";
    }
};

class NoOnions : public Onions {
public:
    NoOnions() {}
    virtual ~NoOnions() {}
    virtual void Prepare() {
        // do noting
    }
};

class WhiteOnions : public Onions {
public:
    WhiteOnions() {}
    virtual ~WhiteOnions() {}
    virtual void Prepare() {
        cout << "Preparing White Onions\n";
    }
};

class HeinzKetchup : public Ketchup {
public:
    HeinzKetchup() {}
    virtual ~HeinzKetchup() {}
    virtual void Prepare() {
        cout << "Preparing Heinz Ketchup\n";
    }
};

class McDonaldsKetchup : public Ketchup {
public:
    McDonaldsKetchup() {}
    virtual ~McDonaldsKetchup() {}
    virtual void Prepare() {
        cout << "Preparing McDonalds Ketchup\n";
    }
};

class HeinzMustard : public Mustard {
public:
    HeinzMustard() {}
    virtual ~HeinzMustard() {}
    virtual void Prepare() {
        cout << "Preparing Heinz Mustard\n";
    }
};

class McDonaldsMustard : public Mustard {
public:
    McDonaldsMustard() {}
    virtual ~McDonaldsMustard() {}
    virtual void Prepare() {
        cout << "Preparing McDonalds Mustard\n";
    }
};

class BurgerIngredientsFactory {
public:
    virtual ~BurgerIngredientsFactory() {}
    virtual Bun *CreateBun() = 0;
    virtual Pattie *CreatePattie() = 0;
    virtual Pickle *CreatePickle() = 0;
    virtual Onions *CreateOnions() = 0;
    virtual Ketchup *CreateKetchup() = 0;
    virtual Mustard *CreateMustard() = 0;
};

class BurgerKingBurgerIngredientsFactory : public BurgerIngredientsFactory {
public:
    BurgerKingBurgerIngredientsFactory() {}
    virtual ~BurgerKingBurgerIngredientsFactory() {}
    
    virtual Bun *CreateBun() {
        return new SesameSeedBun();
    }
    virtual Pattie *CreatePattie() {
        return new FlameBroiledPattie();
    }
    virtual Pickle *CreatePickle() {
        return new SweetPickles();
    }
    virtual Onions *CreateOnions() {
        return new NoOnions();
    }
    virtual Ketchup *CreateKetchup() {
        return new HeinzKetchup();
    }
    virtual Mustard *CreateMustard() {
        return new HeinzMustard();
    }
};

class McDonaldsBurgerIngredientsFactory : public BurgerIngredientsFactory {
public:
    McDonaldsBurgerIngredientsFactory() {}
    virtual ~McDonaldsBurgerIngredientsFactory() {}
    
    virtual Bun *CreateBun() {
        return new SeedlessBun();
    }
    virtual Pattie *CreatePattie() {
        return new GrilledPattie();
    }
    virtual Pickle *CreatePickle() {
        return new SourDillPickles();
    }
    virtual Onions *CreateOnions() {
        return new WhiteOnions();
    }
    virtual Ketchup *CreateKetchup() {
        return new McDonaldsKetchup();
    }
    virtual Mustard *CreateMustard() {
        return new McDonaldsMustard();
    }
};

class Burger {
public:
    virtual ~Burger() {}
    virtual void Prepare() = 0;
};

class BurgerKingBurger : public Burger {
public:
    BurgerKingBurger(BurgerIngredientsFactory *factory) : m_Bun(factory->CreateBun()),
                                                          m_Pattie(factory->CreatePattie()),
                                                          m_Pickles(factory->CreatePickle()),
                                                          m_Onions(factory->CreateOnions()),
                                                          m_Ketchup(factory->CreateKetchup()),
                                                          m_Mustard(factory->CreateMustard()) {}
    virtual ~BurgerKingBurger() {}
    virtual void Prepare() {
        cout << "Preparing Burger King Burger\n";
        m_Bun->Prepare();
        m_Pattie->Prepare();
        m_Pickles->Prepare();
        m_Onions->Prepare();
        m_Ketchup->Prepare();
        m_Mustard->Prepare();
    }
private:
    Bun *m_Bun;
    Pattie *m_Pattie;
    Pickle *m_Pickles;
    Onions *m_Onions;
    Ketchup *m_Ketchup;
    Mustard *m_Mustard;
};

class McDonaldsBurger : public Burger {
public:
    McDonaldsBurger(BurgerIngredientsFactory *factory) : m_Bun(factory->CreateBun()),
                                                          m_Pattie(factory->CreatePattie()),
                                                          m_Pickles(factory->CreatePickle()),
                                                          m_Onions(factory->CreateOnions()),
                                                          m_Ketchup(factory->CreateKetchup()),
                                                          m_Mustard(factory->CreateMustard()) {}
    virtual ~McDonaldsBurger() {}
    virtual void Prepare() {
        cout << "Preparing McDonalds Burger\n";
        m_Bun->Prepare();
        m_Pattie->Prepare();
        m_Pickles->Prepare();
        m_Onions->Prepare();
        m_Ketchup->Prepare();
        m_Mustard->Prepare();
    }
private:
    Bun *m_Bun;
    Pattie *m_Pattie;
    Pickle *m_Pickles;
    Onions *m_Onions;
    Ketchup *m_Ketchup;
    Mustard *m_Mustard;
};

int main() {
    BurgerIngredientsFactory *factory = new BurgerKingBurgerIngredientsFactory();
    Burger *burger = new BurgerKingBurger(factory);
    burger->Prepare();
    delete burger;
    delete factory;
    cout << "\n";
    
    factory = new McDonaldsBurgerIngredientsFactory();
    burger = new McDonaldsBurger(factory);
    burger->Prepare();

    delete burger;
    delete factory;
}

/************************************************************************/
/************  Smart Pointer Version **************/
/************************************************************************/
#include <iostream>
#include <memory>

using namespace std;

class Bun {
public:
    virtual ~Bun() {}
    virtual void Prepare() = 0;
};

class Pattie {
public:
    virtual ~Pattie() {}
    virtual void Prepare() = 0;
};

class Pickle {
public:
    virtual ~Pickle() {}
    virtual void Prepare() = 0;
};

class Onions {
public:
    virtual ~Onions() {}
    virtual void Prepare() = 0;
};

class Ketchup {
public:
    virtual ~Ketchup() {}
    virtual void Prepare() = 0;
};

class Mustard {
public:
    virtual ~Mustard() {}
    virtual void Prepare() = 0;
};

class SesameSeedBun : public Bun {
public:
    SesameSeedBun() {}
    virtual ~SesameSeedBun() {}
    virtual void Prepare() {
        cout << "Preparing Sesame Seed Bun.\n";
    }
};

class SeedlessBun : public Bun {
public:
    SeedlessBun() {}
    virtual ~SeedlessBun() {}
    virtual void Prepare() {
        cout << "Preparing Seedless Bun.\n";
    }
};

class FlameBroiledPattie : public Pattie {
public:
    FlameBroiledPattie() {}
    virtual ~FlameBroiledPattie() {}
    virtual void Prepare() {
        cout << "Preparing Flame Broiled Burger.\n";
    }
};

class GrilledPattie : public Pattie {
public:
    GrilledPattie() {}
    virtual ~GrilledPattie() {}
    virtual void Prepare() {
        cout << "Preparing Grilled Pattie.\n";
    }
};

class SweetPickles : public Pickle {
public:
    SweetPickles() {}
    virtual ~SweetPickles() {}
    virtual void Prepare() {
        cout << "Preparing Sweet Pickles.\n";
    }
};

class SourDillPickles : public Pickle {
public:
    SourDillPickles() {}
    virtual ~SourDillPickles() {}
    virtual void Prepare() {
        cout << "Preparing Sour Dill Pickles.\n";
    }
};

class NoOnions : public Onions {
public:
    NoOnions() {}
    virtual ~NoOnions() {}
    virtual void Prepare() {
        // do nothing
    }
};

class WhiteOnions : public Onions {
public:
    WhiteOnions() {}
    virtual ~WhiteOnions() {}
    virtual void Prepare() {
        cout << "Preparing White Onions.\n";
    }
};

class HeinzKetchup : public Ketchup {
public:
    HeinzKetchup() {}
    virtual ~HeinzKetchup() {}
    virtual void Prepare() {
        cout << "Preparing heinx Ketchup.\n";
    }
};

class McDonaldKetchup : public Ketchup {
public:
    McDonaldKetchup() {}
    virtual ~McDonaldKetchup() {}
    virtual void Prepare() {
        cout << "Preparing McDonalds Ketchup.\n";
    }
};

class HeinzMustard : public Mustard {
public:
    HeinzMustard() {}
    virtual ~HeinzMustard() {}
    virtual void Prepare() {
        cout << "Preparing Heinz Mustard.\n";
    }
};

class McDonaldMustard : public Mustard {
public:
    McDonaldMustard() {}
    virtual ~McDonaldMustard() {}
    virtual void Prepare() {
        cout << "Preparing McDonalds Mustard.\n";
    }
};

class BurgerIngredientFactory {
public:
    virtual ~BurgerIngredientFactory() = default;
    virtual unique_ptr<Bun> CreateBun() = 0;
    virtual unique_ptr<Pattie> CreatePattie() = 0;
    virtual unique_ptr<Pickle> CreatePickle() = 0;
    virtual unique_ptr<Onions> CreateOnions() = 0;
    virtual unique_ptr<Ketchup> CreateKetchup() = 0;
    virtual unique_ptr<Mustard> CreateMustard() = 0;
};

class BurgerKingBurgerIngredientFactory : public BurgerIngredientFactory {
public:
    unique_ptr<Bun> CreateBun() override {
        return make_unique<SesameSeedBun>();
    }
    unique_ptr<Pattie> CreatePattie() override {
        return make_unique<FlameBroiledPattie>();
    }
    unique_ptr<Pickle> CreatePickle() override {
        return make_unique<SweetPickles>();
    }
    unique_ptr<Onions> CreateOnions() override {
        return make_unique<NoOnions>();
    }
    unique_ptr<Ketchup> CreateKetchup() override {
        return make_unique<HeinzKetchup>();
    }
    unique_ptr<Mustard> CreateMustard() override {
        return make_unique<HeinzMustard>();
    }
};

class McDonaldBurgerIngredientFactory : public BurgerIngredientFactory {
public:
    unique_ptr<Bun> CreateBun() override {
        return make_unique<SeedlessBun>();
    }
    unique_ptr<Pattie> CreatePattie() override {
        return make_unique<GrilledPattie>();
    }
    unique_ptr<Pickle> CreatePickle() override {
        return make_unique<SourDillPickles>();
    }
    unique_ptr<Onions> CreateOnions() override {
        return make_unique<WhiteOnions>();
    }
    unique_ptr<Ketchup> CreateKetchup() override {
        return make_unique<McDonaldKetchup>();
    }
    unique_ptr<Mustard> CreateMustard() override {
        return make_unique<McDonaldMustard>();
    }
};

class Burger {
public:
    virtual ~Burger() {}
    virtual void Prepare() = 0;
};

class BurgerKingBurger : public Burger {
    unique_ptr<Bun> m_Bun;
    unique_ptr<Pattie> m_Pattie;
    unique_ptr<Pickle> m_Pickles;
    unique_ptr<Onions> m_Onions;
    unique_ptr<Ketchup> m_Ketchup;
    unique_ptr<Mustard> m_Mustard;
public:
    BurgerKingBurger(BurgerIngredientFactory& factory) : m_Bun(factory.CreateBun()),
                                                         m_Pattie(factory.CreatePattie()),
                                                         m_Pickles(factory.CreatePickle()),
                                                         m_Onions(factory.CreateOnions()),
                                                         m_Ketchup(factory.CreateKetchup()),
                                                         m_Mustard(factory.CreateMustard()) {}
    virtual ~BurgerKingBurger() {}
    virtual void Prepare() {
        cout << "Preparing Burger King Burger.\n";
        m_Bun->Prepare();
        m_Pattie->Prepare();
        m_Pickles->Prepare();
        m_Onions->Prepare();
        m_Ketchup->Prepare();
        m_Mustard->Prepare();
    }
};

class McDonaldBurger : public Burger {
    unique_ptr<Bun> m_Bun;
    unique_ptr<Pattie> m_Pattie;
    unique_ptr<Pickle> m_Pickles;
    unique_ptr<Onions> m_Onions;
    unique_ptr<Ketchup> m_Ketchup;
    unique_ptr<Mustard> m_Mustard;
public:
    McDonaldBurger(BurgerIngredientFactory& factory) : m_Bun(factory.CreateBun()),
                                                       m_Pattie(factory.CreatePattie()),
                                                       m_Pickles(factory.CreatePickle()),
                                                       m_Onions(factory.CreateOnions()),
                                                       m_Ketchup(factory.CreateKetchup()),
                                                       m_Mustard(factory.CreateMustard()) {}
    virtual ~McDonaldBurger() {}
    virtual void Prepare() {
        cout << "Preparing McDonalds Burger.\n";
        m_Bun->Prepare();
        m_Pattie->Prepare();
        m_Pickles->Prepare();
        m_Onions->Prepare();
        m_Ketchup->Prepare();
        m_Mustard->Prepare();
    }
};

int main(int argc, char** argv) {
    {
        auto factory = make_unique<BurgerKingBurgerIngredientFactory>();
        auto burger = make_unique<BurgerKingBurger>(*factory);
        burger->Prepare();
    }
    
    cout << "\n";
    
    {
        auto factory = make_unique<McDonaldBurgerIngredientFactory>();
        auto burger = make_unique<McDonaldBurger>(*factory);
        burger->Prepare();
    }
    
    return 0;
}
