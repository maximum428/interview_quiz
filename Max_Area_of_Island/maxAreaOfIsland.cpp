#include <iostream>

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int area = 0;
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c])
                    area = max(area, AreadOfIsland(grid, r, c));
            }
        }
        return area;
    }
    int AreadOfIsland(vector<vector<int>>& grid, int row, int col) {
        if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size() || grid[row][col] == 0)
            return 0;
        grid[row][col] = 0;
        /*
        int left = AreadOfIsland(grid, row - 1, col);
        int right = AreadOfIsland(grid, row + 1, col);
        int top = AreadOfIsland(grid, row, col - 1);
        int bottom = AreadOfIsland(grid, row, col + 1);
        return 1 + left + right + top + bottom;
        */
        return 1 + AreadOfIsland(grid, row - 1, col) + AreadOfIsland(grid, row + 1, col) + AreadOfIsland(grid, row, col - 1) + AreadOfIsland(grid, row, col + 1);
    }
};

int main() {
    Solution solution;
    vector<vector<int>> sea = {{0,0,1,0,0,0,0,1,0,0,0,0,0},
                               {0,0,0,0,0,0,0,1,1,1,0,0,0},
                               {0,1,1,0,1,0,0,0,0,0,0,0,0},
                               {0,1,0,0,1,1,0,0,1,0,1,0,0},
                               {0,1,0,0,1,1,0,0,1,1,1,0,0},
                               {0,0,0,0,0,0,0,0,0,0,1,0,0},
                               {0,0,0,0,0,0,0,1,1,1,0,0,0},
                               {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    
    cout << solution.maxAreaOfIsland(sea) << endl;
    for (auto v : sea) {
        for (auto s : v)
            cout << s << " ";
        cout << "\n";
    }
