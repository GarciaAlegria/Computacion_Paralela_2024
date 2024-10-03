// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Corto 2

#include <stdio.h>
#include <omp.h>
#include <time.h>

// Umbral para evitar la creación excesiva de tareas
#define THRESHOLD 10

// Función recursiva de Fibonacci normal
int fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// Función recursiva de Fibonacci con OpenMP y Threshold
int fib_recursive_omp_fix(int n) {
    if (n <= 1)
        return n;

    // Evitar tareas innecesarias si n es pequeño
    if (n <= THRESHOLD)
        return fib_recursive(n);

    int x, y;
    // Se crean tareas para calcular los valores de Fibonacci de n-1 y n-2
    #pragma omp task shared(x)
    x = fib_recursive_omp_fix(n - 1);
    #pragma omp task shared(y)
    y = fib_recursive_omp_fix(n - 2);
    // Se espera a que ambas tareas terminen
    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    printf("Ingrese un número: ");
    scanf("%d", &n);

    clock_t start = clock(); // Se inicia el contador de tiempo
    #pragma omp parallel
    {
        #pragma omp single
        {
            int result = fib_recursive_omp_fix(n); // Se llama a la función recursiva con OpenMP y Threshold
            clock_t end = clock(); // Se finaliza el contador de tiempo
            double time_taken = (double)(end - start) / CLOCKS_PER_SEC; // Se calcula el tiempo de ejecución

            printf("Fibonacci(%d) = %d\n", n, result);
            printf("Tiempo de ejecución con OpenMP y Threshold: %f segundos\n", time_taken);
        }
    }

    return 0;
}