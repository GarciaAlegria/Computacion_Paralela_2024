# Laboratorio 2 Programación Paralela y Distribuida

## Integrantes

Abner Iván Garcia Alegría - 21285
Oscar Esteban Donis Martinez 21610

## Descripción del Laboratorio 2

Para este laboratorio se busca crear un archivo con n números aleatorios segun el usuario desee, el cual en base a n se creará n números del 0 al 99 de forma aleatoria y se almacenará en un archivo csv llamado nums.csv, por lo cual leeremos este archivo y en el mismo programa debemos ordenar ese archivo de forma ascendente el cual esta en el archivo csv llamado nums_orders.csv esa es para la parte secuencial, ahora para la parte paralela se busca usar la biblioteca de OpenMP para poder paralelizar lo que sea necesario en el código por lo que la generación de n números de forma aleatoria se encuentra en el archivo numspa.csv y luego su forma ordenada usando openMP esta en el archivo nums_sorted_parallel.csv.

# Instrucciones de compilación

Antes de iniciar a compila asegurarse de tener instalado en su máquina la libreria de openmp para poder correr los archivos que posean paralelización, para tenerla pueden usar el siguiente comando:

```shell
sudo apt install fopenmp
```

## Archivo sequentialpart1.cpp

A continuación se muestra como se debe compilar

```shell
g++ -o parte1 sequentialpart1.cpp && ./parte1
```

## Archivo parallelpart2.cpp

a continuación se muestra como se debe compilar

```shell
g++ -fopenmp parallelpart2.cpp -o parte2 && ./parte2
```