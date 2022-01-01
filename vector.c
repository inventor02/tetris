#include "vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static void vector_resize(struct vector *vec) {
    vec->limit = vec->limit * 2;
    vec->data = realloc(vec->data, vec->limit * vec->element_size);
    assert(vec->data != NULL);
}

struct vector vector_create(size_t capacity, size_t element_size) {
    return (struct vector) {
        .size = 0,
        .element_size = element_size,
        .limit = capacity,
        .data = calloc(capacity, element_size),
    };
}

void vector_delete(struct vector *vec) {
    assert(vec != NULL);
    free(vec->data);
    vec->data = NULL;
}

void vector_add(struct vector *vec, void *elem) {
    assert(vec != NULL);

    if (vec->size == vec->limit) {
        vector_resize(vec);
    }

    memcpy(vec->data + (vec->size * vec->element_size), elem, vec->element_size);
    vec->size++;
}

void vector_remove(struct vector *vec, size_t index) {
    assert(vec != NULL);
    assert(index >= 0);

    memmove(vec->data + index * vec->element_size, vec->data + (index + 1) * vec->element_size,
            (vec->size - index) * vec->element_size);
    vec->size--;
}

void *vector_get(struct vector *vec, size_t index) {
    assert(vec != NULL);
    assert(index >= 0);

    return vec->data + (vec->element_size * index);
}
