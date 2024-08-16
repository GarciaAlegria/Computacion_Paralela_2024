// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Laboratorio 1

#include <stdio.h> // Incluye la biblioteca estándar de entrada/salida
#include <stdlib.h> // Incluye la biblioteca estándar de utilidades (para atoi)
#include <string.h> // Incluye la biblioteca estándar de manipulación de cadenas
#include <math.h> // Incluye la biblioteca matemática (aunque no se usa en este código)
#include <omp.h> // Incluye la biblioteca OpenMP para la programación paralela

int main(int argc, char *argv[]) {
    // Valores predeterminados
    double factor = 1.0; // Inicializa el factor con 1.0, que se alternará entre 1.0 y -1.0
    double sum = 0.0; // Inicializa la suma con 0.0
    int n; // Declaración de la variable n que almacenará el número de términos
    int thread_count; // Declaración de la variable thread_count que almacenará el número de hilos
    int block_size = 128; // Tamaño de bloque por defecto
    char *schedule_type = "auto"; // Planificación por defecto

    // Se verifica que se ingresen parámetros
    if (argc > 1) {
        n = atoi(argv[1]); // Convierte el primer argumento de línea de comandos a un entero
        thread_count = atoi(argv[2]); // Convierte el segundo argumento de línea de comandos a un entero
        if (argc > 3) {
            block_size = atoi(argv[3]); // Convierte el tercer argumento de línea de comandos a un entero
            if (argc > 4) {
                schedule_type = argv[4]; // Asigna el cuarto argumento de línea de comandos a la variable schedule_type
            }
        }
    } else {
        // Si no se ingresan los parámetros necesarios, muestra el uso correcto del programa
        printf("Uso: %s <n> <num_threads> [block_size] [schedule_type]\n", argv[0]);
        return 1; // Termina el programa con un código de error
    }

    double start_time, end_time; // Variables para medir el tiempo de ejecución

    // Configura la planificación
    omp_set_schedule(omp_sched_static, block_size); // Planificación estática por defecto
    if (strcmp(schedule_type, "dynamic") == 0) {
        omp_set_schedule(omp_sched_dynamic, block_size); // Planificación dinámica
    } else if (strcmp(schedule_type, "guided") == 0) {
        omp_set_schedule(omp_sched_guided, block_size); // Planificación guiada
    } else if (strcmp(schedule_type, "auto") == 0) {
        omp_set_schedule(omp_sched_auto, 0); // Planificación automática
    }

    // Medir tiempo
    start_time = omp_get_wtime(); // Obtiene el tiempo de inicio

    // Bucle paralelo para calcular la serie de Leibniz para la aproximación de pi
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum) private(factor) schedule(runtime)
    for (int i = 0; i < n; i++) {
        factor = (i % 2 == 0) ? 1.0 : -1.0; // Alterna el signo del factor
        sum += factor / (2 * i + 1); // Añade el término correspondiente a la suma
    }

    end_time = omp_get_wtime(); // Obtiene el tiempo de finalización

    double pi_aprox = 4.0 * sum; // Calcula la aproximación de pi multiplicando la suma por 4
    printf("Valor aproximado pi: %.15lf \n", pi_aprox); // Imprime el valor aproximado de pi
    printf("Tiempo de ejecución: %lf segundos\n", end_time - start_time); // Imprime el tiempo de ejecución

    return 0; // Finaliza el programa
}