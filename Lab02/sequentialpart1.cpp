#include <iostream> // Para usar cout
#include <fstream> // Para usar ifstream, ofstream
#include <cstdlib> // Para usar srand, rand
#include <ctime> // Para usar time
#include <sstream> // Para usar stringstream
#include <vector> // Para usar vector
#include <algorithm> // Para usar sort

using namespace std; // Para no tener que anteponer std::

// Función para determinar si un número es primo
bool isPrime(int number) {
    if (number == 0 || number == 1) {
        return false;
    }
    int divisor; // Variable para almacenar el divisor
    for (divisor = number / 2; number % divisor != 0; --divisor) {
        ;
    }
    if (divisor != 1) {
        return false;
    } else {
        return true;
    }
}

int main() {
    int N; // Cantidad de números aleatorios a generar
    cout << "Ingrese la cantidad de números aleatorios a generar: ";
    cin >> N; // Leer la cantidad de números aleatorios a generar

    // Generar números aleatorios
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios
    int *numbers = new int[N]; /// Arreglo para almacenar los números aleatorios
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 100; // Generar un número aleatorio entre 0 y 99
    }

    // almacenar los números en un archivo
    ofstream outFile("nums.txt");
    for (int i = 0; i < N; i++) {
        outFile << numbers[i]; // Escribir el número en el archivo
        if (i < N - 1) {
            outFile << ",";
        }
    }
    outFile.close();

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
            stringstream(line) >> number;
            numbersVector.push_back(number);
        }
        inFile.close();
    } else {
        cout << "ERROR: No se pudo abrir el archivo." << endl;
        return 1;
    }

    // ordenar los números de forma ascendente
    sort(numbersVector.begin(), numbersVector.end());

    // Escribir los números ordenados en un segundo archivo
    ofstream outFileSorted("nums_orders.txt");
    for (size_t i = 0; i < numbersVector.size(); i++) {
        outFileSorted << numbersVector[i]; // Escribir el número en el archivo
        if (i < numbersVector.size() - 1) {
            outFileSorted << ",";
        }
    }
    outFileSorted.close();

    return 0;
}