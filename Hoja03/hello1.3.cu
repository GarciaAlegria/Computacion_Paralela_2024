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

   if (idx == 1023) {
    printf("Thread 1023, Name: Abner Garcia, Carnet: 21285\n");
   }
}

int main()
{
  // Configurar 2 bloques de 1024 hilos cada uno
  hello<<<2, 1024>>>();
  cudaDeviceSynchronize(); 
  return 0;
}