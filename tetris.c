#include "tetris.h"

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "vector.h"

static uint8_t calculate_block_dim_x(struct block *blocks) {
    uint8_t lowest_x = blocks[0].coords.x;
    uint8_t highest_x = blocks[0].coords.x;

    for (int i = 1; i < 4; i++) {
        if (blocks[i].coords.x < lowest_x) {
            lowest_x = blocks[i].coords.x;
        }

        if (blocks[i].coords.x > highest_x) {
            highest_x = blocks[i].coords.x;
        }
    }

    return highest_x - lowest_x;
}

static uint8_t calculate_block_dim_y(struct block *blocks) {
    uint8_t lowest_y = blocks[0].coords.y;
    uint8_t highest_y = blocks[0].coords.y;

    for (int i = 1; i < 4; i++) {
        if (blocks[i].coords.y < lowest_y) {
            lowest_y = blocks[i].coords.y;
        }

        if (blocks[i].coords.y > highest_y) {
            highest_y = blocks[i].coords.y;
        }
    }

    return highest_y - lowest_y;
}

static void transform_piece(struct falling_piece *piece, uint8_t displacement_x, uint8_t displacement_y) {
    for (int i = 0; i < 4; i++) {
        piece->blocks[i].coords.x = piece->blocks[i].coords.x + displacement_x;
        piece->blocks[i].coords.y = piece->blocks[i].coords.y + displacement_y;
    }
}

struct grid grid_create() {
    struct grid g = {
            .blocks = vector_create(10, sizeof(struct block)),
            .falling_piece = {0},
    };

    return g;
}

void grid_destroy(struct grid *grid) {
    assert(grid != NULL);

    free(grid->falling_piece.blocks);
    grid->falling_piece.blocks = NULL;

    vector_delete(&grid->blocks);
}

static enum block_color pick_random_block_color() {
    return rand() % 8;
}

static uint8_t pick_starting_x(uint8_t block_size_x) {
    return rand() % (GRID_SIZE_X + 1);
}

static struct block *generate_block_for_color(enum block_color color, struct coordinate *coords) {
    struct block *blocks = malloc(4 * sizeof(struct block));

    for (int i = 0; i < 4; i++) {
        blocks[i] = (struct block) {color, {coords[i].x, coords[i].y}};
    }

    return blocks;
}

static struct falling_piece generate_piece(struct grid *grid) {
    enum block_color color = pick_random_block_color();

    struct coordinate *coords = malloc(4 * sizeof(struct coordinate));

    switch (color) {
        case CYAN:
            coords[0] = (struct coordinate) {0, 0};
            coords[1] = (struct coordinate) {1, 0};
            coords[2] = (struct coordinate) {2, 0};
            coords[3] = (struct coordinate) {3, 0};
            break;
        case YELLOW:
            coords[0] = (struct coordinate) {0, 0};
            coords[1] = (struct coordinate) {1, 0};
            coords[2] = (struct coordinate) {0, 1};
            coords[3] = (struct coordinate) {1, 1};
            break;
        case PURPLE:
            coords[0] = (struct coordinate) {1, 1};
            coords[1] = (struct coordinate) {0, 0};
            coords[2] = (struct coordinate) {1, 0};
            coords[3] = (struct coordinate) {2, 0};
            break;
        case BLUE:
            coords[0] = (struct coordinate) {1, 2};
            coords[1] = (struct coordinate) {1, 1};
            coords[2] = (struct coordinate) {0, 0};
            coords[3] = (struct coordinate) {1, 0};
            break;
        case ORANGE:
            coords[0] = (struct coordinate) {0, 2};
            coords[1] = (struct coordinate) {0, 1};
            coords[2] = (struct coordinate) {0, 0};
            coords[3] = (struct coordinate) {1, 0};
            break;
        case GREEN:
            coords[0] = (struct coordinate) {0, 0};
            coords[1] = (struct coordinate) {1, 0};
            coords[2] = (struct coordinate) {1, 1};
            coords[3] = (struct coordinate) {2, 1};
            break;
        default:
        case RED:
            coords[0] = (struct coordinate) {1, 0};
            coords[1] = (struct coordinate) {2, 0};
            coords[2] = (struct coordinate) {0, 0};
            coords[3] = (struct coordinate) {1, 0};
            break;
    }

    struct block *blocks = generate_block_for_color(color, coords);

    free(coords);
    coords = NULL;

    struct falling_piece piece = {
            .blocks = blocks,
    };

    return piece;
}