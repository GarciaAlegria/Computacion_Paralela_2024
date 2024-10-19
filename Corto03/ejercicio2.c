// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Corto 3

#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tamaño del arreglo a utilizar
#define ARRAY_SIZE 5000

// Programa principal que calcula la suma, el máximo y el mínimo de un arreglo de enteros
int main(int argc, char** argv) {
    int rank, size; // Rank y tamaño del comunicador
    int *array = NULL; // Arreglo de enteros
    int local_sum = 0, global_sum = 0; // Suma local y global
    int local_max = 0, global_max = 0; // Máximo local y global
    int local_min = 0, global_min = 0; // Mínimo local y global
    
    MPI_Init(&argc, &argv); // Inicializar MPI y obtener rank y size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener rank
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener size
 
    // Array initialization
    if (rank == 0) {
        array = (int*) malloc(ARRAY_SIZE * sizeof(int)); // espacio para el arreglo
        srand(time(NULL)); // establecer la semilla para los números aleatorios

        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % 1000; // Valores enteros aleatorios entre 0 y 999
        }
    }

    // arreglo local para cada proceso para almacenar una parte del arreglo
    int *local_array = (int*) malloc(ARRAY_SIZE / size * sizeof(int));

    // Distribuir el arreglo entre los procesos
    MPI_Scatter(array, ARRAY_SIZE / size, MPI_INT, local_array, ARRAY_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular la suma, el máximo y el mínimo local
    local_sum = 0;
    local_max = local_array[0];
    local_min = local_array[0];
    // Calcular la suma, el máximo y el mínimo local
    for (int i = 0; i < ARRAY_SIZE / size; i++) {
        local_sum += local_array[i];
        if (local_array[i] > local_max) local_max = local_array[i];
        if (local_array[i] < local_min) local_min = local_array[i];
    }

    // Reducir la suma, el máximo y el mínimo local a la suma, el máximo y el mínimo global
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // Imprimir la suma, el máximo y el mínimo global
    if (rank == 0) {
        printf("Global sum: %d\n", global_sum);
        printf("Global max: %d\n", global_max);
        printf("Global min: %d\n", global_min);
    }

    // Liberar memoria
    if (rank == 0) {
        free(array);
    }
    free(local_array); // Liberar memoria del arreglo local

    MPI_Finalize(); // Finalizar MPI
    return 0; // Retornar 0 al sistema operativo para indicar que no hubo errores
}
