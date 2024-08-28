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

using namespace std; // Para no tener que anteponer std::

/**
 * Función para determinar si un número es primo
 * @param number Número a verificar si es primo
 */
bool isPrime(int number) {
    if (number == 0 || number == 1) {
        return false; // Si el número es 0 o 1, no es primo
    }
    int divisor; // Variable para almacenar el divisor
    for (divisor = number / 2; number % divisor != 0; --divisor) {
        ;
    }
    if (divisor != 1) {
        return false; // Si el número es divisible por otro número a parte de 1 y él mismo, no es primo
    } else {
        return true; // Si el número es divisible por 1 y él mismo, es primo
    }
}

void par_qsort(int *data, int lo, int hi) //}, int (*compare)(const int *, const int*))
{
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = data[(hi + lo)/2];

  while(l <= h){
    while((data[l] - p) < 0) l++;
    while((data[h] - p) > 0) h--;
    if(l<=h){
      //swap
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      l++; h--;
    }
  }
  //recursive call
  par_qsort(data, lo, h);
  par_qsort(data, l, hi);
}

/**
 * Función principal donde se corre el programa
 */
int main() {
    int N; // Cantidad de números aleatorios a generar
    cout << "Ingrese la cantidad de números aleatorios a generar: ";
    cin >> N; // Leer la cantidad de números aleatorios a generar

    // Medir el tiempo de generación de números aleatorios
    clock_t start_gen = clock();

    srand(time(0)); // Inicializar la semilla del generador de números aleatorios
    int *numbers = new int[N]; /// Arreglo para almacenar los números aleatorios
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 100; // Generar un número aleatorio entre 0 y 99
    }

    clock_t end_gen = clock(); // Medir el tiempo de finalización de la generación
    double time_gen = double(end_gen - start_gen) * 1000 / CLOCKS_PER_SEC; // Tiempo en milisegundos
    cout << "Tiempo de generación de números: " << time_gen << " milisegundos." << endl;

    // almacenar los números en un archivo
    ofstream outFile("nums.txt");
    for (int i = 0; i < N; i++) {
        outFile << numbers[i]; // Escribir el número en el archivo
        if (i < N - 1) {
            outFile << ","; // Separar los números por comas
        }
    }
    outFile.close(); // Cerrar el archivo

    // Liberar la memoria
    delete[] numbers;

    // Leer los números del archivo
    ifstream inFile("nums.txt");
    vector<int> numbersVector;
    // if para verificar si el archivo se abrió correctamente
    if (inFile.is_open()) {
        string line; // Variable para almacenar la línea leída
        while (getline(inFile, line, ',')) {
            int number; // Variable para almacenar el número
            stringstream(line) >> number; // Convertir la línea a número
            numbersVector.push_back(number); // Agregar el número al vector
        }
        inFile.close(); // Cerrar el archivo
    } else {
        cout << "ERROR: No se pudo abrir el archivo." << endl; // Mostrar un mensaje de error
        return 1; // Terminar el programa con error
    }

    // Medir el tiempo de ordenamiento de los números
    clock_t start_sort = clock();

    par_qsort(numbersVector.data(), 0, numbersVector.size() - 1);

    clock_t end_sort = clock(); // Medir el tiempo de finalización del ordenamiento
    double time_sort = double(end_sort - start_sort) * 1000 / CLOCKS_PER_SEC;
    cout << "Tiempo de ordenamiento de números: " << time_sort << " milisegundos." << endl;

    // Escribir los números ordenados en un segundo archivo
    ofstream outFileSorted("nums_orders.txt");
    for (size_t i = 0; i < numbersVector.size(); i++) {
        outFileSorted << numbersVector[i]; // Escribir el número en el archivo
        if (i < numbersVector.size() - 1) {
            outFileSorted << ","; // Separar los números por comas
        }
    }
    outFileSorted.close(); // Cerrar el archivo
    
    return 0;
}