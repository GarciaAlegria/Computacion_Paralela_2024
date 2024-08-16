// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Laboratorio 1

#include <stdio.h> // Incluye la biblioteca estándar de entrada/salida
#include <stdlib.h> // Incluye la biblioteca estándar de utilidades (para atoi)
#include <math.h> // Incluye la biblioteca matemática (aunque no se usa en este código)
#include <omp.h> // Incluye la biblioteca OpenMP para la programación paralela

int main(int argc, char *argv[]) {
    double factor = 1.0; // Inicializa el factor con 1.0, que se alternará entre 1.0 y -1.0
    double sum = 0.0; // Inicializa la suma con 0.0
    int n; // Declaración de la variable n que almacenará el número de términos
    int thread_count; // Declaración de la variable thread_count que almacenará el número de hilos

    // Verifica si se han pasado argumentos de línea de comandos
    if (argc > 1) {
        n = atoi(argv[1]); // Convierte el primer argumento de línea de comandos a un entero
        thread_count = atoi(argv[2]); // Convierte el segundo argumento de línea de comandos a un entero
    }

    // Bucle paralelo para calcular la serie de Leibniz para la aproximación de pi
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += factor / (2 * i + 1); // Añade el término correspondiente a la suma
        factor = -factor; // Alterna el signo del factor
    }

    double pi_aprox = 4.0 * sum; // Calcula la aproximación de pi multiplicando la suma por 4
    printf("Valor aproximado pi: %lf \n", pi_aprox); // Imprime el valor aproximado de pi

    return 0; // Finaliza el programa
}