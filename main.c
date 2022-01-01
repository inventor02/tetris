#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"
#include "tetris.h"

void render_tetris_grid_to_console(struct block *blocks, uint8_t number_of_blocks) {
    char grid[GRID_SIZE_X][GRID_SIZE_Y];

    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            grid[i][j] = ' ';
        }
    }

    for (int i = 0; i < number_of_blocks; i++) {
        struct block block = blocks[i];
        switch (block.color) {
            case BLUE:
                grid[block.coords.x][block.coords.y] = 'B';
                break;
            case CYAN:
                grid[block.coords.x][block.coords.y] = 'C';
                break;
            case YELLOW:
                grid[block.coords.x][block.coords.y] = 'Y';
                break;
            case RED:
                grid[block.coords.x][block.coords.y] = 'R';
                break;
            case PURPLE:
                grid[block.coords.x][block.coords.y] = 'P';
                break;
            case ORANGE:
                grid[block.coords.x][block.coords.y] = 'O';
                break;
            case GREEN:
                grid[block.coords.x][block.coords.y] = 'G';
                break;
        }
    }

    for (int i = GRID_SIZE_Y - 1; i >= 0; i--) {
        for (int j = 0; j < GRID_SIZE_X; j++) {
            printf("%c", grid[j][i]);
        }

        printf(" | %2d\n", i);
    }

    for (int i = 0; i < GRID_SIZE_X; i++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < GRID_SIZE_X; i++) {
        printf("%d", i);
    }
}

int main() {
    srand(time(0));

    struct block *blocks = calloc(5, sizeof(struct block));
    blocks[0] = (struct block) {
        .coords = (struct coordinate) {0, 0},
        .color = CYAN
    };
    blocks[1] = (struct block) {
        .coords = (struct coordinate) {0, 1},
        .color = BLUE
    };

    render_tetris_grid_to_console(blocks, 2);

    return EXIT_SUCCESS;
}