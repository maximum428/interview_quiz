#include <iostream>
#include <memory>

using namespace std;

class Resource {
public:
    Resource(int id) : m_id(id) {
        cout << "Resource " << m_id << " acquired\n";
    }
    ~Resource() {
        cout << "Resource " << m_id << " destroyed\n";
    }
    void use() const {
        cout << "Using resource " << m_id << endl;
    }
private:
    int m_id;
};

int main() {
    shared_ptr p1 = make_shared<Resource>(1);
    cout << "p1 use_count: " << p1.use_count() << endl;
    
    {
        // Shared ownership
        shared_ptr<Resource> p2 = p1;
        shared_ptr<Resource> p3 = p1;
        
        cout << "After sharing:\n";
        cout << "p1 use_count: " << p1.use_count() << endl;
        
        p1->use();
        p1->use();
    } // p2 and p3 go out of scope here
    
    cout << "After inner scope:\n";
    cout << "p1 use_count: " << p1.use_count() << endl;
    
    p1->use();
    return 0;
}
