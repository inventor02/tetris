#ifndef TETRIS_VECTOR_H
#define TETRIS_VECTOR_H

#include <stdint.h>
#include <stddef.h>

/**
 * A vector (dynamic list).
 */
struct vector {
    uint8_t *data;
    size_t limit;
    size_t size;
    size_t element_size;
};

struct vector vector_create(size_t capacity, size_t element_size);

void vector_delete(struct vector *vec);

void vector_add(struct vector *vec, void *elem);

void vector_remove(struct vector *vec, size_t index);

void *vector_get(struct vector *vec, size_t index);

#endif //TETRIS_VECTOR_H
