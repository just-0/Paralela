//Implementar y comparar los 2-bucles anidados FOR presentados en el cap. 2 del libro, pag 22.
#include <iostream>
#include <chrono>


using namespace std;
const int MAX = 10000;  
double A[MAX][MAX], x[MAX], y[MAX];

void test1() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A[i][j] * x[j];
}

void test2() {
    for (int j = 0; j < MAX; j++)
        for (int i = 0; i < MAX; i++)
            y[i] += A[i][j] * x[j];
}

int main() {
   
    for (int i = 0; i < MAX; i++) {
        x[i] = 1.0;
        for (int j = 0; j < MAX; j++) {
            A[i][j] = 1.0;
        }
    }

   
    auto start1 = chrono::high_resolution_clock::now();
    test1();
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration1 = end1 - start1;
    auto start2 = chrono::high_resolution_clock::now();
    test2();
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration2 = end2 - start2;

    cout << "primero " << duration1.count() << endl;
    cout << "segundo: " << duration2.count() << endl;

    return 0;
}