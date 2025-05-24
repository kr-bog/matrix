#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>

typedef struct matrix matrix;

//создание и освобождение
matrix* matrix_alloc(size_t w, size_t h);
void matrix_free(matrix*m);

//размеры
size_t matrix_width(const matrix* m);
size_t matrix_height(const matrix* m);

int matrix_set (matrix* m, size_t i, size_t j, double val);
double matrix_get (const matrix* m, size_t i, size_t j);

// бязлание и устанявка едининняй матрицы
matrix* matrix_alloc_id(size_t w, size_t h);

//копирование
int matrix_assign(matrix* dest, const matrix* src);
//вывод
void matrix_print(const matrix* m);

#endif //MATRIX_H
