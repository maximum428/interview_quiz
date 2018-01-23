import java.util.concurrent.ThreadLocalRandom;

// "static void main" must be defined in a public class.
public class Game {
    private int[][] board;
    private int _rows, _columns, _nimes;
    public Game(int rows, int columns, int nimes) {
        if ((rows * columns) < nimes) throw new IllegalArgumentException("ERROR: the numbers of nimes are larger than board size.");

        this._nimes = nimes;
        board = new int[this._columns=columns][this._rows=rows];
        while (0 < nimes) {
            int x = ThreadLocalRandom.current().nextInt(0, this._rows);
            int y = ThreadLocalRandom.current().nextInt(0, this._columns);

            if (board[y][x] != 1) {
                board[y][x] = 1;
                nimes--;
            }
        }
    }
    
    public void Display() {
        for (int i = 0; i < this._columns; i++) {
            for (int j = 0; j < this._rows; j++) {
                System.out.print(board[i][j] + "\t");
            }
            System.out.println("");
        }
    }

    public String Play(int x, int y) {
        int numOfNimes = 0;

        if (x > (this._rows - 1) || y > (this._columns - 1))
            throw new IllegalArgumentException("Incorrect input: overflow of range of row or column");
        try {
            if (board[y][x] == 1) return "Bingo!!";
            
            if (x > 0 && y > 0) numOfNimes += board[y-1][x-1]; // top-left

            if (x < (this._rows - 1) && y > 0) numOfNimes += board[y-1][x+1]; // top-right

            if (x > 0 && y < (this._columns - 1)) numOfNimes += board[y+1][x-1]; // botton-left

            if (x < (this._rows - 1) && y < (this._columns - 1)) numOfNimes += board[y+1][x+1]; // botton-right

            if (x > 0) numOfNimes += board[y][x-1]; // left

            if (y > 0) numOfNimes += board[y-1][x]; // top

            if (x < (this._rows - 1)) numOfNimes += board[y][x+1]; // right

            if (y < (this._columns - 1)) numOfNimes += board[y+1][x]; // botton
        } catch (ArrayIndexOutOfBoundsException e) {
            return "IndexOutOfBoundsException: " + e.getMessage();
        }
        
        return "There are " + numOfNimes + " nimes around the point of (" + x + ", " + y + ")";
    }
    
    public static void main(String[] args) {
        Game game = new Game(5, 5, 5);
        game.Display();
        System.out.println(game.Play(3, 4));
    }
}
