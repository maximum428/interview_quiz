#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void Myswap(string& s1, string& s2) {
  string tmp = s2;
  s2 = s1;
  s1 = tmp;
}
bool one_edit_apart(string s1, string s2) {

  if (s1.length() > s2.length()) {
    Myswap(s1, s2);
  }
  if (s2.length() - s1.length() > 1)
     return false;

  bool find_diff = false;
  for (size_t i = 0, j = 0; i < s1.length(); i++, j++) {
    if (s1[i] != s2[j]) {
      if (find_diff) return false;
      find_diff = true;
      if (s2.length() > s1.length())
        i--;
    }
  }
  return find_diff || s2.length() != s1.length();
}

// To execute C++, please define "int main()"
int main() {

  cout << (one_edit_apart("cat", "dog") ? "True" : "False") << endl;
  cout << (one_edit_apart("cat", "cats") ? "True" : "False") << endl;
  cout << (one_edit_apart("cat", "cut") ? "True" : "False") << endl;
  cout << (one_edit_apart("cat", "cast") ? "True" : "False") << endl;
  cout << (one_edit_apart("cat", "at") ? "True" : "False") << endl;
  cout << (one_edit_apart("cat", "act") ? "True" : "False") << endl;
  return 0;
}
