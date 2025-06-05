#ifndef ARIPH_H
#define ARIPH_H

#include "matrix.h"

//сложение матриц
int matrix_add(matrix* m1, const matrix* m2);
//вычитание матриц
int matrix_sub(matrix* m1, const matrix* m2);
//умножение матриц
int matrix_mul(matrix* m1, const matrix* m2);
// поэлементное деление
int matrix_div(matrix* m1, const matrix* m2);

//матричная экспонента
int matrix_exp(matrix* m);
// Решение СЛАУ методом Гаусса
int matrix_gauss(matrix* m);

#endif //ARIPH_H
