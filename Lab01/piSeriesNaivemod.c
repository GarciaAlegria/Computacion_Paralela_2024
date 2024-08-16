#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    // valores predeterminados 
    double factor = 1.0;
    double sum = 0.0;
    int n;
    int thread_count;
    int block_size = 128; // Tamaño de bloque por defecto
    char *schedule_type = "auto"; // Planificación por defecto

    // Se verifica que se ingresen parámetros 
    if (argc > 1) {
        n = atoi(argv[1]);
        thread_count = atoi(argv[2]);
        if (argc > 3) {
            block_size = atoi(argv[3]);
            if (argc > 4) {
                schedule_type = argv[4];
            }
        }
    } else {
        printf("Uso: %s <n> <num_threads> [block_size] [schedule_type]\n", argv[0]);
        return 1;
    }

    double start_time, end_time;

    // Configura la planificación
    omp_set_schedule(omp_sched_static, block_size); // Planificación estática
    if (strcmp(schedule_type, "dynamic") == 0) {
        omp_set_schedule(omp_sched_dynamic, block_size);
    } else if (strcmp(schedule_type, "guided") == 0) {
        omp_set_schedule(omp_sched_guided, block_size);
    } else if (strcmp(schedule_type, "auto") == 0) {
        omp_set_schedule(omp_sched_auto, 0);
    }

    // Medir tiempo
    start_time = omp_get_wtime();

    #pragma omp parallel for num_threads(thread_count) reduction(+:sum) private(factor) schedule(runtime)
    for (int i = 0; i < n; i++) {
        factor = (i % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * i + 1);
    }

    end_time = omp_get_wtime();

    double pi_aprox = 4.0 * sum;
    printf("Valor aproximado pi: %.15lf \n", pi_aprox);
    printf("Tiempo de ejecución: %lf segundos\n", end_time - start_time);

    return 0;
}