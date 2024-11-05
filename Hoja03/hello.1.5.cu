/*
 ============================================================================
 Author        : G. Barlas
 Version       : 1.0
 Last modified : December 2014
 License       : Released under the GNU GPL 3.0
 Description   :
 To build use  : nvcc hello.cu -o hello -arch=sm_20
 ============================================================================
 */
#include <stdio.h>
#include <cuda.h>

__global__ void hello()
{
   int idx = blockIdx.x * blockDim.x + threadIdx.x;
   printf("Hello world from thread %d, Name: Abner Garcia, Carnet: 21285\n", idx);

   if (idx == 2047) {
    printf("Thread 2047, Name: Abner Garcia, Carnet: 21285\n");
   }
}

int main()
{
  // Configurar 1 bloque de 2048 hilos
  hello<<<1, 2048>>>();
  cudaDeviceSynchronize(); 
  return 0;
}