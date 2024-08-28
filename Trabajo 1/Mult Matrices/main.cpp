#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

void multMatrizClasica(int **m1, int **m2, int **res, int N ){
   
    for(int i = 0; i < N;i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                *(*(res+i)+j) += *(*(m1+i)+k) * *(*(m2+k)+j);
            }
        }
    }
    return;
}


void multMatrizBloque(int **m1, int **m2, int **res, int N , int S){
    for (int ii = 0; ii < N; ii += S) {
        for (int jj = 0;jj < N; jj += S) {
            for (int kk = 0; kk < N; kk += S) {
                for (int i = ii;i < std::min(ii+S,N); ++i) {
                    for (int j = jj;j < std::min(jj+S, N); ++j) {
                        for (int k = kk; k < std::min(kk +S, N);++k) {
                            res[i][j] += m1[i][k]*m2[k][j];
                        }
                    }
                }
            }
        }
    }
}
int main() {
    int sizes[] = {10, 20, 40, 80, 160,320,640,1280,2560};
    cout << "Tiempo que demoran en segundos" << endl;
    cout << "Tamaño matriz\tMultClasica\t\tMultBloque" << endl;
    for (int size : sizes) {
        

        
        int **A = new int*[size];
        int **B = new int*[size];
        int **res = new int*[size];
        for (int i = 0; i < size; ++i) {
            A[i] = new int[size];
            B[i] = new int[size];
            res[i] = new int[size];
        }

        
        int value = 1;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                A[i][j] = value++;
                B[i][j] = value++;
            }
        }

        
        auto start1 = chrono::high_resolution_clock::now();
        multMatrizClasica(A, B, res, size);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration1 = end1 - start1;

        

        
        int S = 80;
        auto start2 = chrono::high_resolution_clock::now();
        multMatrizBloque(A, B, res, size, S);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration2 = end2 - start2;

        
         cout << size<<"\t\t" << duration1.count() << "\t\t" << duration2.count()<< endl;
        
        for (int i = 0; i < size; ++i) {
            delete[] A[i];
            delete[] B[i];
            delete[] res[i];
        }
        delete[] A;
        delete[] B;
        delete[] res;
    }

    return 0;
}