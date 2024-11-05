/*
 ============================================================================
 Author        : G. Barlas
 Version       : 1.0
 Last modified : December 2014
 License       : Released under the GNU GPL 3.0
 Description   :
 To build use  : nvcc hello2.cu -o hello2 -arch=sm_20
 ============================================================================
 */
#include <stdio.h>
#include <cuda.h>

__global__ void hello ()
{
  int myID = (blockIdx.z * gridDim.x * gridDim.y  +
              blockIdx.y * gridDim.x +
              blockIdx.x ) * blockDim.x * blockDim.y * blockDim.z +
              threadIdx.z *  blockDim.x * blockDim.y +
              threadIdx.y * blockDim.x +
              threadIdx.x;

//  Simplification of above
  //grid: 3D --- z,y,x: all dims and blockids
  //block: 1D -- x
  //int myID = ( blockIdx.z * gridDim.x * gridDim.y  +
  //             blockIdx.y * gridDim.x +
  //             blockIdx.x ) * blockDim.x +
  //             threadIdx.x;

  // Obtén el número total de hilos en la grilla
  int totalThreads = gridDim.x * gridDim.y * gridDim.z * blockDim.x * blockDim.y * blockDim.z;

  // Comprueba si este hilo tiene el ID global máximo
  if (myID == totalThreads - 1)
  {
    printf ("Hello world from %i by Abner Garcia - 21285\n", myID);
  }
}

int main ()
{
  cudaDeviceProp prop;
  cudaGetDeviceProperties(&prop, 0);  // Obtener las propiedades de la GPU 0

  printf("Max Threads Per Block (x): %d\n", prop.maxThreadsDim[0]); //1024
  printf("Max Threads Per Block (y): %d\n", prop.maxThreadsDim[1]); //1024
  printf("Max Threads Per Block (z): %d\n", prop.maxThreadsDim[2]); //64
  printf("Max Blocks Per Grid (x): %d\n", prop.maxGridSize[0]); // 2147483647
  printf("Max Blocks Per Grid (y): %d\n", prop.maxGridSize[1]); // 65535
  printf("Max Blocks Per Grid (z): %d\n", prop.maxGridSize[2]); // 65535
  // Definir el número total de datos
  int maxThreadsX = 1024;
  int maxThreadsY = 1024;
  int maxThreadsZ = 64;
  int maxBlocksX = 2147483647;
  int maxBlocksY = 65535;
  int maxBlocksZ = 65535;
  int totalData = 100000;
  // obtener el número total de hilos en la grilla y el número de hilos por bloque
  dim3 threadsPerBlock(
    min(totalData, maxThreadsX),
    min(1, maxThreadsY),          
    min(1, maxThreadsZ)
  );
  // obtener el número de bloques por grilla y el número de bloques por eje
  dim3 blocksPerGrid(
    min((totalData + threadsPerBlock.x - 1) / threadsPerBlock.x, maxBlocksX),
    min(1, maxBlocksY),
    min(1, maxBlocksZ)
  );

  hello <<< blocksPerGrid, threadsPerBlock >>> ();
  cudaDeviceReset();

  return 0;
}