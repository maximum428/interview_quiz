#include <iostream>
using namespace std;
template<typename T>
class MySharedPtr {
public:
   MySharedPtr(T *p = NULL) {
      ptr = p;
      count = new int(1);
   }
   MySharedPtr(const MySharedPtr<T> &p) {
      ptr = p.ptr;
      *(p.count) = *(p.count) + 1;
      count = p.count;
   }
   MySharedPtr& operator=(MySharedPtr<T> &p) {
      ptr = p.ptr;
      *(p.count) = *(p.count) + 1;
      count = p.count;
      return *this;
   }
   ~MySharedPtr() {
      (*count)--;
      if (*count == 0) {
         cout << "delete .... " << endl;
         delete(ptr);
         delete(count);
      }
   }
private:
   T *ptr;
   int *count;
};
int main() {
   MySharedPtr<int> myptr(new int(10));
   MySharedPtr<int> a(myptr);
   MySharedPtr<int> b;
   b = myptr;
}
