#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <stdint.h>
#include <stddef.h>
#include "vector.h"

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 20

enum block_color {
    CYAN,
    BLUE,
    ORANGE,
    YELLOW,
    GREEN,
    PURPLE,
    RED,
};

struct coordinate {
    uint8_t x;
    uint8_t y;
};

struct block {
    enum block_color color;
    struct coordinate coords;
};

struct falling_piece {
    struct block *blocks;
};

struct grid {
    struct vector blocks;
    struct falling_piece falling_piece;
};

struct grid grid_create();

void grid_destroy(struct grid *grid);

#endif //TETRIS_TETRIS_H
