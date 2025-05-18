#include <stdio.h>
#include <accctrl.h>
#include "matrix.h"
#include "ariph.h"

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //создаем две матрицы 3 на 3
    matrix *a = matrix_alloc_id(3, 3);
    matrix *b = matrix_alloc_id(3, 3);
    if (!a || !b) {
        printf("ошибка выделения памяти\n");
        return 1;
    }

    printf("Матрица A:\n");
    matrix_print(a);

    printf("\nМатрица B:\n");
    matrix_print(b);

    matrix_add(a, b);
    printf("\nA + B:\n");
    matrix_print(a);

    matrix_free(a);
    matrix_free(b);
    return 0;
}
