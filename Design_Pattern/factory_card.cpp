#include <iostream>

using namespace std;

class Card {
public:
    virtual string dump() { return "Base class"; }
protected:
    string cardtype;
};

class PokerCard : public Card {
public:
    PokerCard() {
        cardtype = "PokerCard";
    }
    void setSuit(string suit) {
        this->suit = suit;
    }
    string getSuit() {
        return suit;
    }
    void setValue(string value) {
        this->value = value;
    }
    string getValue() {
        return value;
    }
private:
    string suit;
    string value;
};

class UnoCard : public Card {
public:
    UnoCard() {
        cardtype = "UnoCard";
    }
    void setColor(string color) {
        this->color = color;
    }
    string getColor() {
        return color;
    }
private:
    string color;
};


class Dock {
public:
    virtual ~Dock() {}
    virtual void shuffle() = 0;
    virtual Card* draw(int index) = 0;
protected:
    int type;
    int num_cards;
};
class Poker : public Dock {
public:
    Poker() {
        type = 0;
        num_cards = 52;
        const string suits[] = {"Diamon", "Hearts", "Clubs", "Sprades"};
        const string values[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Prince", "Queen", "King"};
        for (int i = 0; i < 52; i++) {
            cards[i].setSuit(suits[i % 4]);
            cards[i].setValue(values[i % 13]);
        }
    }
    void shuffle() {
        
    }
    Card* draw(int index) {
        return &cards[index];
    }
private:
    PokerCard cards[52];
};

class Uno : public Dock {
public:
    Uno() {
        type = 1;
        num_cards = 108;
        const string colors[] = {"Red", "Yellow", "Blue", "Green"};
        for (int i = 0; i < 108; i++) 
            cards[i].setColor(colors[i % 4]);
    }
    void shuffle() {
        
    }
    Card* draw(int index) {
        return &cards[index];
    }
private:
    UnoCard cards[108];
};

class Player {
public:
    enum TYPE { POKER, UNO };
    Player(int type = 0) {
        this->type = type;
        switch (type) {
            case POKER:
                pDock = new Poker();
                break;
            case UNO:
                pDock = new Uno();
                break;
            default:
                pDock = NULL;
                cout << "ERROR\n";
        }
    }
    ~Player() {
        if (pDock == NULL) {
            delete(pDock);
            pDock = NULL;
        }
    }
    Dock* getDock() {
        return pDock;
    }
    void shuffle() {
        if (pDock != NULL)
            pDock->shuffle();
    }
    Card* draw(int index) {
        if (pDock != NULL)
            return pDock->draw(index);
        return NULL;
    }
    string getGameName() {
        if (type == POKER)
            return "Poker";
        else if (type == UNO)
            return "Uno";
        else
            return "Unknown";
    }
private:
    int type;
    Dock *pDock;
};

int main() {
    Player player(0);
    player.shuffle();
    Card* card = player.draw(3);
    cout << "Game: " << player.getGameName() << endl;
    if (player.getGameName() == "Poker") {
        PokerCard* pokercard = dynamic_cast<PokerCard*>(card);
        cout << "Suit: " << pokercard->getSuit() << endl;
        cout << "Value: " << pokercard->getValue() << endl;
    } else if (player.getGameName() == "Uno") {
        UnoCard* unocard = dynamic_cast<UnoCard*>(card);
        cout << "Color: " << unocard->getColor() << endl;
    }
}

================================================================================

#include <iostream>
#include <memory>

using namespace std;

class Card {
public:
  virtual string dump() { return "Base class"; }
protected:
  string cardtype;
};

class PokerCard : public Card {
public:
  PokerCard() {
    cardtype = "PokerCard";
  }
  void setSuit(string suit) {
    this->suit = suit;
  }
  string getSuit() {
    return suit;
  }
  void setValue(string value) {
    this->value = value;
  }
  string getValue() {
    return value;
  }
private:
  string suit;
  string value;
};

class UnoCard : public Card {
public:
  UnoCard() {
    cardtype = "UnoCard";
  }
  void setColor(string color) {
    this->color = color;
  }
  string getColor() {
    return color;
  }
private:
  string color;
};

class Dock {
public:
  Dock(int numCards) {
    num_cards = numCards;
  }
  virtual ~Dock() {}
  virtual void shuffle() = 0;
  virtual Card* draw(int index) = 0;
  int getNum_Cards() {
    return num_cards;
  }
protected:
  int type;
  int num_cards;
};

class Poker : public Dock {
public:
  Poker() : Dock(52) {
    type = 0;
    //cards = (PokerCard*)malloc(52 * sizeof(PokerCard));
    cards = make_shared<PokerCard[]>(NUM_CARDS);

    const string suits[] = {"Diaomon", "Hearts", "Clubs", "Sprades"};
    const string values[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Prince", "Queen", "King"};
    for (int i = 0; i < num_cards; i++) {
      cards[i].setSuit(suits[i %4]);
      cards[i].setValue(values[i % 13]);
    }
  }
  void shuffle() override {}

  Card* draw(int index) override {
    return &cards[index];
  }
private:
  static constexpr int NUM_CARDS = 52;
  //PokerCard* cards = new PokerCard[52];
  shared_ptr<PokerCard[]> cards;
};

class Uno : public Dock {
public:
  Uno() : Dock(108) {
    type = 1;
    cards = make_shared<UnoCard[]>(NUM_CARDS);

    const string colors[] = {"Red", "Yellow", "Blue", "Green"};
    for (int i = 0; i < num_cards; i++) {
      cards[i].setColor(colors[i % 4]);
    }
  }
  void shuffle() override {}
    
  Card* draw(int index) override {
    return &cards[index];
  }
private:
  static constexpr int NUM_CARDS = 108;
  shared_ptr<UnoCard[]> cards;
};

class Player {
public:
  enum class TYPE { POKER, UNO, UNDIFINED};

  Player(TYPE type = TYPE::UNDIFINED) {
    _type = type;
    switch (_type) {
      case TYPE::POKER:
        _dock = make_shared<Poker>();
        break;
      case TYPE::UNO:
        _dock = make_shared<Uno>();
        break;
      default:
        _dock = nullptr;
        cout << "ERROR\n";
    }
  }
  shared_ptr<Dock> getDock() {
    return _dock;
  }

  void shuffle() {
    if (_dock != nullptr) {
      _dock->shuffle();
    }
  }

  Card* draw(int index) {
    if (_dock != nullptr) {
      return _dock->draw(index);
    }
    return nullptr;
  }

  string getGameName() {
    if (_type == TYPE::POKER) {
      return "Poker";
    } else if (_type == TYPE::UNO) {
      return "Uno";
    } else {
      return "UNDEFINED";
    }
  }

private:
  TYPE _type;
  shared_ptr<Dock> _dock = nullptr;
};

int main() {
  Player player(Player::TYPE::UNO);
  player.shuffle();
  Card* card = player.draw(3);
  cout << "Game: " << player.getGameName() << endl;
  if (player.getGameName() == "Poker") {
    PokerCard *pokercard = dynamic_cast<PokerCard*>(card);
    cout << "Suit: " << pokercard->getSuit() << endl;
    cout << "Value: " << pokercard->getValue() << endl;
  } else if (player.getGameName() == "Uno") {
    UnoCard* unocard = dynamic_cast<UnoCard*>(card);
    cout << "Color: " << unocard->getColor() << endl;
  }
  return 0;
}
