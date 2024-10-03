#include <stdio.h>
#include <omp.h>
#include <time.h>

// Función recursiva de Fibonacci con OpenMP
int fib_recursive_omp(int n) {
    if (n <= 1)
        return n;
    int x, y;

    #pragma omp task shared(x)
    x = fib_recursive_omp(n - 1);
    #pragma omp task shared(y)
    y = fib_recursive_omp(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    printf("Ingrese un número: ");
    scanf("%d", &n);

    clock_t start = clock();
    #pragma omp parallel
    {
        #pragma omp single
        {
            int result = fib_recursive_omp(n);
            clock_t end = clock();
            double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

            printf("Fibonacci(%d) = %d\n", n, result);
            printf("Tiempo de ejecución con OpenMP: %f segundos\n", time_taken);
        }
    }

    return 0;
}