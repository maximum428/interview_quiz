import java.util.concurrent.ThreadLocalRandom;

public class MineGame {
    private int rows, columns, mines;
    private int[][] board;
    
    public MineGame(int rows, int columns, int mines) {
        if ((rows * columns) < mines) throw new IllegalArgumentException("ERROR: Too many mines.");
        
        this.mines = mines;
        
        board = new int[this.rows = rows][this.columns = columns];
        while (mines > 0) {
            int x = ThreadLocalRandom.current().nextInt(0, this.rows);
            int y = ThreadLocalRandom.current().nextInt(0, this.columns);
            
            if (board[x][y] != 1) {
                board[x][y] = 1;
                mines--;
            }
        }
    }
    
    public void Display() {
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                System.out.print(board[i][j] + "\t");
            }
            System.out.println("");
        }
    }
    
    public String Play(int x, int y) {
        int numOfMines = 0;
        
        if (x > (this.rows - 1) || y > (this.columns - 1))
            throw new IllegalArgumentException("Error: Incorrect input");
        try {
            if (board[x][y] == 1)
                return "Bow!!";
            if (x > 0 && y > 0 ) numOfMines += board[x - 1][y - 1];
            if (x < (this.rows - 1) && y > 0) numOfMines += board[x + 1][y - 1];
            if (x > 0 && y < (this.columns - 1)) numOfMines += board[x - 1][y + 1];
            if (x < (this.rows - 1) && y < (this.columns - 1)) numOfMines += board[x + 1][y + 1];
            if (x > 0) numOfMines += board[x - 1][y];
            if (y > 0) numOfMines += board[x][y - 1];
            if (x < (this.rows - 1)) numOfMines += board[x + 1][y];
            if (y < (this.columns - 1)) numOfMines += board[x][y + 1];
        } catch (ArrayIndexOutOfBoundsException e) {
            return "IndexOutOfBoundsException: " + e.getMessage();
        }
        return "There are " + numOfMines + " mines around the point (" + x + ", " + y + ")";
    }
    
    public static void main(String[] args) {
        MineGame game1 = new MineGame(6, 8, 9);
        MineGame game2 = new MineGame(12, 5, 12);
        MineGame game3 = new MineGame(8, 5, 10);
        MineGame game4 = new MineGame(2, 5, 3);
        MineGame game5 = new MineGame(9, 10, 13);
        game1.Display();
        game2.Display();
        game3.Display();
        game4.Display();
        game5.Display();
        
        System.out.println(game1.Play(3, 4));
    }
}
