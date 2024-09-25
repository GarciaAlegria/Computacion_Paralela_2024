// Universidad del Valle de Guatemala
// Programación Paralela y Distribuida sección 10
// Abner Ivan Garcia Alegria 21285
// Hoja de trabajo 2
// Compilar con: mpicc mpi_hello_2.c -o mpi_hello_2
// Ejecutar con: mpiexec -n <num_procesos> ./mpi_hello_2 <num_procesos>

#include <stdio.h>
#include <string.h>
#include <mpi/mpi.h>

// Programa que envía mensajes de procesos distintos al proceso 0
int main(int argc, char** argv) {
    int rank, size; // Número de proceso y tamaño del grupo

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtiene el número de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el tamaño del grupo

    // Verifica que haya al menos 2 procesos para la comunicación
    if (size < 2) {
        if (rank == 0) {
            printf("Este programa requiere al menos 2 procesos.\n"); // Imprime un mensaje de error
        }
        MPI_Finalize(); // Finaliza MPI
        return 1; // Retorna un código de error
    }

    char message[100]; // Mensaje a enviar 
    sprintf(message, "I am procces %d", rank); // Crea un mensaje con el número de proceso
    if(rank == 0){
        printf("Hi, I'm process %d of %d and I'm receiving!\n", rank, size); // Imprime un mensaje de recepción
    }else{

    printf("Hi, I'm process %d of %d and I'm sending a message to 0!\n", rank, size);
    }

    if (rank == 0) {
        // Proceso 0 recibe mensajes de otros procesos y los muestra
        for (int sender = 1; sender < size; sender++) {
            MPI_Recv(message, sizeof(message), MPI_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Recibe un mensaje
            printf("Greetings process 0, %s\n", message); // Muestra el mensaje recibido
        }
    } else {
        // Procesos distintos de 0 envían mensajes al proceso 0
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("Proceso %d envió el mensaje: \"%s\" a proceso 0\n", rank, message); // Muestra el mensaje enviado
    }

    // Finalización de MPI
    MPI_Finalize();
    return 0;
}