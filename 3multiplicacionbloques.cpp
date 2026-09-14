#include <bits/stdc++.h>
using namespace std;

vector<int> sizes = {100, 250, 500, 750, 1000, 1250, 1500, 1750, 2000, 2250, 2500};
vector<int> blocks = {8, 16, 32, 64, 128};

void multiplicarMatricesBloques(const vector<double>& A, const vector<double>& B, vector<double>& C, int n, int blockSize) {
    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            for (int kk = 0; kk < n; kk += blockSize) {
                int i_max = min(ii + blockSize, n);
                int j_max = min(jj + blockSize, n);
                int k_max = min(kk + blockSize, n);
                for (int i = ii; i < i_max; i++) {
                    for (int j = jj; j < j_max; j++) {
                        for (int k = kk; k < k_max; k++) {
                            C[i*n + j] += A[i*n + k] * B[k*n + j];
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    int max_n = argc > 1 ? stoi(argv[1]) : sizes.back();
    int min_block = argc > 2 ? stoi(argv[2]) : 0;
    int max_block = argc > 2 ? min_block : blocks.back();

    ofstream archivo("tiempospart3.csv");
    archivo << "N,Bloque,Tiempo\n";

    for (int n : sizes) {
        if (n > max_n) break;
        vector<double> A(n * n);
        vector<double> B(n * n);
        vector<double> C(n * n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i*n + j] = rand() % 10;
                B[i*n + j] = rand() % 10;
            }
        }

        for (int blockSize : blocks) {
            if (blockSize < min_block || blockSize > max_block) continue;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    C[i*n + j] = 0.0;
                }
            }
            auto inicio = chrono::high_resolution_clock::now();
            multiplicarMatricesBloques(A, B, C, n, blockSize);
            auto fin = chrono::high_resolution_clock::now();
            double tiempo = chrono::duration<double>(fin - inicio).count();

            volatile double verificacion = C[0] + C[n * n - 1];
            (void)verificacion;

            archivo << n << "," << blockSize << "," << tiempo << "\n";
        }
    }

    archivo.close();

    return 0;
}
