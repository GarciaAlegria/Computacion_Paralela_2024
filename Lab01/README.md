# Laboratorio 1 Programación Paralela y Distribuida
## Integrante
Abner Iván Garcia Alegría - 21285
## Descripción del Laboratorio 1
Para este laboratorio se busca aproximar el valor de pi, lo cual se utiliza la serie de Leibniz que gracias a ella nos permite una aproximación del valor de pi, además se realiza una implementación de un algoritmo secuencial y su transformación en
versión paralela usando la biblioteca de OpenMP.

![image](https://github.com/user-attachments/assets/d5d682b2-b967-44d2-939f-efaa03535980)

# Instrucciones de compilación
Antes de iniciar a compila asegurarse de tener instalado en su máquina la libreria de openmp para tenerla pueden usar el siguiente comando
```shell
sudo apt install fopenmp
```
## Archivo piSeriesSeq.c
a continuación se muestra como se debe compilar
```shell
gcc - o  piSeriesSeq piSeriesSeq.c
./piSeriesSeq <valor n> <threds>
```
## Archivo piSeriesNaive.c
a continuación se muestra como se debe compilar
```shell
gcc - o  piSeriesNaive piSeriesNaive.c -fopenmp
./piSeriesNaive <valor n> <threds>
```

## Archivo piSeriesNaivemod.c
a continuación se muestra como se debe compilar
```shell
gcc - o  piSeriesNaivemod piSeriesNaivemod.c -fopenmp
./piSeriesNaivemod <valor n> <threds>
```
compilar con el tipo (static, dynamic, guided, auto)
```shell
gcc - o  piSeriesNaivemod piSeriesNaivemod.c -fopenmp
./piSeriesNaivemod <valor n> <threds> <tipo>
```

## Archivo piSeriesAlt.c
a continuación se muestra como se debe compilar
```shell
gcc - o  piSeriesAlt piSeriesAlt.c -fopenmp
./piSeriesAlt
```
Compilar con -O2
```shell
gcc - o  piSeriesAlt piSeriesAlt.c -fopenmp -O2
./piSeriesAlt
```
