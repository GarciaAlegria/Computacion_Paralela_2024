#include <stdio.h>
#include <mpi/mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verifica el número de argumentos de línea de comandos
    if (argc != 2) {
        if (rank == 0) {
            printf("Uso: mpiexec -n <num_procesos> %s <num_procesos>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int num_procesos;
    sscanf(argv[1], "%d", &num_procesos);

    // Verifica que el número de procesos coincida con el especificado
    if (num_procesos != size) {
        if (rank == 0) {
            printf("El número de procesos especificado debe coincidir con -n en mpiexec.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Imprime un mensaje con el número de proceso y el tamaño del grupo
    printf("Hello World, I'm process %d of %d!\n", rank, size);

    // Finalización de MPI
    MPI_Finalize();
    return 0;
}