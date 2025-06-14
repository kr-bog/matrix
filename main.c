#include <stdio.h>
#include <windows.h>
#include "matrix.h"
#include "ariph.h"

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    // Создаем две матрицы 3x3
    matrix* a = matrix_alloc(3, 3);
    matrix* b = matrix_alloc(3, 3);
    if (!a || !b) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    // Устанавливаем значения для матрицы A
    matrix_set(a, 0, 0, 1.0); matrix_set(a, 0, 1, 0.0); matrix_set(a, 0, 2, 0.0);
    matrix_set(a, 1, 0, 0.0); matrix_set(a, 1, 1, 2.0); matrix_set(a, 1, 2, 0.0);
    matrix_set(a, 2, 0, 0.0); matrix_set(a, 2, 1, 0.0); matrix_set(a, 2, 2, -1.0);

    // Устанавливаем значения для матрицы B
    matrix_set(b, 0, 0, 1.0); matrix_set(b, 0, 1, 0.0); matrix_set(b, 0, 2, 0.0);
    matrix_set(b, 1, 0, 0.0); matrix_set(b, 1, 1, 1.0); matrix_set(b, 1, 2, 0.0);
    matrix_set(b, 2, 0, 0.0); matrix_set(b, 2, 1, 0.0); matrix_set(b, 2, 2, 1.0);

    printf("Матрица A:\n");
    matrix_print(a);

    printf("\nМатрица B:\n");
    matrix_print(b);

    // Тестирование сложения
    matrix_add(a, b);
    printf("\nA + B:\n");
    matrix_print(a);

    // Тестирование вычитания
    matrix_sub(a, b);
    printf("\n(A + B) - B:\n");
    matrix_print(a);

    // Тестирование матричной экспоненты
    matrix_exp(a);
    printf("\nЭкспонента матрицы A (exp(A)):\n");
    matrix_print(a);

    // Тестирование метода Гаусса
    matrix* slau = matrix_alloc(4, 3);
    if (!slau) {
        printf("Ошибка выделения памяти\n");
        matrix_free(a);
        matrix_free(b);
        return 1;
    }

    // Пример системы уравнений
    matrix_set(slau, 0, 0, 2.0); matrix_set(slau, 0, 1, 1.0);
    matrix_set(slau, 0, 2, -1.0); matrix_set(slau, 0, 3, 8.0);  // 2x + y - z = 8

    matrix_set(slau, 1, 0, -3.0); matrix_set(slau, 1, 1, -1.0);
    matrix_set(slau, 1, 2, 2.0); matrix_set(slau, 1, 3, -11.0); // -3x - y + 2z = -11

    matrix_set(slau, 2, 0, -2.0); matrix_set(slau, 2, 1, 1.0);
    matrix_set(slau, 2, 2, 2.0); matrix_set(slau, 2, 3, -3.0);  // -2x + y + 2z = -3

    printf("\nСистема линейных уравнений:\n");
    matrix_print(slau);

    if (matrix_gauss(slau) == 0) {
        printf("\nРешение системы:\n");
        printf("x = %g\n", matrix_get(slau, 0, 3));
        printf("y = %g\n", matrix_get(slau, 1, 3));
        printf("z = %g\n", matrix_get(slau, 2, 3));
    } else {
        printf("\nСистема не имеет решения или матрица вырожденная\n");
    }

    matrix_free(a);
    matrix_free(b);
    matrix_free(slau);

    return 0;
}

