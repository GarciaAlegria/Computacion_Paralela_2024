// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Hoja de trabajo 2
// Compilar con: mpicc mpi_hello.c -o mpi_hello
// Ejecutar con: mpiexec -n <num_procesos> ./mpi_hello <num_procesos>

#include <stdio.h>
#include <mpi/mpi.h>

// Programa que imprime un mensaje con el número de proceso y el tamaño del grupo
int main(int argc, char** argv) {
    int rank, size;

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtiene el número de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el tamaño del grupo

    // Verifica el número de argumentos de línea de comandos
    if (argc != 2) {
        if (rank == 0) {
            printf("Uso: mpiexec -n <num_procesos> %s <num_procesos>\n", argv[0]); // Imprime el uso correcto
        }
        MPI_Finalize(); // Finaliza MPI
        return 1;
    }

    int num_procesos; // Número de procesos especificado en la línea de comandos
    sscanf(argv[1], "%d", &num_procesos); // Lee el número de procesos de la línea de comandos

    // Verifica que el número de procesos coincida con el especificado
    if (num_procesos != size) {
        if (rank == 0) {
            printf("El número de procesos especificado debe coincidir con -n en mpiexec.\n"); // Imprime un mensaje de error
        }
        MPI_Finalize(); // Finaliza MPI
        return 1; // Retorna un código de error
    }

    // Imprime un mensaje con el número de proceso y el tamaño del grupo
    printf("Hello World, I'm process %d of %d!\n", rank, size);

    // Finalización de MPI
    MPI_Finalize();
    return 0;
}