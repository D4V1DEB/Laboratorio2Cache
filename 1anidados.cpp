#include<bits/stdc++.h>
#include<fstream>
using namespace std;    

vector<int> size = {100, 200, 500, 1000, 1500, 2000, 2500, 3000, 5000};

int main() {
    ofstream archivo("tiempos.csv");
    archivo << "N, Tiempo1, Tiempo2" << endl;

    for (int n : size) {
        auto** A = new double*[n];
        for (int i = 0; i < n; i++) A[i] = new double[n];
        auto* x = new double[n];
        auto* y = new double[n];

        //inicializar A - x - y
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                A[i][j] = rand() % 10;
            }
            x[i] = rand() % 10;
            y[i] = 0;
        }

        //1
        auto inicio1 = chrono::high_resolution_clock::now();
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                y[i] += A[i][j] * x[j];
            }
        }
    
        auto fin1 = chrono::high_resolution_clock::now();
        double tiempo1 = chrono::duration<double>(fin1 - inicio1).count();

        for (int i=0; i<n; i++) {
            y[i] = 0;
        }

        //2
        auto inicio2 = chrono::high_resolution_clock::now();
        for (int j=0; j<n; j++) {
            for (int i=0; i<n; i++) {
                y[i] += A[i][j] * x[j];
            }
        }
        auto fin2 = chrono::high_resolution_clock::now();
        double tiempo2 = chrono::duration<double>(fin2 - inicio2).count();

        archivo << n << ", " << tiempo1 << ", " << tiempo2 << endl;

        for (int i = 0; i < n; i++) delete[] A[i];
        delete[] A;
        delete[] x;
        delete[] y;
    }
    archivo.close();
    return 0;
}