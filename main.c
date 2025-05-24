#include <stdio.h>
#include <accctrl.h>
#include "matrix.h"
#include "ariph.h"

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    matrix* a = matrix_alloc_id(3, 3);
    matrix* b = matrix_alloc_id(3, 3);
    if (!a || !b) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    printf("Матрица A:\n");
    matrix_print(a);

    printf("\nМатрица B:\n");
    matrix_print(b);

    matrix_add(a, b);
    printf("\nA + B:\n");
    matrix_print(a);

    matrix_sub(a, b);
    printf("\n(A + B) - B:\n");
    matrix_print(a);

    matrix_exp(a);
    printf("\nexp(A):\n");
    matrix_print(a);

    matrix_gauss(a);
    printf("\nGauss(A):\n");
    matrix_print(a);

    matrix_free(a);
    matrix_free(b);

    return 0;
}

