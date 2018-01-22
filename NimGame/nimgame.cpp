#include <iostream>
#include <vector>

class NimGame {
public:
    NimGame(int row, int column, int nimes): _row(row), _column(column), _nimes(nimes) {
        srand(time(0));
        for (int r = 0; r < _row; r++) {
            vector<int> myrow;
            for (int col = 0; col < _column; col++) {
                myrow.push_back(0);
            }
            board.push_back(myrow);
        }
        
        while (_nimes--) {
            int x = rand() % _row;
            int y = rand() % _column;
            board[x][y] = 1;
        }
    }
    void Display() {
        for (int r = 0; r < _row; r++) {
            for (int c = 0; c < _column; c++) {
                std::cout << board[r][c] << "\t";
            }
            std::cout << "\n";
        }
    }
    
    string Play(int x, int y) {
        int numOfNimes = 0;
        if (x > _row || y > _column) throw std::invalid_argument("The input is incorret!!");
        if (board[x][y] == 1) {
            return "Bow!! Bow!! Explosion";
        }
        
        if (x > 0 && y > 0)
            numOfNimes += board[x-1][y-1]; // top-left
        if (x > 0 && y < _column)
            numOfNimes += board[x-1][y+1];  // button-left
        if (x < _row && y > 0)
            numOfNimes += board[x+1][y-1]; // top-right
        if (x < _row && y < _column)
            numOfNimes += board[x+1][y+1];  // button-right
        if (x > 0)
            numOfNimes += board[x-1][y]; // left
        if (x < _row)
            numOfNimes += board[x+1][y]; // right
        if (y > 0)
            numOfNimes += board[x][y-1]; // top
        if (y < _column)
            numOfNimes += board[x][y+1]; // button
        
        return "There are " + std::to_string(numOfNimes) + " nimes around the point of (" + std::to_string(x) + ", " + std::to_string(y) + ").";
    }
private:
    vector< vector<int> > board;
    int _row, _column, _nimes;
};

int main() {
    NimGame Game(5, 5, 3);
    Game.Display();
    std::cout << Game.Play(1, 3) << std::endl;
}
