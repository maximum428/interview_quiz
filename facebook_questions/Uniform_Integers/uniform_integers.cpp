#include <iostream>

using namespace std;

int getUniformIntegerCountInInterval(long long A, long long B) {
  int count = 0;
  for (int i = 1; i < 10; i++) {
     int num = i;
     while (num <= B) {
        if (num >= A) {
           count++;
        }
        num = num * 10 + i;
     }
  }
  return count;
}

int main() {
  cout << getUniformIntegerCountInInterval(75, 300) << endl;
  return 0;
}
