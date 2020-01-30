/*
The Iterator Pattern provides a way to access the elements of an aggregate object sequentially without exposing 
its underlying representation.
*/
#include <iostream>

#define MAXSIZEARRAY 10

using namespace std;

template<class Item>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Item CurrentItem() const = 0;
};

template <class Item>
class List {
public:
    virtual Iterator<Item> *CreateIterator() const = 0;
    virtual unsigned int Count() const             = 0;
    virtual void Append(Item item)                 = 0;
};

template<class Item>
class StdVectorList : public List<Item> {
public:
    StdVectorList() {}
    virtual ~StdVectorList() {}
    virtual Iterator<Item> *CreateIterator() const {
        return new StdVectorListIterator<Item>(this);
    }
    virtual unsigned int Count() const {
        return m_vector.size();
    }
    virtual void Append(Item item) {
        m_vector.push_back(item);
    }
    virtual const Item& Get(unsigned int index) const {
        return m_vector.at(index);
    }
private:
    vector<Item> m_vector;
};

template<class Item>
class StdVectorListIterator : public Iterator<Item> {
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
private:
    const StdVectorList<Item> *m_List;
    unsigned int m_index;
};

template <class Item>
class ArrayListIterator : public Iterator<Item> {
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
private:
    const List<Item> *m_List;
    unsigned int m_index;
};

template<class Item>
class ArrayList : public List<Item> {
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
        if (m_currentSize <MAXSIZEARRAY) {
            m_array[m_currentSize] = item;
            m_currentSize++;
        }
    }
    virtual const Item& Get(unsigned int index) const {
        return m_array[index];
    }
private:
    Item m_array[MAXSIZEARRAY];
    unsigned int m_currentSize;
};

class BaseballPlayer {
public:
    BaseballPlayer(string name, string position, char swingType) : m_name(name), 
                                                                   m_position(position),
                                                                   m_swingType(swingType) {}
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
    
private:
    string m_name;
    string m_position;
    char   m_swingType;
};

std::ostream& operator<<(std::ostream& outc, const BaseballPlayer& player) {
    string tabsAfterName = (player.GetName().size() >= 16) ?string("\t") : string("\t\t");
    outc << player.GetPosition() << "\t"
         << player.GetName() << tabsAfterName
         << player.GetSwingType();
    return outc;
}

List<BaseballPlayer> *MakeNewYorkmetsLineup() {
    List<BaseballPlayer> *NewYorkMetsLineup = new StdVectorList<BaseballPlayer>();
    NewYorkMetsLineup->Append(BaseballPlayer(string("Curtis Granderson"), string("CF"), 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Asdrubal Cabrera"), string("SS"), 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Yoenis Cespedes"), string("LF"), 'R'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Jay Bruce"), string("RF"), 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Neil Walker"), string("2B"), 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Lucas Duda"), string("1B"), 'L'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Travis d'Arnaud"), string("C"), 'R'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Jose Reyes"), string("SS"), 'S'));
    NewYorkMetsLineup->Append(BaseballPlayer(string("Noah Syndergaard"), string("P"), 'L'));
    return NewYorkMetsLineup;
}

List<BaseballPlayer> *MakeWashingtonNationalsLineup() {
    List<BaseballPlayer> *WashingtonNationalsLineup = new ArrayList<BaseballPlayer>();
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Adam Eaton"), string("CF"), 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Wilmer Difo"), string("SS"), 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Daniel Murphy"), string("2B"), 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Bryce Harper"), string("RF"), 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Ryan Zimmerman"), string("1B"), 'L'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Anthony Rendon"), string("3B"), 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Matt Wieters"), string("C"), 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Michael Taylor"), string("CF"), 'R'));
    WashingtonNationalsLineup->Append(BaseballPlayer(string("Stephen Strasburg"), string("P"), 'S'));
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
int main() {
    List<BaseballPlayer> *newYorkMetsLineup = MakeNewYorkmetsLineup();
    Iterator<BaseballPlayer> *newYorkMetsLIneupIterator = newYorkMetsLineup->CreateIterator();
    PrintLineup(string("New York Mets Lineup"), newYorkMetsLIneupIterator);
    delete newYorkMetsLIneupIterator;
    delete newYorkMetsLineup;
    
    List<BaseballPlayer> *washingtonNationalsLineup = MakeWashingtonNationalsLineup();
    Iterator<BaseballPlayer> *washingtonNationalsLineupIterator = washingtonNationalsLineup->CreateIterator();
    PrintLineup(string("Washington Nationsl Lineup"), washingtonNationalsLineupIterator);
    delete washingtonNationalsLineupIterator;
    delete washingtonNationalsLineup;
    return 0;
}
