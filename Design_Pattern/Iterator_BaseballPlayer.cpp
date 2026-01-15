/*
The Iterator Pattern provides a way to access the elements of an aggregate object sequentially without exposing 
its underlying representation.

先用白話講（直覺版）

👉 Iterator Pattern 讓你「一個一個地」走訪集合裡的元素，
而且不用知道這個集合內部到底是怎麼存資料的。

你只需要知道：

給我下一個
我走完了沒？
現在是誰？


你不需要知道：

是 vector 還是 array

是 linked list 還是 tree

index 怎麼算

指標怎麼移

最重要的一張圖（一定要會畫）
Client
  │
  │   next() / hasNext()
  ▼
Iterator  ───────────────►  Aggregate
 (游標)                     (集合本體)
                             ┌─────────────┐
                             │  [ ? ? ? ]  │
                             │  array      │
                             │  list       │
                             │  tree       │
                             └─────────────┘


🧠 關鍵畫面感

Client 只碰 Iterator

Iterator 偷偷幫你走集合

Aggregate 的內部結構 完全被藏起來

三、角色拆解圖（面試加分）
        +------------------+
        |   Iterator       |◄───────+
        |------------------|        |
        | hasNext()        |        |
        | next()           |        |
        +------------------+        |
                 ▲                  |
                 |                  |
     +--------------------+   +--------------------+
     | ConcreteIterator   |   | ConcreteAggregate  |
     |--------------------|   |--------------------|
     | currentIndex       |──►| data structure     |
     +--------------------+   +--------------------+

角色意義（白話）

Aggregate：資料本體（容器）

Iterator：走資料的人

Client：只跟 Iterator 說話的人

四、生活例子（超好背）📺
例子：看電視
電視（Aggregate）
   ├─ HDMI
   ├─ YouTube
   ├─ Netflix
   ├─ News


你拿到的是：

遙控器（Iterator）


你只會：

下一台

有沒有下一台？

現在在看哪一台？

👉 你完全不需要知道電視裡怎麼存頻道
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::string_literals;

#define MAX_SIZE_ARRAY 10

template<class Item>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Item CurrentItem() const = 0;
};

template<class Item>
class List {
public:
    virtual ~List() {}
    virtual Iterator<Item> *CreateIterator() const = 0;
    virtual unsigned int Count() const             = 0;
    virtual void Append(Item item)                 = 0;
    virtual const Item& Get(unsigned int idnex) const = 0;
};

template<class Item>
class StdVectorList : public List<Item> {
    vector<Item> m_vector;
public:
    StdVectorList() {}
    virtual ~StdVectorList() {}
    virtual Iterator<Item> *CreateIterator() const; /* {
        return new StdVectorListIterator<Item>(this);
    }*/
    virtual unsigned int Count() const {
        return m_vector.size();
    }
    virtual void Append(Item item) {
        m_vector.push_back(item);
    }
    virtual const Item& Get(unsigned int index) const {
        return m_vector.at(index);
    }
};

template<class Item>
class StdVectorListIterator : public Iterator<Item> {
    unsigned int m_index;
    const StdVectorList<Item> *m_List;
public:
    StdVectorListIterator(const StdVectorList<Item> *list) : m_List(list), m_index(0) {}
    virtual ~StdVectorListIterator() {}
    virtual void First() { m_index = 0; }
    virtual void Next() { m_index++; }
    virtual bool IsDone() const {
        return (m_List->Count() <= m_index);
    }
    virtual Item CurrentItem() const {
        if (IsDone())
            return Item();
        return m_List->Get(m_index);
    }
};

template<class Item>
Iterator<Item> *StdVectorList<Item>::CreateIterator() const {
    return new StdVectorListIterator<Item>(this);
}

template<class Item>
class ArrayListIterator : public Iterator<Item> {
    const List<Item> *m_List;
    unsigned int m_index;
public:
    ArrayListIterator(const List<Item> *list) : m_List(list), m_index(0) {}
    virtual ~ArrayListIterator() {}
    virtual void First() { m_index = 0; }
    virtual void Next() { m_index++; }
    virtual bool IsDone() const {
        return (m_List->Count() <= m_index);
    }
    virtual Item CurrentItem() const {
        if (IsDone())
            return Item();
        return m_List->Get(m_index);
    }
};

template<class Item>
class ArrayList : public List<Item> {
    Item m_array[MAX_SIZE_ARRAY];
    unsigned int m_currentSize;
public:
    ArrayList() : m_currentSize(0) {}
    virtual ~ArrayList() {}
    virtual Iterator<Item> *CreateIterator() const {
        return new ArrayListIterator<Item>(this);
    }
    virtual unsigned int Count() const {
        return m_currentSize;
    }
    virtual void Append(Item item) {
        if (m_currentSize < MAX_SIZE_ARRAY) {
            m_array[m_currentSize] = item;
            m_currentSize++;
        }
    }
    virtual const Item& Get(unsigned int index) const {
        return m_array[index];
    }
};

class BaseballPlayer {
    string m_name, m_position;
    char m_swingType;
public:
    BaseballPlayer(string name, string position, char swingType) : m_name(name), m_position(position), m_swingType(swingType) {}
    BaseballPlayer() : m_swingType('\0') {}
    virtual ~BaseballPlayer() {}
    string GetName() const {
        return m_name;
    }
    string GetPosition() const {
        return m_position;
    }
    char GetSwingType() const {
        return m_swingType;
    }
};

std::ostream& operator<<(std::ostream& outc, const BaseballPlayer& player) {
    string tabsAfterName = (player.GetName().size() >= 16) ? "\t"s : "\t\t"s;
    outc << player.GetPosition() << "\t"
         << player.GetName() << tabsAfterName
         << player.GetSwingType();
    return outc;
}

List<BaseballPlayer> *MakeNewYorkmetsLineup() {
    List<BaseballPlayer> *NewYorkMetsLineup = new StdVectorList<BaseballPlayer>();
    NewYorkMetsLineup->Append(BaseballPlayer("Curtis Granderson", "CF", 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer("Asdrubal Cabrera", "SS", 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer("Yoenis Cespedes", "LF", 'R'));
    NewYorkMetsLineup->Append(BaseballPlayer("Jay Bruce", "RF", 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer("Neil Walker", "2B", 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer("Lucas Duda", "1B", 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer("Travis d'Arnaud", "C", 'R'));
    NewYorkMetsLineup->Append(BaseballPlayer("Jose Reyes", "SS", 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer("Noah Syndergaard", "P", 'L'));
    return NewYorkMetsLineup;
}

List<BaseballPlayer> *MakeWashingtonnationalsLineup() {
    List<BaseballPlayer> *WashingtonNationalsLineup = new ArrayList<BaseballPlayer>();
    WashingtonNationalsLineup->Append(BaseballPlayer("Adam Eaton", "F", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Wilmer Difo", "SS", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Daniel Murphy", "2B", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Bryce Harper", "RF", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Ryan Zimmerman", "1B", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Anthony Rendon", "3B", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Matt Wieters", "C", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Michael Taylor", "CF", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Stephen Strasburg", "P", 'S'));
    return WashingtonNationalsLineup;
}

void PrintLineup(string lineupName, Iterator<BaseballPlayer> *iterator) {
    cout << lineupName << "\n";
    unsigned int lineupPosition = 1;
    
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        cout << lineupPosition++ << ". " << iterator->CurrentItem() << "\n";
    }
    cout << "\n";
}

int main(int argc, char** argv) {
    List<BaseballPlayer> *newYorkMetsLineup = MakeNewYorkmetsLineup();
    Iterator<BaseballPlayer> *newYorkMetsLineupIterator = newYorkMetsLineup->CreateIterator();
    PrintLineup("New York Mets Lineup", newYorkMetsLineupIterator);
    delete newYorkMetsLineupIterator;
    delete newYorkMetsLineup;
    
    List<BaseballPlayer> *washingtonNationalsLineup = MakeWashingtonnationalsLineup();
    Iterator<BaseballPlayer> *washingtonNationalsLineupIterator = washingtonNationalsLineup->CreateIterator();
    PrintLineup("Washington Nationals Lineup", washingtonNationalsLineupIterator);
    delete washingtonNationalsLineupIterator;
    delete washingtonNationalsLineup;
    
    return 0;
    
}


/****************************************************************************************
******************************** Smart Pointer Version **********************************
*****************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
using namespace std::string_literals;

#define MAX_SIZE_ARRAY 10

template<class Item>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Item CurrentItem() const = 0;
};

template<class Item>
class List {
public:
    virtual ~List() = default;
    virtual unique_ptr<Iterator<Item>> CreateIterator() const = 0;
    virtual unsigned int Count() const             = 0;
    virtual void Append(Item item)                 = 0;
};

template<class Item>
class StdVectorListIterator;

template<class Item>
class StdVectorList : public List<Item> {
    vector<Item> m_vector;
public:
    unique_ptr<Iterator<Item>> CreateIterator() const override {
        return make_unique<StdVectorListIterator<Item>>(this);
    }
    unsigned int Count() const override {
        return m_vector.size();
    }
    void Append(Item item) override {
        m_vector.push_back(item);
    }
    const Item& Get(unsigned int index) const {
        return m_vector.at(index);
    }
};

template<class Item>
class StdVectorListIterator : public Iterator<Item> {
    unsigned int m_index{0};
    const StdVectorList<Item> *m_List;
public:
    StdVectorListIterator(const StdVectorList<Item> *list) : m_List(list) {}
    void First() override { m_index = 0; }
    void Next() override { m_index++; }
    bool IsDone() const override {
        return (m_List->Count() <= m_index);
    }
    Item CurrentItem() const override {
        return IsDone() ? Item() : m_List->Get(m_index);
    }
};

template<class item>
class ArrayList;

template<class Item>
class ArrayListIterator : public Iterator<Item> {
    const ArrayList<Item> *m_List;
    unsigned int m_index{0};
public:
    ArrayListIterator(const ArrayList<Item> *list) : m_List(list) {}
    void First() override { m_index = 0; }
    void Next() override { m_index++; }
    bool IsDone() const override {
        return (m_List->Count() <= m_index);
    }
    Item CurrentItem() const override {
        return IsDone() ? Item() : m_List->Get(m_index);
    }
};

template<class Item>
class ArrayList : public List<Item> {
    Item m_array[MAX_SIZE_ARRAY];
    unsigned int m_currentSize{0};
public:
    unique_ptr<Iterator<Item>> CreateIterator() const override {
        return make_unique<ArrayListIterator<Item>>(this);
    }
    unsigned int Count() const override {
        return m_currentSize;
    }
    void Append(Item item) override {
        if (m_currentSize < MAX_SIZE_ARRAY) {
            m_array[m_currentSize++] = item;
        }
    }
    const Item& Get(unsigned int index) const {
        return m_array[index];
    }
};

class BaseballPlayer {
    string m_name, m_position;
    char m_swingType;
public:
    BaseballPlayer(string name, string position, char swingType) : m_name(name), m_position(position), m_swingType(swingType) {}
    BaseballPlayer() : m_swingType('\0') {}
    virtual ~BaseballPlayer() {}
    string GetName() const {
        return m_name;
    }
    string GetPosition() const {
        return m_position;
    }
    char GetSwingType() const {
        return m_swingType;
    }
};

std::ostream& operator<<(std::ostream& outc, const BaseballPlayer& player) {
    string tabsAfterName = (player.GetName().size() >= 16) ? "\t"s : "\t\t"s;
    outc << player.GetPosition() << "\t"
         << player.GetName() << tabsAfterName
         << player.GetSwingType();
    return outc;
}

List<BaseballPlayer> *MakeNewYorkmetsLineup() {
    List<BaseballPlayer> *NewYorkMetsLineup = new StdVectorList<BaseballPlayer>();
    NewYorkMetsLineup->Append(BaseballPlayer("Curtis Granderson", "CF", 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer("Asdrubal Cabrera", "SS", 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer("Yoenis Cespedes", "LF", 'R'));
    NewYorkMetsLineup->Append(BaseballPlayer("Jay Bruce", "RF", 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer("Neil Walker", "2B", 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer("Lucas Duda", "1B", 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer("Travis d'Arnaud", "C", 'R'));
    NewYorkMetsLineup->Append(BaseballPlayer("Jose Reyes", "SS", 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer("Noah Syndergaard", "P", 'L'));
    return NewYorkMetsLineup;
}

List<BaseballPlayer> *MakeWashingtonnationalsLineup() {
    List<BaseballPlayer> *WashingtonNationalsLineup = new ArrayList<BaseballPlayer>();
    WashingtonNationalsLineup->Append(BaseballPlayer("Adam Eaton", "F", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Wilmer Difo", "SS", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Daniel Murphy", "2B", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Bryce Harper", "RF", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Ryan Zimmerman", "1B", 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Anthony Rendon", "3B", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Matt Wieters", "C", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Michael Taylor", "CF", 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer("Stephen Strasburg", "P", 'S'));
    return WashingtonNationalsLineup;
}

void PrintLineup(const string& lineupName, unique_ptr<Iterator<BaseballPlayer>> iterator) {
    cout << lineupName << "\n";
    unsigned int lineupPosition = 1;
    
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        cout << lineupPosition++ << ". " << iterator->CurrentItem() << "\n";
    }
    cout << "\n";
}

int main(int argc, char** argv) {
    auto newYorkMetsLineup = MakeNewYorkmetsLineup();
    PrintLineup("New York Mets Lineup", newYorkMetsLineup->CreateIterator());
    
    auto washingtonNationalsLineup = MakeWashingtonnationalsLineup();
    PrintLineup("Washington Nationals Lineup", washingtonNationalsLineup->CreateIterator());
    
    return 0;
    
}
