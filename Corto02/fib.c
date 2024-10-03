#include <stdio.h>
#include <time.h>

// Función recursiva de Fibonacci
int fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
    int n;
    printf("Ingrese un número: ");
    scanf("%d", &n);

    clock_t start = clock();
    int result = fib_recursive(n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Tiempo de ejecución: %f segundos\n", time_taken);

    return 0;
}