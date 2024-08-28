#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

void test1(double** A, double* x, double* y, int MAX) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A[i][j] * x[j];
}
void test2(double** A, double* x, double* y, int MAX) {
    for (int j = 0; j < MAX; j++)
        for (int i = 0; i < MAX; i++)
            y[i] += A[i][j] * x[j];
}
int main() {
    int sizes[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
    cout << "Tiempo que demoran en segundos" << endl;
    cout << "Tamaño matriz\tPrimera Forma\t\tSegundaForma" << endl;
    for (int s = 0; s < 9; s++) {
        int MAX = sizes[s];        
        double** A = new double*[MAX];
        for (int i = 0; i < MAX; i++) {
            A[i] = new double[MAX];
        }
        double* x = new double[MAX];
        double* y = new double[MAX];

        
        for (int i = 0; i < MAX; i++) {
            x[i] = 1.0;
            y[i] = 0.0;
            for (int j = 0; j < MAX; j++) {
                A[i][j] = 1.0;
            }
        }
        auto start1 = chrono::high_resolution_clock::now();
        test1(A, x, y, MAX);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration1 = end1 - start1;

        fill_n(y, MAX, 0.0);
        auto start2 = chrono::high_resolution_clock::now();
        test2(A, x, y, MAX);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration2 = end2 - start2;
        
        cout << sizes[s]<<"\t\t" << duration1.count() << "\t\t" << duration2.count()<< endl;
        

        
        delete[] x;
        delete[] y;
        for (int i = 0; i < MAX; i++) {
            delete[] A[i];
        }
        delete[] A;
    }

    return 0;
}
