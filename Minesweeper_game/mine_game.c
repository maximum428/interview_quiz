#include<stdio.h>

typedef struct game {
    uint8_t rows;
    uint8_t columns;
    uint16_t **board;
} game_t;

struct game* game_create(uint8_t rows, uint8_t columns, uint8_t mines) {
    int i, x, y;
    
    game_t *game = NULL;
    if (mines > rows * columns) {
        printf("ERROR: The number of mines is out of range\n");
        return NULL;
    }
    
    if ((game = (game_t*)calloc(1, sizeof(game_t))) == NULL) {
        return NULL;
    }
    
    game->rows = rows;
    game->columns = columns;
    if ((game->board = (uint16_t**)calloc(rows, sizeof(uint16_t*))) == NULL) {
        return NULL;
    }
    
    for (i = 0; i < rows; i++) {
        if ((game->board[i] = (uint16_t*)calloc(columns, sizeof(uint16_t))) == NULL) {
            return NULL;
        }
    }
    
    srand(time(0));
    while (mines) {
        x = rand() % (rows);
        y = rand() % (columns);
        game->board[x][y] = 1;
        mines--;
    }
    return game;
}

void delete(game_t* game) {
    if (game != NULL) {
        if (game->board != NULL) {
            printf("Clean board.\n");
            free(game->board);
        }
        printf("Clean game.\n");
        free(game);
    }
}

void print(game_t* game) {
    int i, j;
    for (i = 0; i < game->rows; i++) {
        for (j = 0; j < game->columns; j++) {
            printf("%d\t", game->board[i][j]);
        }
        printf("\n");
    }
}

int play(game_t* game, uint8_t x, uint8_t y) {
    int numOfMines = 0;
    
    if (x > game->rows || y > game->columns) {
        printf("ERROR: Incorrect input\n");
        return -2;
    }
    if (game->board[x][y] == 1) {
        printf("Bow!!\n");
        return -1;
    }
    
    if (x > 0 && y > 0)
        numOfMines += game->board[x - 1][y - 1];
    if (x > 0 && y < game->columns)
        numOfMines += game->board[x - 1][y + 1];
    if (x < game->rows && y > 0)
        numOfMines += game->board[x + 1][y - 1];
    if (x < game->rows && y < game->columns)
        numOfMines += game->board[x + 1][y + 1];
    if (x > 0)
        numOfMines += game->board[x - 1][y];
    if (x < game->rows)
        numOfMines += game->board[x + 1][y];
    if (y > 0)
        numOfMines += game->board[x][y - 1];
    if (y < game->columns)
        numOfMines += game->board[x][y + 1];
    
    return numOfMines;
    
}

int main(void) {
    int result;
    game_t *game1 = game_create(5, 6, 3);
    game_t *game2 = game_create(10, 8, 5);
    game_t *game3 = game_create(10, 16, 10);
    game_t *game4 = game_create(10, 20, 5);
    game_t *game5 = game_create(10, 5, 8);
    if (game1 == NULL) {
        printf("ERROR: Failed to create game1.\n");
    } else {
        print(game1);
    }
    
    if (game2 == NULL) {
        printf("ERROR: Failed to create game2.\n");
    } else {
        print(game2);
    }
    
    if (game3 == NULL) {
        printf("ERROR: Failed to create game3.\n");
    } else {
        print(game3);
    }
    
    if (game4 == NULL) {
        printf("ERROR: Failed to create game4.\n");
    } else {
        print(game4);
    }
    
    if (game5 == NULL) {
        printf("ERROR: Failed to create game5.\n");
    } else {
        print(game5);
    }
    
    result = play(game1, 1, 1);
    switch (result) {
        case -1: printf("Bow!!\n");
            break;
        case -2: printf("ERROR: Incorrect input\n");
            break;
        default: printf("There are %d mines around the point(1, 1)", result);       
    }

    delete(game1);
    delete(game2);
    delete(game3);
    delete(game4);
    delete(game5);
    return 0;
}
