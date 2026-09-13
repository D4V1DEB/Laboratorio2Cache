#include<bits/stdc++.h>
using namespace std;    

vector<int> sizes = {100, 200, 500, 1000, 1500, 2000, 2500, 3000, 5000};

int main() {
    ofstream archivo("tiempospart1.csv");
    archivo << "N, Tiempo1, Tiempo2" << endl;

    for (int n : sizes) {
        vector<double> A(n * n);
        vector<double> x(n);
        vector<double> y(n, 0.0);

        //inicializar A - x - y
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                A[i*n + j] = rand() % 10;
            }
            x[i] = rand() % 10;
        }

        //1
        auto inicio1 = chrono::high_resolution_clock::now();
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                y[i] += A[i*n + j] * x[j];
            }
        }
    
        auto fin1 = chrono::high_resolution_clock::now();
        double tiempo1 = chrono::duration<double>(fin1 - inicio1).count();

        for (int i=0; i<n; i++) {
            y[i] = 0.0;
        }

        //2
        auto inicio2 = chrono::high_resolution_clock::now();
        for (int j=0; j<n; j++) {
            for (int i=0; i<n; i++) {
                y[i] += A[i*n + j] * x[j];
            }
        }
        auto fin2 = chrono::high_resolution_clock::now();
        double tiempo2 = chrono::duration<double>(fin2 - inicio2).count();

        archivo << n << ", " << tiempo1 << ", " << tiempo2 << endl;
    }
    archivo.close();
    return 0;
}