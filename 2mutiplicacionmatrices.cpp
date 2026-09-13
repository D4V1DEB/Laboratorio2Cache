#include<bits/stdc++.h>
using namespace std;

vector<int> sizes = {100, 250, 500, 1000, 2000, 3000, 4000, 5000};

void multiplicarMatrices(const vector<double>& A, const vector<double>& B, vector<double>& C, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                C[i*n + j] += A[i*n + k] * B[k*n + j];
            }
        }
    }
}

int main() {

    ofstream archivo("tiempospart2.csv");
    archivo << "N, Tiempo" << endl;

    for (int n: sizes) {
        vector<double> A(n * n);
        vector<double> B(n * n);
        vector<double> C(n * n, 0.0);

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                A[i*n + j] = rand() % 10;
                B[i*n + j] = rand() % 10;
            }
        }

        auto inicio = chrono::high_resolution_clock::now();
        multiplicarMatrices(A, B, C, n);
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double>(fin - inicio).count();

        archivo << n << ", " << tiempo << endl;
    }

    return 0;
}