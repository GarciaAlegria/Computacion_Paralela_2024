#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    int n;
    int thread_count;

    if (argc > 1) {
        n = atoi(argv[1]);
        thread_count = atoi(argv[2]);
    }

    int block_size = 128;

    #pragma omp parallel for num_threads (thread_count) reduction(+:sum) private(factor) schedule(auto)
    for (int i = 0; i < n; i++) {
        
        if (i % 2 == 0){
            factor = 1.0;
        }else{
            factor =-1.0;
        }

        sum += factor/(2*i+1);

    }
    double pi_aprox = 4.0 * sum;
    printf("Valor aproximado pi: %lf \n",pi_aprox );

    return 0;
}