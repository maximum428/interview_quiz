#include <iostream>
#include <memory>
#include <vector>

class GenericCell {
public:
    int _x;
    int _y;
    GenericCell(int x, int y) : _x(x), _y(y) {};
};

template<typename T>
class Cell : public GenericCell {
public:
    T value;
    Cell(int x, int y) : GenericCell(x, y) {};
};


class Excel {
public:
    Excel(int rows, int columns) : _rows(rows), _columns(columns) {
       for (int r = 0; r < rows; r++) {
           vector<GenericCell> myrow;
           for (int col = 0; col < columns; col++) {
               GenericCell cell(r, col);
               myrow.push_back(cell);
           }
           board.push_back(myrow);
       }
    }
    
    template<typename T>
    void setValue(int row, int column, T value) {
        if (board.size() == 0) throw invalid_argument("Error: Excel not created");
        if (row > _rows || column > _columns) throw invalid_argument("Error: Inccorect input given (numbers of row or column)");

        Cell<int> cell(row, column);
        cell.value = value;
        board[row][column] = cell;
    }
    
    template<typename T>
    T getValue(int row, int column) {
        if (row > _rows || column > _columns) throw invalid_argument("Error: Inccorect input given (numbers of row or column)");
        
        Cell<T> cell = board[row][column];
        return cell.val;
    }
    void Display() {
        /*for (int r = 0; r < _rows; r++) {
            for (int c = 0; c < _columns; c++) {
                std::cout << board[r][c] << "\t";
            }
            std::cout << "\n";
        } */
    }
private:
    int _rows;
    int _columns;
    vector< vector<GenericCell> > board;
};
int main() {
    Excel excel(5, 10);
    excel.setValue(2, 4, 15);
    std::cout << excel.getValue(2, 4) << std::endl;   //  ?? Erro?? not give type
    std::cout << "Hello World!\n";
}
