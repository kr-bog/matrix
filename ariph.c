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

int matrix_exp(matrix* A) {
    if (!A || matrix_width(A) != matrix_height(A)) return -1;

    const double eps = 1e-10;
    size_t n = matrix_width(A);

    matrix* result = matrix_alloc_id(n, n);
    matrix* term = matrix_alloc_id(n, n);
    matrix* temp = matrix_alloc(n, n);

    if (!result || !term || !temp) {
        matrix_free(result);
        matrix_free(term);
        matrix_free(temp);
        return -1;
    }

    int k = 1;
    double norm;

    do {
        matrix_assign(temp, term);
        if (matrix_mul(temp, A)) {
            matrix_free(result);
            matrix_free(term);
            matrix_free(temp);
            return -1;
        }

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                matrix_set(term, i, j, matrix_get(temp, i, j) / k);
            }
        }

        if (matrix_add(result, term)) {
            matrix_free(result);
            matrix_free(term);
            matrix_free(temp);
            return -1;
        }

        norm = 0;
        for (size_t i = 0; i < n; i++) {
            double row_sum = 0;
            for (size_t j = 0; j < n; j++) {
                row_sum += fabs(matrix_get(term, i, j));
            }
            if (row_sum > norm) norm = row_sum;
        }

        k++;
    } while (norm >= eps);

    int assign_res = matrix_assign(A, result);

    matrix_free(result);
    matrix_free(term);
    matrix_free(temp);

    return assign_res;
}

int matrix_gauss(matrix* m) {
    if (!m) return -1;

    size_t n = matrix_height(m);
    if (matrix_width(m) != n + 1) return -1; // Проверка размера [A|B]

    for (size_t i = 0; i < n; i++) {
        // Частичный выбор главного элемента
        size_t max_row = i;
        double max_val = fabs(matrix_get(m, i, i));
        for (size_t k = i + 1; k < n; k++) {
            double val = fabs(matrix_get(m, k, i));
            if (val > max_val) {
                max_val = val;
                max_row = k;
            }
        }

        if (max_val < 1e-10) return -1; // Система вырождена

        if (max_row != i) {
            // Перестановка строк
            for (size_t j = i; j < n + 1; j++) {
                double tmp = matrix_get(m, i, j);
                matrix_set(m, i, j, matrix_get(m, max_row, j));
                matrix_set(m, max_row, j, tmp);
            }
        }

        // Прямой ход
        for (size_t k = i + 1; k < n; k++) {
            double factor = matrix_get(m, k, i) / matrix_get(m, i, i);
            for (size_t j = i; j < n + 1; j++) {
                double val = matrix_get(m, k, j) - factor * matrix_get(m, i, j);
                matrix_set(m, k, j, val);
            }
        }
    }

    // Обратный ход
    for (int i = (int)n - 1; i >= 0; i--) {
        double sum = matrix_get(m, i, n);
        for (size_t j = i + 1; j < n; j++) {
            sum -= matrix_get(m, i, j) * matrix_get(m, j, n);
        }
        matrix_set(m, i, n, sum / matrix_get(m, i, i));
    }

    return 0;
}
