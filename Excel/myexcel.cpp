#include <iostream>

using namespace std;

template<typename T>
class Cell {
public:
    uint32_t x;
    uint32_t y;
    T value;
    Cell(uint32_t _x, uint32_t _y) : x(_x), y(_y) {}
    Cell(const Cell<T> &cell) {
        this->x = cell.x;
        this->y = cell.y;
        this->value = cell.value;
    }
    Cell<T> operator=(Cell<T> &cell) {
        cout << "operator..." << endl;
        this->x = cell.x;
        this->y = cell.y;
        this->value = cell.value;
        return *this;
    }
    /*
    T operator+(const Cell<T> &cell2) {
        cout << "operator +" << endl;
        return this->value + cell2.value;
    }
    */
    Cell<T> operator+(const Cell<T> &cell2) {
 #if 1
        Cell<T> cell;
        cell.x = this->x + cell2.x;
        cell.y = this->y + cell2.y;
 #else
        Cell<T> cell(this->x + cell2.x, this->y + cell2.y);
 #endif
        cell.value = this->value + cell2.value;
        return cell;
    }
    T operator-(Cell<T> &cell2) {
        cout << "operator -" << endl;
        return this->value - cell2.value;
    }
};

template<typename T>
class MyExcel {
public:
    MyExcel(uint32_t r, uint32_t c) : rows(r), columns(c) {
        for (int i = 0; i < rows; i++) {
            vector<Cell<T>> myrow;
            for (int j = 0; j < columns; j++) {
                myrow.push_back(Cell<T>(i, j));
            }
            table.push_back(myrow);
        }
    }
    
    void setValue(uint32_t r, uint32_t c, T value) {
        if (table.size() == 0 || r >= rows || c >= columns) return;
        
        Cell<T> cell(r, c);
        cell.value = value;
        table[r][c] = cell;
    }
    
    T getValue(uint32_t r, uint32_t c) {
        if (r >= rows || c >= columns) throw invalid_argument("ERROR");
        
        Cell<T> cell = table[r][c];
        return cell.value;
    }
    
    Cell<T> getCell(uint32_t r, uint32_t c) {
        return table[r][c];
    }
private:
    uint32_t rows;
    uint32_t columns;
    vector<vector<Cell<T>>> table;
};

template<typename T>
class Excel {
public:
    Excel(uint32_t r, uint32_t c) : rows(r), columns(c) {
        table = vector<vector<T>>(rows, vector<T>(columns));
        cout << table[0].size() << endl;
    }
    
    void setValue(uint32_t r, uint32_t c, T val) {
        if (r >= table.size() || c >= table[0].size()) return;
        
        table[r][c] = val;
    }
    
    T getValue(uint32_t r, uint32_t c) {
        if (r >= table.size() || c >= table[0].size()) return -1;
        
        return table[r][c];
    }
    
    T add(uint32_t r1, uint32_t c1, uint32_t r2, uint32_t c2) {
        return table[r1][c1] + table[r2][c2];
    }
    
private:
    uint32_t rows;
    uint32_t columns;
    vector<vector<T>> table;
};

int main() {
    Excel<int> excel(12, 20);
    excel.setValue(3, 3, 9);
    excel.setValue(8, 10, 6);
    cout << excel.getValue(3, 3) << endl;
    cout << excel.add(3, 3, 8, 10) << endl;
    
    
    MyExcel<float> myexcel(12, 21);
    myexcel.setValue(3, 5, 4.3);
    myexcel.setValue(8, 6, 10.5);
    cout << myexcel.getValue(3, 5) << endl;
    Cell<float> cell1 = myexcel.getCell(3, 5);
    Cell<float> cell2 = myexcel.getCell(8, 6);
    cout << cell2.value << endl;
    Cell<float> cell3 = cell1 + cell2;
    cout << cell3.value << endl;
    cout << cell1 - cell2 << endl;
}
