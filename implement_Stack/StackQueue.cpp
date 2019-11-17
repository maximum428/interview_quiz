#include <iostream>

using namespace std;

template<typename T>
class MyQueue {
public:
    void push(T val) {
        q.push_back(val);
    }
    void pop() {
        if (q.size() == 0) return;
        q.erase(q.begin());
    }
    int size() {
        return q.size();
    }
    T front() {
        if (q.size() == 0) return NULL;
        return q[0];
    }
    bool empty() {
        if (q.size() == 0) return true;
        return false;
    }
    void remove(T t) {
        if (q.size() == 0) return;
        typename vector<T>::iterator it = find(q.begin(), q.end(), t);
        if (it != q.end())
            q.erase(it);
    }
private:
    vector<T> q;
};

template<typename T>
class MyStack {
public:
    void push(T val) {
        typename vector<T>::iterator it = stk.begin();
        stk.insert(it, val);
    }
    void pop() {
        stk.erase(stk.begin());
    }
    bool empty() {
        if (stk.size() == 0) return true;
        return false;
    }
    int size() {
        return stk.size();
    }
    T top() {
        return stk[0];
    }
    void remove(T t) {
        if (stk.size() == 0) return;
        typename vector<T>::iterator it = find(stk.begin(), stk.end(), t);
        if (it != stk.end())
            stk.erase(it);
    }
private:
    vector<T> stk;
};

int main() {    
    MyQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.remove(2);
    auto n = q.front();
    cout << n << endl;
    q.pop();
    cout << q.size() << endl;
    
    MyStack<int> stk;
    stk.push(4);
    stk.push(5);
    stk.push(6);
    auto i = stk.top();
    stk.pop();
    cout << i << endl;
    cout << stk.size() << endl;
}
