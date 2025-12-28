#include <iostream>
#include <memory>

using namespace std;
class B;  // forward declaration

class A {
public:
    shared_ptr<B> b;
    ~A() { cout << "A destroyed\n"; }
};

class B {
public:
    weak_ptr<A> a;  // weak_ptr breaks cycle
    ~B() { cout << "B destroyed\n"; }
};

int main() {
    shared_ptr a = make_shared<A>();
    shared_ptr b = make_shared<B>();
    
    a->b = b;
    b->a = a;  // weak reference
    
    cout << "A use count: " << a.use_count() << endl;
    cout << "B use count: " << b.use_count() << endl;
    
    if (auto sp = b->a.lock()) {
        cout << "A is still alive\n";
    } else {
        cout << "A is destroyed\n";
    }
    
    return 0;
}
