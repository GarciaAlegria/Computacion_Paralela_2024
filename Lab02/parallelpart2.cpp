/**
 * Universidad del Valle de Guatemala
 * Programación Paralela y Distribuida sección 10
 * Abner Ivan Garcia Alegria 21285
 * Oscar Esteban Donis Martinez 21610
 * Laboratorio 2
 */

#include <iostream> // Para usar cout
#include <fstream> // Para usar ifstream, ofstream
#include <cstdlib> // Para usar srand, rand
#include <ctime> // Para usar time, clock
#include <sstream> // Para usar stringstream
#include <vector> // Para usar vector
#include <algorithm> // Para usar sort
#include <random> // Para usar random
#include <chrono> // Para usar chrono
#include <omp.h> // Para usar OpenMP para paralelizar 

using namespace std; // Para no tener que anteponer std::

/**
 * Función para determinar si un número es primo
 * @param number Número a verificar si es primo
 */
bool isPrime(int number) {
    // Verificamos si el número es 0 o 1
    if (number == 0 || number == 1) {
        return false; // Si el número es 0 o 1, no es primo
    }
    int divisor; // Variable para almacenar el divisor

    for (divisor = number / 2; number % divisor != 0; --divisor) {
        ; // Buscamos el primero divisor o hasta que el número sea 1
    }
    if (divisor != 1) {
        return false; // Si el número es divisible por otro número a parte de 1 y él mismo, no es primo
    } else {
        return true; // Si el número es divisible por 1 y él mismo, es primo
    }
}

/**
 * Función para generar números aleatorios seguro para paralelización
 * @param N Cantidad de números a generar
 * @param min Valor mínimo para los números
 * @param max Valor máximo para los números
 */
std::vector<int> generate_random_numbers(int N, int min, int max) {
    std::vector<int> numbers(N);
    
    #pragma omp parallel
    {
        // Create a thread-local random number generator
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count() + omp_get_thread_num();
        std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(min, max);

        #pragma omp for
        for (int i = 0; i < N; i++) {
            numbers[i] = distribution(generator);
        }
    }
    
    return numbers;
}

/**
 * Función para comparar dos números
 * @param a Primer número
 * @param b Segundo número
 */
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Función para ordenar de forma paralela un arreglo utilizando QuickSort
 * @param data Arreglo a ordenar
 * @param lo Índice inferior
 * @param hi Índice superior
 * @param compare Función para comparar dos números
 */
void par_qsort(int* data, int lo, int hi, int (*compare)(const void*, const void*)) {
    if (lo >= hi) return;

    int l = lo;
    int h = hi;
    int p = data[(hi + lo) / 2];

    while (l <= h) {
        while (compare(&data[l], &p) < 0) l++;
        while (compare(&data[h], &p) > 0) h--;
        if (l <= h) {
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++; h--;
        }
    }

    #pragma omp task if (h - lo > 1000)
    par_qsort(data, lo, h, compare);

    #pragma omp task if (hi - l > 1000)
    par_qsort(data, l, hi, compare);

    #pragma omp taskwait
}

/**
 * Función principal donde se corre el programa
 */
int main() {
    int N; // Cantidad de números aleatorios a generar
    cout << "Ingrese la cantidad de números aleatorios a generar: ";
    cin >> N; // Leer la cantidad de números aleatorios a generar

    srand(time(0)); // Inicializar la semilla del generador de números aleatorios
    int *numbers = new int[N]; // Arreglo para almacenar los números aleatorios

    double start_gen = omp_get_wtime(); // Medir el tiempo de generación de números aleatorios

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count() + omp_get_thread_num();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);

    std::vector<int> numbers = generate_random_numbers(N, 0, 99);

    double end_gen = omp_get_wtime(); // Medir el tiempo de finalización de la generación
    double time_gen = double(end_gen - start_gen) * 1000 / CLOCKS_PER_SEC; // Tiempo en milisegundos 
    cout << "Tiempo de generación de números (paralelizado): " << time_gen << " ms." << endl;

    ofstream outFile("numsparallel.txt"); // Crear un archivo para almacenar los números generados
    for (int i = 0; i < N; i++) {
        outFile << numbers[i]; // Escribir el número en el archivo
        if (i < N - 1) {
            outFile << ",";
        }
    }
    outFile.close(); // Cerrar el archivo

    delete[] numbers; // Liberar la memoria

    ifstream inFile("numsparallel.txt"); // Leer los números del archivo
    vector<int> numbersVector; // Vector para almacenar los números

    if (inFile.is_open()) {
        string line; // Variable para almacenar la línea leída del archivo
        while (getline(inFile, line, ',')) {
            int number; // Variable para almacenar el número
            stringstream(line) >> number; // Convertir la línea a número
            numbersVector.push_back(number); // Agregar el número al vector
        }
        inFile.close(); // Cerrar el archivo
    } else {
        cout << "No se pudo abrir el archivo." << endl; // Mostrar un mensaje de error
        return 1; // Terminar el programa con error
    }

    // Medir el tiempo de ordenamiento de los números
    double start_sort = omp_get_wtime(); // Inicializar el tiempo de inicio del ordenamiento

    #pragma omp parallel
    {
        #pragma omp single
        par_qsort(numbersVector.data(), 0, numbersVector.size() - 1, compare);
    }

    double end_sort = omp_get_wtime(); // Medir el tiempo de finalización del ordenamiento
    double time_sort = double(end_sort - start_sort) * 1000/ CLOCKS_PER_SEC ; // Tiempo en milisegundos
    cout << "Tiempo de ordenamiento de números (paralelizado): " << time_sort << " ms." << endl;

    ofstream outFileSorted("numsparallel_orders.txt"); // Crear un archivo para almacenar los números ordenados
    for (size_t i = 0; i < numbersVector.size(); i++) {
        outFileSorted << numbersVector[i]; // Escribir el número en el archivo
        if (i < numbersVector.size() - 1) {
            outFileSorted << ","; // Agregar una coma si no es el último número
        }
    }
    outFileSorted.close(); // Cerrar el archivo

    return 0; // Terminar el programa con éxito
}