typedef struct game {
    uint8_t rows;
    uint8_t columns;
    uint32_t **board;
} game_t;

game_t *create_game(uint8_t rows, uint8_t columns, uint32_t mines) {
    game_t *game = NULL;
    int i;
    if (mines > rows * columns) {
        printf("[ERROR]: Incorrect input\n");
        return NULL;
    }
    
    if ((game = (game_t*)malloc(sizeof(game_t))) == NULL)
        return NULL;
    game->rows = rows;
    game->columns = columns;
    
    if ((game->board = (uint32_t**)malloc(sizeof(uint32_t*) * rows)) == NULL)
        return NULL;
    
    for (i = 0; i < rows; i++) {
        if ((game->board[i] = (uint32_t*)calloc(columns, sizeof(uint32_t))) == NULL)
            return NULL;
    }
    
    srand(time(0));
    while (mines--) {
        int x = rand() % rows;
        int y = rand() % columns;
        game->board[x][y] = 1;
    }
    return game;
}

void display(game_t *game) {
    int i, j;
    for (i = 0; i < game->rows; i++) {
        for (j = 0; j < game->columns; j++) {
            printf("%d\t", game->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void delete_game(game_t *game) {
    int i, j;
    if (game != NULL) {
        if (game->board != NULL) {
            for (i = 0; i < game->rows; i++)
                free(game->board[i]);
            free(game->board);
        }
        free(game);
    }
}

int play(game_t *game, uint8_t x, uint8_t y) {
    int numOfMines = 0, i;
    
    if (game == NULL) return -2;
    if (x >= game->rows || y >= game->columns)
        return -2;
    if (game->board[x][y]) {
        printf("Bom!!\n");
        return -1;
    }
    
    int dirs[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
    for (i = 0; i < 8; i++) {
        int _x = x + dirs[i][0];
        int _y = y + dirs[i][1];
        if (_x >= 0 && _x < game->rows && _y >= 0 && _y < game->columns)
            numOfMines += game->board[_x][_y];
    }
    return numOfMines;
}

int main() {
    game_t *game = create_game(5, 5, 3);
    display(game);
    printf("Mines: %d\n", play(game, 3, 2));
    delete_game(game);
}
