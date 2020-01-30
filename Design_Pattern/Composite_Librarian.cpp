/*
The Composite Pattern allows you to compose objects into tree structures to represent part-whole hierarchies. 
Composite lets clients treat individual objects and compositions of objects uniformly.
*/

#include <iostream>

using namespace std;

class BookComponent {
public:
    BookComponent() {}
    virtual ~BookComponent() {}
    virtual void Add(BookComponent *newComponent) {}
    virtual void Remove(BookComponent *newComponent) {}
    virtual void DisplayInfo() = 0;
};

class Book : public BookComponent {
public:
    Book(std::string title, std::string author) : m_title(title), m_author(author) {}
    virtual ~Book() {}
    virtual void DisplayInfo() {
        cout << "Book : " << m_title << " by " << m_author << endl;
    }
private:
    std::string m_title;
    std::string m_author;
};

class BookGroup : public BookComponent {
public:
    BookGroup(string groupName) : m_groupName(groupName) {}
    void Add(BookComponent *newComponent) {
        m_bookComponents.push_back(newComponent);
    }
    void Remove(BookComponent *componentToRemove) {
        vector<BookComponent*>::iterator pos;
        
        for (pos = m_bookComponents.begin(); pos != m_bookComponents.end(); ++pos) {
            if (*pos == componentToRemove) {
                m_bookComponents.erase(pos);
                break;
            }
        }
    }
    void DisplayInfo(){
        static string spaces;
        cout << "Group : " << m_groupName << endl;
        spaces += string("    ");
        
        vector<BookComponent*>::iterator pos;
        for (pos = m_bookComponents.begin(); pos != m_bookComponents.end(); pos++) {
            cout << spaces;
            BookComponent *bookComponent = *pos;
            bookComponent->DisplayInfo();
        }
        spaces.pop_back();
        spaces.pop_back();
        spaces.pop_back();
        spaces.pop_back();
    }
private:
    string m_groupName;
    vector<BookComponent*> m_bookComponents;
};

class Librarian {
public:
    Librarian() : m_BookCollection(new BookGroup(string("Book Collection"))) {
        BuildBookCollection();
    }
    virtual ~Librarian() {
        delete m_BookCollection;
    }
    void DisplayBookCollection() {
        m_BookCollection->DisplayInfo();
    }
private:
    void BuildBookCollection() {
        AddBookToGroup(m_BookCollection, string("Merriam-Webster's Collegiate Dictionary"),
                                         string("Merriam-Webster"));
        m_BookCollection->Add(BuildFictionGroup());
        m_BookCollection->Add(BuildNonfictionGroup());
    }
    BookComponent *BuildFictionGroup() {
        BookComponent *fictionGroup = new BookGroup(string("Fiction"));
        fictionGroup->Add(BuildKidsGroup());
        return fictionGroup;
    }
    BookComponent *BuildNonfictionGroup() {
        BookComponent *nonfictionGroup = new BookGroup(string("Nonfiction"));
        nonfictionGroup->Add(BuildBiographyGroup());
        return nonfictionGroup;
    }
    BookComponent *BuildKidsGroup() {
        BookComponent *kidsGroup = new BookGroup(string("Kids"));
        AddBookToGroup(kidsGroup, string("Green Eggs and Ham"), string("Dr. Suess"));
        kidsGroup->Add(BuildKidsAges3To5Group());
        return kidsGroup;
    }
    BookComponent *BuildKidsAges3To5Group() {
        BookComponent *kidsAges3To5Group = new BookGroup(string("Kids (Ages 3-5)"));
        AddBookToGroup(kidsAges3To5Group, string("Goodnight Moon"), string("Margaret Wise Brown"));
        return kidsAges3To5Group;
    }
    BookComponent *BuildBiographyGroup() {
        BookComponent *biographyGroup = new BookGroup(string("Biography"));
        AddBookToGroup(biographyGroup, string("teve Jobs"), string("Walter Isaacson"));
        return biographyGroup;
    }
    
    void AddBookToGroup(BookComponent *group, string title, string author) {
        BookComponent *book = new Book(title, author);
        group->Add(book);
    }
    BookComponent *m_BookCollection;
};

int main() {
    Librarian librarian;
    librarian.DisplayBookCollection();
}
