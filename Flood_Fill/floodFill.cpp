class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int color = image[sr][sc];
        if (color != newColor)
            startFloodFill(image, sr, sc, color, newColor);
        return image;
    }
private:
    void startFloodFill(vector<vector<int>>& image, int sr, int sc, int color, int newColor) {
        if (sr < 0 || sc < 0 || sr >= image.size() || sc >= image[0].size() || image[sr][sc] != color) return;
        
        image[sr][sc] = newColor;
        startFloodFill(image, sr, sc - 1, color, newColor);
        startFloodFill(image, sr, sc + 1, color, newColor);
        startFloodFill(image, sr - 1, sc, color, newColor);
        startFloodFill(image, sr + 1, sc, color, newColor);
    }
};

void fillFlood2(std::vector<std::vector<int>>& image, int sr, int sc, int color, int newColor) {
    std::queue<int> sr_q, sc_q;
    sr_q.push(sr);
    sc_q.push(sc);
    
    std::vector<std::vector<int>> dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    
    while (!sr_q.empty() && !sc_q.empty()) {
        int r = sr_q.front();
        sr_q.pop();
        int c = sc_q.front();
        sc_q.pop();
        
        for (auto dir = 0; dir < dirs.size(); dir++) {
            if ((r + dirs[dir][0]) < 0 || (c + dirs[dir][1]) < 0 || (r + dirs[dir][0]) >= image.size() || (c + dirs[dir][1]) >= image[0].size() || image[r+dirs[dir][0]][c+dirs[dir][1]] != color) { 
                continue;
            }
            sr_q.push(r+dirs[dir][0]);
            sc_q.push(c+dirs[dir][1]);
        }
        image[r][c] = newColor;
    }
}
int main() {
    // Write C++ code here
    std::vector<std::vector<int>> image = {{1, 1, 1},{1, 1, 0}, {1, 0, 1}};
    int sr = 1, sc = 1, newColor = 2;
    
    fillFlood2(image, sr, sc, image[sr][sc], newColor);
    
    for (auto &r : image) {
        std::cout << "[";
        for (auto &c : r) {
            std::cout << c << " ";
        }
        std::cout << "]\n";
    }

    return 0;
}
