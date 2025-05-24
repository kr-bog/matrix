#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct matrix {
    double* data;
    size_t w, h;
};

matrix* matrix_alloc(size_t w, size_t h) {
    matrix* m = malloc(sizeof(matrix));
    if (!m) return NULL;
    m->data = malloc(sizeof(double) * w * h);
    if (!m->data) {
        free(m);
        return NULL;
    }
    m->w = w;
    m->h = h;
    return m;
}

void matrix_free(matrix* m) {
    if (m) {
        free(m->data);
        free(m);
    }
}

size_t matrix_width(const matrix* m) { return m ? m->w : 0; }
size_t matrix_height(const matrix* m) { return m ? m->h : 0; }

int matrix_set(matrix* m, size_t i, size_t j, double val) {
    if (!m || i >= m->h || j >= m->w) return -1;
    m->data[i * m->w + j] = val;
    return 0;
}

double matrix_get(const matrix* m, size_t i, size_t j) {
    if (!m || i >= m->h || j >= m->w) return 0.0;
    return m->data[i * m->w + j];
}

matrix* matrix_alloc_id(size_t w, size_t h) {
    matrix* m = matrix_alloc(w, h);
    if (!m) return NULL;
    for (size_t i = 0; i < h; i++)
        for (size_t j = 0; j < w; j++)
            matrix_set(m, i, j, (i == j ? 1.0 : 0.0));
    return m;
}

int matrix_assign(matrix* dest, const matrix* src) {
    if (!dest || !src || dest->w != src->w || dest->h != src->h) return -1;
    for (size_t i = 0; i < dest->w * dest->h; i++)
        dest->data[i] = src->data[i];
    return 0;
}

void matrix_print(const matrix* m) {
    if (!m) return;
    for (size_t i = 0; i < m->h; i++) {
        for (size_t j = 0; j < m->w; j++) {
            printf("%8.3f ", matrix_get(m, i, j));
        }
        printf("\n");
    }
}
