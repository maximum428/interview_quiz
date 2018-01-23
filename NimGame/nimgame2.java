import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

// "static void main" must be defined in a public class.
public class Game {
    private Vector< Vector<Integer> > board;
    private int _rows, _columns, _nimes;
    public Game(int rows, int columns, int nimes) {
        if ((rows * columns) < nimes) throw new IllegalArgumentException("ERROR: the numbers of nimes are larger than board size.");

        this._nimes = nimes;
        this._columns = columns;
        board = new Vector< Vector<Integer> >(this._rows=rows);
        for (int r = 0; r < this._rows; r++) {
            board.add(r, new Vector<Integer>(this._columns));
        }
        
        for (int i = 0; i < this._columns; i++) {
            for(int j = 0; j < this._rows; j++) {
                board.get(i).add(j, 0);
            }
        }       
        
        while (0 < nimes) {
            int x = ThreadLocalRandom.current().nextInt(0, this._columns);
            int y = ThreadLocalRandom.current().nextInt(0, this._rows);

            if (1 != board.get(x).get(y)) {
                board.get(x).set(y, 1);
                nimes--;
            }
        }
    }
   
    public void Display() {
        for (int i = 0; i < this._columns; i++) {
            for (int j = 0; j < this._rows; j++) {
                System.out.print(board.get(i).get(j) + "\t");
            }
            System.out.println("");
        }
    }

    public String Play(int x, int y) {
        int numOfNimes = 0;

        if (x > (this._rows - 1) || y > (this._columns - 1))
            throw new IllegalArgumentException("Incorrect input: overflow of range of row or column");
        try {
            if (board.get(y).get(x) == 1) return "Bingo!!";
            
            if (x > 0 && y > 0) numOfNimes += board.get(y-1).get(x-1); // top-left

            if (x < (this._rows - 1) && y > 0) numOfNimes += board.get(y-1).get(x+1); // top-right

            if (x > 0 && y < (this._columns - 1)) numOfNimes += board.get(y+1).get(x-1); // botton-left

            if (x < (this._rows - 1) && y < (this._columns - 1)) numOfNimes += board.get(y+1).get(x+1); // botton-right

            if (x > 0) numOfNimes += board.get(y).get(x-1); // left

            if (y > 0) numOfNimes += board.get(y-1).get(x); // top

            if (x < (this._rows - 1)) numOfNimes += board.get(y).get(x+1); // right

            if (y < (this._columns - 1)) numOfNimes += board.get(y+1).get(x); // botton
        } catch (ArrayIndexOutOfBoundsException e) {
            return "IndexOutOfBoundsException: " + e.getMessage();
        }
        
        return "There are " + numOfNimes + " nimes around the point of (" + x + ", " + y + ")";
    }

    public static void main(String[] args) {
        Game game = new Game(5, 4, 5);
        game.Display();
        System.out.println(game.Play(3, 3));
    }
}
