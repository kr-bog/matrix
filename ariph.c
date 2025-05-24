#include "ariph.h"
#include <math.h>
#include <stdlib.h>
//сложение матрицы
int matrix_add(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || matrix_width(m1) != matrix_width(m2) || matrix_height(m1) != matrix_height(m2))
        return -1;

    for (size_t i = 0; i < matrix_height(m1); i++) {
        for (size_t j = 0; j < matrix_width(m1); j++) {
            double val = matrix_get(m1, i, j) + matrix_get(m2, i, j);
            matrix_set(m1, i, j, val);
        }
    }
    return 0;
}

int matrix_sub(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || matrix_width(m1) != matrix_width(m2) || matrix_height(m1) != matrix_height(m2))
        return -1;

    for (size_t i = 0; i < matrix_height(m1); i++) {
        for (size_t j = 0; j < matrix_width(m1); j++) {
            double val = matrix_get(m1, i, j) - matrix_get(m2, i, j);
            matrix_set(m1, i, j, val);
        }
    }
    return 0;
}

int matrix_mul(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || matrix_width(m1) != matrix_height(m2))
        return -1;

    matrix* res = matrix_alloc(matrix_width(m2), matrix_height(m1));
    if (!res) return -1;

    for (size_t i = 0; i < matrix_height(m1); i++) {
        for (size_t j = 0; j < matrix_width(m2); j++) {
            double sum = 0;
            for (size_t k = 0; k < matrix_width(m1); k++) {
                sum += matrix_get(m1, i, k) * matrix_get(m2, k, j);
            }
            matrix_set(res, i, j, sum);
        }
    }

    int r = matrix_assign(m1, res);
    matrix_free(res);
    return r;
}

int matrix_div(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || matrix_width(m1) != matrix_width(m2) || matrix_height(m1) != matrix_height(m2))
        return -1;

    for (size_t i = 0; i < matrix_height(m1); i++) {
        for (size_t j = 0; j < matrix_width(m1); j++) {
            double denom = matrix_get(m2, i, j);
            if (denom == 0.0) return -1; // защита от деления на ноль
            double val = matrix_get(m1, i, j) / denom;
            matrix_set(m1, i, j, val);
        }
    }
    return 0;
}

int matrix_exp(matrix* m) {
    if (!m) return -1;
    for (size_t i = 0; i < matrix_height(m); i++) {
        for (size_t j = 0; j < matrix_width(m); j++) {
            double val = exp(matrix_get(m, i, j));
            matrix_set(m, i, j, val);
        }
    }
    return 0;
}

int matrix_gauss(matrix* m) {
    if (!m) return -1;
    for (size_t i = 0; i < matrix_height(m); i++) {
        for (size_t j = 0; j < matrix_width(m); j++) {
            double x = matrix_get(m, i, j);
            matrix_set(m, i, j, exp(-x * x));
        }
    }
    return 0;
}

