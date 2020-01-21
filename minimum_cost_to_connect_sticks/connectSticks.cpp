class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        int res = 0;
        priority_queue<int, vector<int>, greater<int>> q;
        for (int stick : sticks)
            q.push(stick);
            
        while (!q.empty()) {
            int first = q.top();
            q.pop();
            if (!q.empty()) {
            int second = q.top();
            q.pop();
            int sum = first + second;
            res += sum;
            q.push(sum);
        }
        return res;
    }
};
