#include <iostream>
#include <memory>

using namespace std;

class Resource {
public:
    Resource(int id) : m_id(id) {
        cout << "Resourcee " << m_id << " acquired\n";
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
    // Create a unique_ptr
    unique_ptr ptr = make_unique<Resource>(1);
    
    ptr->use();
    
    // Transfer ownership (move semantics)
    unique_ptr ptr2 = move(ptr);
    if (!ptr) {
        cout << "ptr no longer owns the resource\n";
    }
    ptr2->use();
    
    // Resource is automatically destroyed when ptr2 goes out of scope
    return 0;
}
