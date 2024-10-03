// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Corto 2

#include <stdio.h>
#include <omp.h>
#include <time.h>

// Función recursiva de Fibonacci con OpenMP
int fib_recursive_omp(int n) {
    if (n <= 1)
        return n; 
    int x, y; // Variables para almacenar los resultados
// Se crean tareas para calcular los valores de Fibonacci de n-1 y n-2
    #pragma omp task shared(x)
    x = fib_recursive_omp(n - 1);
    #pragma omp task shared(y)
    y = fib_recursive_omp(n - 2);
    // Se espera a que ambas tareas terminen
    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    printf("Ingrese un número: ");
    scanf("%d", &n); // Se lee el número ingresado por el usuario

    clock_t start = clock(); // Se inicia el contador de tiempo
    #pragma omp parallel
    {
        #pragma omp single
        {
            int result = fib_recursive_omp(n); // Se llama a la función recursiva con OpenMP
            clock_t end = clock(); // Se finaliza el contador de tiempo
            double time_taken = (double)(end - start) / CLOCKS_PER_SEC; // Se calcula el tiempo de ejecución

            printf("Fibonacci(%d) = %d\n", n, result);
            printf("Tiempo de ejecución con OpenMP: %f segundos\n", time_taken);
        }
    }

    return 0;
}