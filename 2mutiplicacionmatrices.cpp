#include<bits/stdc++.h>
using namespace std;

vector<int> sizes = {100, 200, 500, 750, 1000, 1500, 2000};

void multiplicarMatrices(double** A, double** B, double** C, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            C[i][j] = 0;
            for (int k=0; k<n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {

    ofstream archivo("tiempospart2.csv");
    archivo << "N, Tiempo" << endl;

    for (int n: sizes) {
        auto** A = new double*[n];
        auto** B = new double*[n];
        auto** C = new double*[n];

        for (int i=0; i<n; i++) {
            A[i] = new double[n];
            B[i] = new double[n];
            C[i] = new double[n];
        }

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
                C[i][j] = 0;
            }
        }

        auto inicio = chrono::high_resolution_clock::now();
        multiplicarMatrices(A, B, C, n);
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double>(fin - inicio).count();

        archivo << n << ", " << tiempo << endl;

        for (int i=0; i<n; i++) {
            delete[] A[i];
            delete[] B[i];
            delete[] C[i];
        }
        delete[] A;
        delete[] B;
        delete[] C;
    }

    return 0;
}