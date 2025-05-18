#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct matrix {
    double *data;   // элементы
    size_t w, h;    // ширина и высота
};

// выделение памяти
matrix *matrix_alloc(size_t w, size_t h) {
    matrix *m = malloc(sizeof(matrix));
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

//освобождение
void matrix_free(matrix *m) {
    if (m) {
        free(m->data);
        free(m);
    }
}

//размеры
size_t matrix_width(const matrix *m) { return m->w; }
size_t matrix_height(const matrix *m) { return m->h; }

double *matrix_ptr(matrix *m, size_t i, size_t j) {
    return &m->data[i * m->w + j];
}

const double *matrix_cptr(const matrix *m, size_t i, size_t j) {
    return &m->data[i * m->w + j];
}

//заполнение единичной матрицы
void matrix_set_id(matrix *m) {
    for (size_t i = 0; i < m->h; i++)
        for (size_t j = 0; j < m->w; j++)
            *matrix_ptr(m, i, j) = (i == j ? 1.0 : 0.0);
}

//создание и заполнение единичной
matrix *matrix_alloc_id(size_t w, size_t h) {
    matrix *m = matrix_alloc(w, h);
    if (m) matrix_set_id(m);
    return m;
}

//копирование матрицы
int matrix_assign(matrix *m1, const matrix *m2) {
    if (m1->w != m2->w || m1->h != m2->h) return -1;
    for (size_t i = 0; i < m1->h * m1->w; i++)
        m1->data[i] = m2->data[i];
    return 0;
}

//вывод матрицы
void matrix_print(const matrix *m) {
    for (size_t i = 0; i < m->h; i++) {
        for (size_t j = 0; j < m->w; j++)
            printf("%8.3f ", *matrix_cptr(m, i, j));
        printf("\n");
    }
}
