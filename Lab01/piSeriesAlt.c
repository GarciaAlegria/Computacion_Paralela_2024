// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Laboratorio 1

#include <stdio.h> // Incluye la biblioteca estándar de entrada/salida
#include <omp.h> // Incluye la biblioteca OpenMP para la programación paralela

int main(int argc, char const *argv[])
{
    long n = 10000000; // Número de términos en la serie
    double pi = 0.0; // Inicializa la variable pi con 0.0
    int num_threads = 2; // Número de hilos a utilizar

    omp_set_num_threads(num_threads); // Establece el número de hilos para las regiones paralelas siguientes

    double start_time = omp_get_wtime(); // Obtiene el tiempo de inicio

    #pragma omp parallel for reduction(+:pi) // Bucle paralelo con reducción para la variable pi
    for (long i = 0; i < n; i++) // Itera desde 0 hasta n-1
    {
        double term = 1.0 / (2 * i + 1); // Calcula el término correspondiente de la serie
        if (i % 2 == 1) { // Si el índice es impar
            term = -term; // Alterna el signo del término
        }

        pi += term; // Añade el término a la suma de pi
    }

    double end_time = omp_get_wtime(); // Obtiene el tiempo de finalización

    pi *= 4.0; // Multiplica la suma por 4 para obtener la aproximación de pi

    printf("Valor aproximado de pi con n = %ld y %d hilos = %.15f\n", n, num_threads, pi); // Imprime el valor aproximado de pi
    printf("Tiempo de ejecucion: %.15f segundos\n", end_time - start_time); // Imprime el tiempo de ejecución

    return 0; // Finaliza el programa
}