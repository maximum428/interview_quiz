#include <iostream>
#include <vector>

using namespace std;

class Queue {
public:
    void push(int x) {
        q.push_back(x);
    }
    void pop() {
        if (q.size() == 0)
            return;
        q.erase(q.begin());
    }
    void remove(int x) {
        if (q.size() == 0) return;
        std::vector<int>::iterator it = find(q.begin(), q.end(), x);
        if (it != q.end())
            q.erase(it);
    }
    int top() {
        if (q.size() == 0) return -1;
        return q[0];
    }
    void print() {
        for (auto e : q)
            cout << e << " ";
        cout << "\n";
    }
private:
    vector<int> q;
};

class Stack {
public:
    void push(int x) {
        vector<int>::iterator it = stk.begin();
        stk.insert(it, x);
    }
    void pop() {
        stk.erase(stk.begin());
    }
    void remove(int x) {
        if (stk.size() == 0) return;
        std::vector<int>::iterator it = find(stk.begin(), stk.end(), x);
        if (it != stk.end())
            stk.erase(it);
    }
    void print() {
        for (auto e : stk) {
            cout << e << " ";
        }
        cout << "\n";
    }
private:
    vector<int> stk;
};

int main() {
    Queue queue = Queue();
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.remove(2);
    queue.print();

    Stack stack = Stack();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.remove(2);
    stack.print();
}
