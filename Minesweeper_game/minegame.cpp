#include <random>

class MineGame {
    int m_rows, m_columns;
    int m_mines;
    vector<vector<int>> board;
public:
    MineGame(int rows, int columns, int mines) : m_rows(rows), m_columns(columns), m_mines(mines) {
        board = vector<vector<int>>(rows, vector<int>(columns, 0));
#if 1
        random_device rd;
        mt19937 mt(rd());
        while (m_mines--) {
            uniform_real_distribution<double> x(0, m_rows-1);
            uniform_real_distribution<double> y(0, m_columns-1);
            if (board[int(x(mt))][int(y(mt))]) {
                m_mines++;
                continue;
            }
            board[int(x(mt))][int(y(mt))] = 1;
        }
#else
        srand(time(0));
        while (m_mines--) {
            int x = rand() % m_rows;
            int y = rand() % m_columns;
            if (board[x][y])
                m_mines++;
            else
                board[x][y] = 1;
        }
#endif
    }
    void Display() {
        for (auto row : board) {
            string line = "";
            for (auto element : row) {
                line += to_string(element) + ", ";
            }
            cout << line.substr(0, line.length()-2) << '\n';
        }
        cout << '\n';
    }
    string Play(int x, int y) {
        if (x < 0 || x >= m_rows || y < 0 || y >= m_columns)
            return "Incorrect input";
        if (board[x][y])
            return "BOW!! You hit.";
        
        int sum = 0;
        vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto dir : dirs) {
            int _x = x + dir[0];
            int _y = y + dir[1];
            if (_x < 0 || _x == m_rows)
                _x = x;
            if (_y < 0 || _y == m_columns)
                _y = y;
            sum += board[_x][_y];
        }
        return "There are " + to_string(sum) + " mines arount the point";
    }
};

int main() {
    MineGame game1(10, 5, 8);
    
    game1.Display();
    
    cout << game1.Play(3, 4) << endl;

    
    return 0;
}
