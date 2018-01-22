#include<stdio.h>

typedef struct entry {
    int X;
    int Y;
} entry_t;

typedef struct game {
    int row;
    int column;
    //struct entry **table;
    int **table;
} game_t;

game_t* game_create(int row, int column, int mines) {
    int i, x, y;
    game_t *game = NULL;
    
    if (mines > row*column) {
        printf("ERROR: mines is larger than board scale\n");
        return NULL;
    }
    if (row < 1 && column < 1) return NULL;
    
    if ((game = (game_t*)malloc(sizeof(game_t))) == NULL) {
        return NULL;
    }
    
    game->row = row;
    game->column = column;
    if ((game->table = (int**)malloc(sizeof(int*) * row)) == NULL) {
        return NULL;
    }
    
    for (i = 0; i < row; i++) {
        if ((game->table[i] = (int*)malloc(column * sizeof(int))) == NULL) {
            return NULL;
        }
    }
    
    srand(time(0));
    while (mines) {
        x = rand() % (row);
        y = rand() % (column);
        printf("x=%d; y=%d\n", x, y);
        game->table[x][y] = 1;
        mines--;
    }
    return game;
}

void print(game_t* game) {
    int i, j;
    for (i = 0; i < game->row; i++) {
        for (j = 0; j < game->column; j++) {
            printf("%d\t", game->table[i][j]);
        }
        printf("\n");
    }
}

int play(game_t* game, int x, int y) {
    int numOfMines = 0;
    
    if (game->table[x][y] == 1) {
        printf("Bow!! Bow!!\n");
        return -1;
    }
    /*
    if (x > 0 && y > 0) {
        numOfMines += game->table[x-1][y-1];
        numOfMines += game->table[x][y-1];
        numOfMines += game->table[]
    } */
    return NULL;
}

int main() {
    game_t *game1 = game_create(5, 5, 3);
    game_t *game2 = game_create(10, 10, 5);
    if (game1 == NULL) {
        printf("return NULL (game1)\n");
    } else
        print(game1);

    if (game2 == NULL) {
        printf("return NULL (game2)\n");
    } else
        print(game2);

    if (play(game1, 3, 1) == -1) {
        printf("Game Over!!\n");
    }
    if (game1 != NULL) free(game1);
    if (game2 != NULL) free(game2);
}
