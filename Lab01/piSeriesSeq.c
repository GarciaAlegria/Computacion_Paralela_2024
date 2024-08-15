#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {
    double factor = 1.0;
    double sum = 0.0;
    int n;

     
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    for (int i = 0; i < n; i++) {
        sum += factor/(2*i+1);
        factor = -factor;
    }
    double pi_aprox = 4.0 * sum;
    printf("Valor aproximado pi: %lf \n",pi_aprox );

    return 0;
}