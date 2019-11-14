class Card {
public:
    //friend class Deck;
    string value;
    string suit;
    string getSuit() {
        return suit;
    }
    void setSuit(string suit) {
        this->suit = suit;
    }
    string getValue(){
        return value;
    }
    void setValue(string value){
        this->value = value;
    }
};

class PokerCard : public Card {
public:
    static constexpr uint32_t NUM_CARD = 52;
    enum Suits { DIAMON, HEARTS, CLUBS, SPADES };
    enum Values {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
                        TEN, PRINCE, QUEEN, KING};
};

class UnoCard : public Card {
public:
    static constexpr uint32_t NUM_CARD = 108;
    enum Colors { RED, YELLOW, BLUE, GREEN };
};

class Deck {
public:
    Deck() {
        string Suits[] = {"Diamond", "Hearts", "Clubs", "Spades"};
        string Values[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen"};
        int start = 0;
        for (auto suit : Suits) {
            int i = 0;
            for (; i < 13; i++) {
                card[start+i].suit = suit;
                card[start+i].value = Values[i];
            }
            start = i+1;
        }
    }
    void shuffle() {
        srand(time(0));
        
        for (int i = 0; i < 52; i++) {
            int index = rand() % 52;
            swapCard(i, index);
        }
    };
    void displayDeck();
    Card draw(uint32_t index) {
        if (index > 52)
            return card[0];
        return card[index];
    }
private:
    Card card[52];
    void swapCard(int first_card, int second_card) {
        Card tmp = card[first_card];
        card[first_card] = card[second_card];
        card[second_card] = tmp;
    }
};


int main() {
    //Card card();
    Deck deck;
    deck.shuffle();
    Card  card = deck.draw(8);
    cout << card.suit << endl;
    cout << card.value << endl;
}
