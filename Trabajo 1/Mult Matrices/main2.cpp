#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;
const int N = 200;

void multMatrizClasica(int **m1, int **m2, int **res, int N ){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}
void multMatrizBloque(int **m1, int **m2, int **res, int N, int S){
    for (int ii = 0; ii < N; ii += S) {
        for (int jj = 0; jj < N; jj += S) {
            for (int kk = 0; kk < N; kk += S) {
                for (int i = ii; i < std::min(ii + S, N); ++i) {
                    for (int j = jj; j < std::min(jj + S, N); ++j) {
                        for (int k = kk; k < std::min(kk + S, N); ++k) {
                            res[i][j] += m1[i][k] * m2[k][j];
                        }
                    }
                }
            }
        }
    }
}
int main() {
    int **A = new int*[N];
    int **B = new int*[N];
    int **res = new int*[N];
    for (int i = 0; i < N; ++i) {
        A[i] = new int[N];
        B[i] = new int[N];
        res[i] = new int[N];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1; 
            B[i][j] = 1; 
            res[i][j] = 0;
        }
    }
    
    auto start1 = chrono::high_resolution_clock::now();
    multMatrizClasica(A, B, res, N);
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration1 = end1 - start1;
    for (int i = 0; i < N; ++i) {
        fill(res[i], res[i] + N, 0);
    }
    int S = 20;  
    auto start2 = chrono::high_resolution_clock::now();
    multMatrizBloque(A, B, res, N, S);
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration2 = end2 - start2;
    cout << "Tiempo de multiplicación clásica: " << duration1.count() << " segundos" << endl;
    cout << "Tiempo de multiplicación por bloques: " << duration2.count() << " segundos" << endl;

    for (int i = 0; i < N; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] res[i];
    }
    delete[] A;
    delete[] B;
    delete[] res;

    return 0;
}
