#include <stdio.h>
#include <omp.h>

int main(int argc, char const *argv[])
{

    long n = 10000000; 
    double pi = 0.0;
    int num_threads = 2; 

    omp_set_num_threads(num_threads); 

    double start_time = omp_get_wtime(); 

    #pragma omp parallel for reduction(+:pi) 

    for (long i = 0; i < n; i++) 
    {
        double term = 1.0 / (2*i+1); 
        if(i % 2 == 1) {
            term = -term; 
        }

        pi += term; 
    }

    double end_time = omp_get_wtime(); 

    pi *= 4.0; 

    printf("Valor aproximado de pi con n = %ld y %d hilos = %.15f\n", n, num_threads, pi);
    printf("Tiempo de ejecucion: %.15f segundos\n", end_time - start_time);

    return 0;
}