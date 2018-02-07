##from timeit import timeit
##import random

class MineGame:
    def __init__ (self, rows, columns, mines):
        self.rows = rows
        self.columns = columns
        self.mines = mines
        
        ##self.board = [[0] * columns] * rows
        self.board = [ [ 0 for i in range(columns)] for j in range(rows)]
        
        while (mines > 0):
            x = random.randint(0, (self.rows - 1))
            y = random.randint(0, (self.columns - 1))
            print "x=%d; y=%d" % (x, y)
            if (self.board[x][y] != 1):
                self.board[x][y] = 1
                mines -= 1
        
    def Display(self):
        for i in range(self.rows):
            for j in range(self.columns):
                print self.board[i][j],
            print("\n")
            
    def Play(self, x, y):
        if x > (self.rows - 1) or y > (self.columns - 1):
            system.exit("ERROR: Incorrect input")
            
        try:
            if self.board[x][y] == 1:
                return "Bow!!"
            
            numOfMines = 0
            if x > 0 and y > 0:
                numOfMines += self.board[x - 1][y - 1]
            if x < (self.rows - 1) and y > 0:
                numOfMines += self.board[x + 1][y - 1]
            if x > 0 and y < (self.columns - 1):
                numOfMines += self.board[x - 1][y + 1]
            if x > (self.rows - 1) and y < (self.columns - 1):
                numOfMines += self.board[x + 1][y + 1]
            if x > 0:
                numOfMines += self.board[x + 1][y]
            if y > 0:
                numOfMines += self.board[x][y - 1]
            if x < (self.rows - 1):
                numOfMines += self.board[x + 1][y]
            if y < (self.columns - 1):
                numOfMines += self.board[x][y + 1]
        except:
            system.exit("ERROR")
        return "There are " + str(numOfMines) + " mines around the point (" + str(x) + ", " + str(y) + ")"
        
        
if __name__ == "__main__":
    game1 = MineGame(5, 4, 3)
    game1.Display()
    print "%s" % game1.Play(2, 2)
