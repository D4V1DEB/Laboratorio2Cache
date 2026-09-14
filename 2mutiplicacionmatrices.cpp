#include<bits/stdc++.h>
using namespace std;

vector<int> sizes = {100, 250, 500, 750, 1000, 1250, 1500, 1750, 2000, 2250, 2500};

void multiplicarMatrices(const vector<double>& A, const vector<double>& B, vector<double>& C, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                C[i*n + j] += A[i*n + k] * B[k*n + j];
            }
        }
    }
}

int main(int argc, char** argv) {
    int max_n = argc > 1 ? stoi(argv[1]) : sizes.back();

    ofstream archivo("tiempospart2.csv");
    archivo << "N, Tiempo" << endl;

    for (int n: sizes) {
        if (n > max_n) break;
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

        volatile double verificacion = C[0] + C[n * n - 1];
        (void)verificacion;

        archivo << n << ", " << tiempo << endl;
    }

    return 0;
}
