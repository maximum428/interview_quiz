#include <iostream>

using namespace std;

template<typename T>
class MyUniquePtr {
public:
    MyUniquePtr(T *p = NULL) {
        ptr = p;
    }
    MyUniquePtr(const MyUniquePtr<T> &p) {
        ptr = p.ptr;
        p.ptr = nullptr;
    }
    MyUniquePtr& operator=(const MyUniquePtr<T> &p) {
        if (this == &p) return *this;
        ptr = p.ptr;
        return *this;
    }
    ~MyUniquePtr() {
        delete(ptr);
    }
private:
    T *ptr;
};

int main() {
    MyUniquePtr<int> myptr(new int(10));
    MyUniquePtr<int> myptr2 = myptr;
    MyUniquePtr<int> myptr3(myptr2);
    MyUniquePtr<int> myptr4 = MyUniquePtr<int>(new int(5));

    return 0;
}
