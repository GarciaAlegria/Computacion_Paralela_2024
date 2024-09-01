/**
 * Universidad del Valle de Guatemala
 * Programación Paralela y Distribuida sección 10
 * Abner Ivan Garcia Alegria 21285
 * Oscar Esteban Donis Martinez 21610
 * Laboratorio 2
 */

#include <iostream> // cout, cin
#include <fstream> // ofstream, ifstream
#include <cstdlib> // srand, rand
#include <ctime> // time
#include <sstream> // stringstream
#include <vector> // vector
#include <algorithm> // sort
#include <omp.h> // OpenMP

using namespace std; // std::cout, std::cin
// Función para determinar si un número es primo
bool isPrime(int number) {
    if (number == 0 || number == 1) {
        return false; // 0 y 1 no son primos
    }
    int divisor; // Variable para almacenar el divisor
    for (divisor = number / 2; number % divisor != 0; --divisor) {
        ;
    }
    if (divisor != 1) {
        return false; // Si encontramos un divisor diferente de 1 y number, entonces no es primo
    } else {
        return true; // Si no encontramos ningún divisor diferente de 1 y number, entonces es primo
    }
}
// Función para ordenar un array de enteros de forma paralela
void par_qsort(int *data, int lo, int hi) {
    if (lo < hi) {
        int l = lo; // Variable para el índice inferior
        int h = hi; // Variable para el índice superior
        int p = data[(hi + lo) / 2]; // Variable para el pivote

        while (l <= h) {
            while (data[l] < p) l++; // Mientras el valor en el índice inferior sea menor al pivote, incrementar el índice inferior
            while (data[h] > p) h--; // Mientras el valor en el índice superior sea mayor al pivote, decrementar el índice superior
            // Si el índice inferior es menor o igual al índice superior, intercambiar los valores en los índices inferior y superior
            if (l <= h) {
                int tmp = data[l]; // Variable temporal para intercambiar los valores
                data[l] = data[h]; // Intercambiar los valores
                data[h] = tmp; // Intercambiar los valores
                l++; h--; // Incrementar el índice inferior y decrementar el índice superior
            }
        }
        int Theshold = 100;  // Tamaño del array para el cual se ejecutará el algoritmo de forma paralela

        if (hi - lo < Theshold) {
            par_qsort(data, lo, h); // Llamada recursiva para ordenar la mitad inferior del array
            par_qsort(data, l, hi); // Llamada recursiva para ordenar la mitad superior del array
            
        } else {
            #pragma omp task shared(data) // Crear una tarea compartiendo el array de datos
            par_qsort(data, lo, h); // Llamada recursiva para ordenar la mitad inferior del array
            
            #pragma omp task shared(data)  // Crear una tarea compartiendo el array de datos
            par_qsort(data, l, hi); // Llamada recursiva para ordenar la mitad superior del array
        }

        
    }
}

// Función principal
int main() {
    int N; // Variable para almacenar la cantidad de números aleatorios a generar
    cout << "Ingrese la cantidad de números aleatorios a generar: "; // Solicitar al usuario la cantidad de números aleatorios a generar
    cin >> N; // Leer la cantidad de números aleatorios a generar

    double start_gen = omp_get_wtime(); // Iniciar el cronómetro para medir el tiempo de generación de números

    srand(time(0)); // Semilla para generar números aleatorios
    int *numbers = new int[N]; // Array para almacenar los números aleatorios
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 100; // Generar un número aleatorio entre 0 y 99
    }

    double end_gen = omp_get_wtime(); // Detener el cronómetro para medir el tiempo de generación de números
    double time_gen = (end_gen - start_gen) * 1000; // Calcular el tiempo de generación de números en milisegundos
    cout << "Tiempo de generación de números: " << time_gen << " milisegundos." << endl; // Mostrar el tiempo de generación de números

    ofstream outFile("numspa.csv"); // Crear un archivo para almacenar los números aleatorios
    for (int i = 0; i < N; i++) {
        outFile << numbers[i]; // Escribir el número en el archivo
        if (i < N - 1) {
            outFile << ","; // Si no es el último número, escribir una coma
        }
    }
    outFile.close(); // Cerrar el archivo

    ifstream inFile("numspa.csv"); // Abrir el archivo con los números aleatorios
    vector<int> numbersVector; // Vector para almacenar los números del archivo
    if (inFile.is_open()) {
        string line; // Variable para leer una línea del archivo
        while (getline(inFile, line, ',')) {
            int number; // Variable para almacenar el número
            stringstream(line) >> number; // Convertir la línea a un número
            numbersVector.push_back(number); // Agregar el número al vector
        }
        inFile.close(); // Cerrar el archivo
    } else {
        cout << "ERROR: No se pudo abrir el archivo." << endl; // Mostrar un mensaje de error si no se pudo abrir el archivo
        return 1; // Terminar el programa con error
    }

    double start_sort = omp_get_wtime(); // Iniciar el cronómetro para medir el tiempo de ordenamiento de números

    #pragma omp parallel // Iniciar la región paralela
    {
        #pragma omp single nowait // Crear una tarea única sin esperar a que termine
        par_qsort(numbersVector.data(), 0, numbersVector.size() - 1); // Llamar a la función de ordenamiento paralelo
    }

    double end_sort = omp_get_wtime(); // Detener el cronómetro para medir el tiempo de ordenamiento de números
    double time_sort = (end_sort - start_sort) * 1000; // Calcular el tiempo de ordenamiento de números en milisegundos
    cout << "Tiempo de ordenamiento de números: " << time_sort << " milisegundos." << endl; // Mostrar el tiempo de ordenamiento de números

    ofstream outFileSorted("nums_sorted_parallel.csv"); // Crear un archivo para almacenar los números ordenados
    for (size_t i = 0; i < numbersVector.size(); i++) {
        outFileSorted << numbersVector[i]; // Escribir el número en el archivo
        if (i < numbersVector.size() - 1) {
            outFileSorted << ","; // Si no es el último número, escribir una coma
        }
    }
    outFileSorted.close(); // Cerrar el archivo

    // cerrar array
    delete[] numbers; // Liberar la memoria del array de números

    return 0;
}