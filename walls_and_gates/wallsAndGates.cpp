class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
#if 1
        queue<pair<int, int>> q;
        vector<vector<int>> dirs = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < rooms.size(); i++) {
            for (int j = 0; j < rooms.[i].size(); j++) {
                if (rooms[i][j] == 0)
                    q.push({i, j});
            }
        }
        while (!q.empty()) {
            int i = q.front().first, j = q.front().second;
            q.pop();
            for (int k = 0; k < dirs.size(); k++) {
                int x = i + dirs[k][0], y = j + dirs[k][1];
                if (x < 0 || y < 0 || x >= rooms.size() || y >= rooms[0].size() || rooms[x][y] < rooms[i][j] + 1)
                    continue;
                rooms[x][y] = rooms[i][j] + 1;
                q.push({x, y});
            }
        }
#else
        for (int i = 0; i < rooms.size(); i++) {
            for (int j = 0; j < rooms[i].size(); j++) {
                if (rooms[i][j] == 0)
                    helper(rooms, i, j, 0);
            }
        }
#endif
    }
    
    void helper(vector<vector<int>>& rooms, int i, int j, int val) {
        if (i < 0 || j < 0 || i >= rooms.size() || j >= rooms[0].size() || rooms[i][j] < val)
            return;
        rooms[i][j] = val;
        helper(rooms, i + 1, j, val + 1);
        helper(rooms, i - 1, j, val + 1);
        helper(rooms, i, j + 1, val + 1);
        helper(rooms, i, j - 1, val + 1);
    }
};
