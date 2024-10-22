// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Laboratorio 4

// Se importan librerias necesarias para el programa y se definen las funciones a utilizar en el programa
#include <stdio.h> // Libreria estandar de entrada y salida
#include <stdlib.h> // Libreria estandar de C
#include <mpi/mpi.h> // Libreria de MPI
#include <math.h> // Libreria de matematicas
#include <sys/time.h> // Libreria de tiempo

// Declaración de funciones a utilizar
double cuadratic_func(double x); // Función cuadrática (x^2)
double trapezoides(double (*func)(double), double a, double b, int n, double h); // Función para calcular la integral de una función en el intervalo [a, b]

// Número de subdivisiones (n) para el cálculo de la integral
int n = 10e6;

int main(int argc, char *argv[]) // Función principal
{
    // Inicialización de MPI
    MPI_Init(&argc, &argv);

    int rank, size; // Rank y tamaño del comunicador
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener rank
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener size

    // límites del intervalo de integración [a, b]
    double a = 1.0;
    double b = 1.0;

    // Verificación de argumentos de línea de comandos para los límites del intervalo de integración
    if (argc > 1) {
        a = atof(argv[1]); // Convertir el primer argumento a un número flotante
        b = atof(argv[2]); // Convertir el segundo argumento a un número flotante
    }

    double h = (b - a) / n; // Ancho de cada subintervalo
    double local_sum = 0.0; // Suma local

    // Inicio del contador de tiempo
    struct timeval start, end; // Estructuras para almacenar el tiempo
    gettimeofday(&start, NULL); // Obtener el tiempo actual

    // Cálculo de la integral en paralelo utilizando la regla de los trapecios
    for (int i = rank; i < n; i += size) {
        double x = a + i * h; // Calcular el valor de x
        local_sum += trapezoides(cuadratic_func, x, x + h, 1, h); // Calcular la integral de la función cuadrática en el intervalo [x, x + h]
    }

    double global_sum; // Suma global de las integrales locales
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); // Reducción de las sumas locales a la suma global

    // Fin del contador de tiempo para calcular el tiempo de ejecución
    gettimeofday(&end, NULL); // Obtener el tiempo actual
    double execution_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000; // Calcular el tiempo de ejecución

    // Impresión del resultado y tiempo de ejecución
    if (rank == 0) {
        printf("Para n = %d, nuestra aproximación de la integral reimann de %f a %f es = %f\n", n, a, b, global_sum); // Imprimir el resultado de la integral aproximada
        printf("Tiempo de ejecución: %f segundos\n", execution_time); // Imprimir el tiempo de ejecución del programa en segundos
    }

    // Finalización de MPI
    MPI_Finalize();

    return 0;
}

// Función para calcular la integral de una función en el intervalo [a, b]
double trapezoides(double (*func)(double), double a, double b, int n, double h) {
    double sum = 0.0; // Suma de las áreas de los trapecios
    sum = (func(a) + func(b)) / 2.0; // Calcular el área del primer trapecio
    // Calcular el área de los trapecios restantes
    for (int i = 1; i < n; i++) {
        double x = a + i * h; // Calcular el valor de x
        sum += func(x); // Calcular el área del trapecio y sumarlo a la suma total
    }

    sum *= h; // Multiplicar la suma por el ancho de los trapecios
    return sum; // Retornar la suma de las áreas de los trapecios
}

// Función cuadrática (x^2) para calcular la integral de la función en el intervalo [a, b]
double cuadratic_func(double x) {
    return x * x; // Retornar el valor de la función cuadrática
}