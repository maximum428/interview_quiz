#include <iostream>

using namespace std;

enum class Suit { CLUB, DIAMOND, HEART, SPADE };

struct Card {
    int rank;
    Suit suit;
    
    bool operator<(const Card& other) const {
        if (rank != other.rank) return rank < other.rank;
        return suit < other.suit;
    }
};

string suitToStr(Suit s) {
    switch(s) {
        case Suit::CLUB: return "♣";
        case Suit::DIAMOND: return "♦";
        case Suit::HEART: return "♥";
        case Suit::SPADE: return "♠";
    }
    return "";
};

class PlayStrategy {
public:
    virtual bool isValid(const vector<Card>& cards) = 0;
    virtual bool canBeat(const vector<Card>& curr, const vector<Card>& last) = 0;
    virtual string name() const = 0;
    virtual ~PlayStrategy() = default;
};

class SingleStrategy : public PlayStrategy {
public:
    bool isValid(const vector<Card>& cards) override {
        return cards.size() == 1;
    }
    bool canBeat(const vector<Card>& curr, const vector<Card>& last) override {
        return curr[0] < last[0] == false;
    }
    string name() const override {
        return "Single";
    }
};

class PairStrategy : public PlayStrategy {
public:
    bool isValid(const vector<Card>& cards) override {
        return cards.size() == 2 && cards[0].rank == cards[1].rank;
    }
    bool canBeat(const vector<Card>& curr, const vector<Card>& last) override {
        return curr[0].rank > last[0].rank;
    }
    string name() const override {
        return "Pair";
    }
};

class Player {
    string m_name;
public:
    vector<Card> m_hand;
    Player(string name) : m_name(name) {}
    void showHand() {
        cout << m_name << " hand: ";
        for (const auto& card : m_hand) {
            cout << card.rank << suitToStr(card.suit) << " ";
        }
        cout << "\n";
    }
    void shuffle(vector<Card> cards) {
        m_hand = cards;
    }
    string getName() const {
        return m_name;
    }
};

class BigTwoGame {
    unique_ptr<PlayStrategy> m_strategy;
    vector<Player> m_players;
    vector<Card> m_lastPlay;
public:
    BigTwoGame() {
        m_strategy = make_unique<SingleStrategy>();
    }
    void addPlayer(const Player& p) {
        m_players.push_back(p);
    }
    void setStrategy(unique_ptr<PlayStrategy> strategy) {
        m_strategy = std::move(strategy);
    }
    bool play(int playerIdx, vector<Card> cards) {
        sort(cards.begin(), cards.end());
        
        if (!m_strategy->isValid(cards)) {
            cout << "Invalid play type\n";
            return false;
        }
        if (!m_lastPlay.empty() && !m_strategy->canBeat(cards, m_lastPlay)) {
            cout << "Cannot beat last play\n";
            return false;
        }
        
        m_lastPlay = cards;
        cout << m_players[playerIdx].getName() << " plays " << m_strategy->name() << ": ";
        
        for (auto& card : cards) {
            cout << card.rank << suitToStr(card.suit) << " ";
        }
        cout << endl;
        
        return true;
    }
};

int main() {
    Player alice("Alice");
    Player bob("Bob");
    
    alice.shuffle({
        {3, Suit::CLUB}, {3, Suit::DIAMOND}, {5, Suit::HEART}
    });
    bob.shuffle({
        {4, Suit::CLUB}, {4, Suit::SPADE}, {6, Suit::HEART}
    });
    
    BigTwoGame game;
    game.addPlayer(alice);
    game.addPlayer(bob);
    
    alice.showHand();
    bob.showHand();
    
    game.setStrategy(make_unique<SingleStrategy>());
    game.play(0, {alice.m_hand[0]});
    
    game.play(1, {bob.m_hand[0]});
    
    game.setStrategy(make_unique<PairStrategy>());
    
    game.play(0, {alice.m_hand[0], alice.m_hand[1]});
    
    game.play(1, {bob.m_hand[0], bob.m_hand[1]});
    
    return 0;
}
