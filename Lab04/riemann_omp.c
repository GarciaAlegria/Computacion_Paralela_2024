// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Este es el OpenMP
// Laboratorio 4

#include <stdio.h> // Librería estándar de entrada y salida
#include <stdlib.h> // Librería estándar de C
#include <math.h> // Librería de matemáticas
#include <sys/time.h> // Librería de tiempo
#include <omp.h> // Librería para OpenMP

// Declaración de funciones a utilizar en el programa
double cuadratic_func(double x); // Función cuadrática (x^2)
double trapezoides(double (*func)(double), double a, double b, int n, double h); // Función para calcular la integral en el intervalo [a, b]

// Número de subdivisiones (n) para el cálculo de la integral
int n = 10e6;

int main(int argc, char *argv[]) {
    // Límites del intervalo de integración [a, b]
    double a = 1.0; // Límite inferior del intervalo de integración (por defecto 1.0)
    double b = 1.0; // Límite superior del intervalo de integración (por defecto 1.0)

    // Verificación de argumentos de línea de comandos para los límites del intervalo de integración
    if (argc > 1) {
        a = atof(argv[1]); // Convertir el primer argumento a un número flotante
        b = atof(argv[2]); // Convertir el segundo argumento a un número flotante
    }

    double h = (b - a) / n; // Ancho de cada subintervalo
    double global_sum = 0.0; // Suma total

    // Inicio del contador de tiempo para calcular el tiempo de ejecución
    struct timeval start, end; // Estructuras para almacenar el tiempo
    gettimeofday(&start, NULL); // Obtener el tiempo actual

    // Cálculo de la integral usando OpenMP para paralelizar
    #pragma omp parallel
    {
        double local_sum = 0.0; // Suma local para cada hilo

        #pragma omp for // Paralelización de la región crítica
        for (int i = 0; i < n; i++) {
            double x = a + i * h; // Cálculo del valor de x
            local_sum += trapezoides(cuadratic_func, x, x + h, 1, h); // Cálculo de la integral en el subintervalo
        }

        // Suma local de cada hilo a la suma global de forma segura
        #pragma omp critical // Región crítica para la suma global de las integrales locales
        global_sum += local_sum; // Suma de las integrales locales
    }

    // Fin del contador de tiempo
    gettimeofday(&end, NULL); // Obtener el tiempo actual
    double execution_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000; // Calcular el tiempo de ejecución

    // Impresión del resultado
    printf("Para n = %d, nuestra aproximación de la integral de %f a %f es = %f\n", n, a, b, global_sum); // Imprimir el resultado de la integral aproximada
    printf("Tiempo de ejecución: %f segundos\n", execution_time); // Imprimir el tiempo de ejecución

    return 0; // Retornar 0 al sistema
}

// Función para calcular la integral en el intervalo [a, b]
double trapezoides(double (*func)(double), double a, double b, int n, double h) {
    double sum = 0.0; // Suma de la integral 
    sum = (func(a) + func(b)) / 2.0; // Calcular la integral en los extremos del intervalo
    for (int i = 1; i < n; i++) {
        double x = a + i * h; // Calcular el valor de x
        sum += func(x); // Calcular la integral en el subintervalo
    }
    sum *= h; // Multiplicar por el ancho del subintervalo
    return sum; // Retornar la suma de la integral
}

// Función cuadrática (x^2) para calcular la integral de la función en el intervalo [a, b]
double cuadratic_func(double x) {
    return x * x; // Retornar el valor de x^2 para un valor de x dado
}
