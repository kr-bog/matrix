#include "ariph.h"

//сложение матрицы
int matrix_add(matrix *m1, const matrix *m2) {
    if (matrix_width(m1) != matrix_width(m2) || matrix_height(m1) != matrix_height(m2))
        return -1;
    for (size_t i = 0; i < matrix_height(m1); i++)
        for (size_t j = 0; j < matrix_width(m1); j++)
            *matrix_ptr(m1, i, j) += *matrix_cptr(m2, i, j);
    return 0;
}

//умножение матрицы
int matrix_mul(matrix *m1, const matrix *m2) {
    if (matrix_width(m1) != matrix_height(m2)) return -1;

    matrix *res = matrix_alloc(matrix_width(m2), matrix_height(m1));
    if (!res) return -1;

    for (size_t i = 0; i < matrix_height(m1); i++) {
        for (size_t j = 0; j < matrix_width(m2); j++) {
            double sum = 0;
            for (size_t k = 0; k < matrix_width(m1); k++) {
                sum += (*matrix_cptr(m1, i, k)) * (*matrix_cptr(m2, k, j));
            }
            *matrix_ptr(res, i, j) = sum;
        }
    }

    int r = matrix_assign(m1, res);
    matrix_free(res);
    return r;
}
