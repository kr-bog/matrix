#ifndef ARIPH_H
#define ARIPH_H
#include "matrix.h"

int matrix_add(matrix* m1, const matrix* m2);
int matrix_sub(matrix* m1, const matrix* m2);
int matrix_mul(matrix* m1, const matrix* m2);
int matrix_div(matrix* m1, const matrix* m2); //поэлементное деление

int matrix_exp(matrix* m);  //экспонента каждого элемента
int matrix_gauss(matrix* m); //exp для каждого элемента

#endif //ARIPH_H
