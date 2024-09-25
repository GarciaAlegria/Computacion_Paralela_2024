#include <stdio.h>
#include <string.h>
#include <mpi/mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verifica que haya al menos 2 procesos para la comunicación
    if (size < 2) {
        if (rank == 0) {
            printf("Este programa requiere al menos 2 procesos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    char message[100];
    sprintf(message, "I am procces %d", rank);
    if(rank == 0){
        printf("Hi, I'm process %d of %d and I'm receiving!\n", rank, size);
    }else{

    printf("Hi, I'm process %d of %d and I'm sending a message to 0!\n", rank, size);
    }

    if (rank == 0) {
        // Proceso 0 recibe mensajes de otros procesos y los muestra
        for (int sender = 1; sender < size; sender++) {
            MPI_Recv(message, sizeof(message), MPI_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Greetings process 0, %s\n", message);
        }
    } else {
        // Procesos distintos de 0 envían mensajes al proceso 0
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("Proceso %d envió el mensaje: \"%s\" a proceso 0\n", rank, message);
    }

    // Finalización de MPI
    MPI_Finalize();
    return 0;
}