import java.util.ArrayList;

public class Excel<T> {
    int _rows, _columns;
    ArrayList< ArrayList<GenericCell> > board = new ArrayList<ArrayList<GenericCell>>();
    
    class GenericCell {
        int _x, _y;
        GenericCell(int x, int y) {
            this._x = x;
            this._y = y;
        }
    }
    class Cell<T> extends GenericCell {
        T value;
        Cell(int x, int y) {
            super(x, y);
        }
    }
    
    Excel(int rows, int columns) {
        this._rows = rows;
        this._columns = columns;
        
        for (int ro = 0; ro < _rows; ro++) {
            ArrayList<GenericCell> myrow = new ArrayList<GenericCell>();
            for (int col = 0; col < _columns; col++) {
                GenericCell cell = new GenericCell(ro, col);
                myrow.add(cell);
            }
            board.add(myrow);
        }
    }
    
    void setValue(int x, int y, T value) {
        if (board.size() == 0) throw new IllegalArgumentException("Excel not created!");
        if (x > _rows || y > _columns) throw new IllegalArgumentException("Incorrect input");

        Cell<T> cell = new Cell<T>(x, y);
        cell.value = value;
        board.get(x).set(y, cell);
    }
    
    T getValue(int x, int y) {
        if (board.size() == 0) throw new IllegalArgumentException("Excel not created!");
        if (x > _rows || y > _columns) throw new IllegalArgumentException("Incorrect input");
        
        Cell<T> cell = (Cell)board.get(x).get(y);
        return cell.value;
    }

    public static void main(String[] args) {
        Excel excel = new Excel(5, 10);
        excel.setValue(2, 4, 15);
        System.out.println(excel.getValue(2, 4));
    }
}
