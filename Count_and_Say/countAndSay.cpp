class Solution {
public:
    string countAndSay(int n) {
        string str = "1";

        while (n > 1) {
            int count = 0;
            string pre = "";
            char c = str[0];
            for (int i = 0; i <= str.size(); i++) {
                if (str[i] == c) {
                    count++;
                } else {
                    pre += to_string(count) + c;
                    c = str[i];
                    count = 1;
                }
            }
            str = pre;
            n--;
        }
        return str;
    }
};
