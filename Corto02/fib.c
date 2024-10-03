// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Corto 2

#include <stdio.h>
#include <time.h>

// Función recursiva de Fibonacci
int fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2); // Se llama a la función recursiva
}

// Función principal
int main() {
    int n;
    printf("Ingrese un número: ");
    scanf("%d", &n); // Se lee el número ingresado por el usuario

    clock_t start = clock(); // Se inicia el contador de tiempo
    int result = fib_recursive(n); // Se llama a la función recursiva
    clock_t end = clock(); // Se finaliza el contador de tiempo

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC; // Se calcula el tiempo de ejecución
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Tiempo de ejecución: %f segundos\n", time_taken);

    return 0;
}