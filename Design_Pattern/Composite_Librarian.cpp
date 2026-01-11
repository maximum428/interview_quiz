/*
The Composite Pattern allows you to compose objects into tree structures to represent part-whole hierarchies. 
Composite lets clients treat individual objects and compositions of objects uniformly.

一、白話翻譯（先懂意思）

Composite Pattern 讓你把物件組合成樹狀結構，用來表示「部分–整體」的關係。
它讓使用者可以用「同一種方式」對待單一物件與由多個物件組成的集合。

簡單說就是：

👉 「一個東西」和「一堆東西」看起來是一樣的

二、什麼是「part–whole hierarchy」？

意思是這種結構：

整體
 ├── 部分
 │    ├── 子部分
 │    └── 子部分
 └── 部分


實際例子：

| 領域       | 整體       | 部分          |
| --------- | ---------  | ------------ |
| 檔案系統   | 資料夾      | 檔案 / 子資料夾 |
| UI        | 視窗       | 按鈕、Panel    |
| 書籍      | 書櫃        | 書、分類       |
| 組織      | 部門        | 員工          |

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


/*****************************************************************************************
***************************** Smart Pointer Version *********************************
******************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;
using namespace std::string_literals;

class BookComponent {
public:
    virtual ~BookComponent() = default;
    virtual void Add(unique_ptr<BookComponent> newComponent) {}
    virtual void Remove(BookComponent *newComponent) {}
    virtual void DisplayInfo() = 0;
};

class Book : public BookComponent {
    string m_title, m_author;
public:
    Book(string title, string author) : m_title(move(title)), m_author(move(author)) {}
    virtual void DisplayInfo() override {
        cout << "Book : " << m_title << " by " << m_author << endl;
    }
};

class BookGroup : public BookComponent {
    string m_groupName;
    vector<unique_ptr<BookComponent>> m_bookComponents;
public:
    BookGroup(string groupName) : m_groupName(move(groupName)) {}
    void Add(unique_ptr<BookComponent> newComponent) override {
        m_bookComponents.push_back(move(newComponent));
    }
    void Remove(BookComponent *componentToRemove) override {
        m_bookComponents.erase(
            remove_if(
                m_bookComponents.begin(),
                m_bookComponents.end(),
                [&](const unique_ptr<BookComponent>& ptr) {
                    return ptr.get() == componentToRemove;
                }),
            m_bookComponents.end());
    }
    void DisplayInfo() {
        static string spaces;
        cout << "Group : " << m_groupName << endl;
        spaces += "    "s;
        
        for (const auto& component : m_bookComponents) {
            cout << spaces;
            component->DisplayInfo();
        }
        spaces.resize(spaces.size() - 4);
    }
};

class Librarian {
    unique_ptr<BookComponent> m_BookCollection;
    void BuildBookCollection() {
        AddBookToGroup(m_BookCollection.get(), "Merrian-Webster's Collegiate Dictionary"s, "Merrian-Webster"s);
        m_BookCollection->Add(BuildFictionGroup());
        m_BookCollection->Add(BuildNonfictionGroup());
    }
    unique_ptr<BookComponent> BuildFictionGroup() {
        auto fictionGroup = make_unique<BookGroup>("Fiction"s);
        fictionGroup->Add(BuildKidsGroup());
        return fictionGroup;
    }
    unique_ptr<BookComponent> BuildNonfictionGroup() {
        auto nonfictionGroup = make_unique<BookGroup>("Nonfiction"s);
        nonfictionGroup->Add(BuildBiographyGroup());
        return nonfictionGroup;
    }
    unique_ptr<BookComponent> BuildKidsGroup() {
        auto kidsGroup = make_unique<BookGroup>("Kids"s);
        AddBookToGroup(kidsGroup.get(), "Green Eggs and Ham"s, "Dr. Suess"s);
        kidsGroup->Add(BuildKidsAge3To5Group());
        return kidsGroup;
    }
    unique_ptr<BookComponent> BuildKidsAge3To5Group() {
        auto kidsAges3To5Group = make_unique<BookGroup>("Kids (Ages 3-5)"s);
        AddBookToGroup(kidsAges3To5Group.get(), "Goodnight Moon"s, "Margaret Wise Brown"s);
        return kidsAges3To5Group;
    }
    unique_ptr<BookComponent> BuildBiographyGroup() {
        auto biographyGroup = make_unique<BookGroup>("Biography"s);
        AddBookToGroup(biographyGroup.get(), "Steve Jobs", "Walter Isaacson"s);
        return biographyGroup;
    }
    void AddBookToGroup(BookComponent *group, const string& title, const string& author) {
        group->Add(make_unique<Book>(title, author));
    }
public:
    Librarian() : m_BookCollection(make_unique<BookGroup>("Book Coolection"s)) {
        BuildBookCollection();
    }
    void DisplayBookCollection() {
        m_BookCollection->DisplayInfo();
    }
};

int main(int argc, char** argv) {
    Librarian librarian;
    librarian.DisplayBookCollection();
    
    return 0;
}
