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
