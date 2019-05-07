#include <iostream>

class MineGame {
public:
    MineGame(int rows, int columns, int mines) : _rows(rows), _columns(columns), _mines(mines) {
        srand(time(0));
        board = vector<vector<unsigned int>>(rows, vector<unsigned int>(columns, 0));
        /*
        for (int i = 0; i < _rows; i++) {
            vector<unsigned int> myrow;
            for (int j = 0; j < _columns; j++) {
                myrow.push_back(0);
            }
            board.push_back(myrow);
        }*/
        
        while (_mines--) {
            int x = rand() % _rows;
            int y = rand() % _columns;
            board[x][y] = 1;
        }
    }
    
    void Display() {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _columns; j++) {
                std::cout << board[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }
    
    string Play(int x, int y) {
        int numOfMines = 0;
        if (x > _rows || y > _columns) throw std::invalid_argument("ERROR:Incorrect input");
        
        if (board[x][y] == 1) {
            return "Bow!!";
        }
        
        if (x > 0 && y > 0)
            numOfMines += board[x - 1][ y - 1];
        if (x > 0 && y < _columns)
            numOfMines += board[x - 1][y + 1];
        if (x < _rows && y > 0)
            numOfMines += board[x + 1][y - 1];
        if (x < _rows && y < _columns)
            numOfMines += board[x + 1][y + 1];
        if (x > 0)
            numOfMines += board[x - 1][y];
        if (x < _rows)
            numOfMines += board[x + 1][y];
        if (y > 0)
            numOfMines += board[x][y - 1];
        if (y < _columns)
            numOfMines += board[x][y + 1];
        return "There are " + std::to_string(numOfMines) + " mines around the point (" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
    
private:
    int _rows, _columns;
    int _mines;
    vector< vector<unsigned int> > board;
};
int main() {
    MineGame game1(10, 5, 5);
    MineGame game2(4, 3, 2);
    MineGame game3(12, 12, 10);
    MineGame game4(9, 6, 8);
    MineGame game5(9, 10, 10);
    game1.Display();
    game2.Display();
    game3.Display();
    game4.Display();
    game5.Display();
    
    std::cout << game1.Play(3, 5) << std::endl;
}
