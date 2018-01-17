#include <iostream>
#include <queue>

class MovingAverage {
public:
    MovingAverage(int size) : _size(size) {}
    double next(int val) {
        if (stream.size() == _size) {
            sum -= stream.front();
            stream.pop();
        }
        sum += val;
        stream.push(val);
        return sum / stream.size();
    }
private:
    std::queue<int> stream;
    int _size;
    double sum = 0;
};

int main() {
    MovingAverage ma(3);
    std::cout << "ma.next(1) = " << ma.next(1) << std::endl;
    std::cout << "ma.next(10) = " << ma.next(10) << std::endl;
    std::cout << "ma.next(3) = " << ma.next(3) << std::endl;
    std::cout << "ma.next(5) = " << ma.next(5) << std::endl;
}
