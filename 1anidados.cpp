#include<bits/stdc++.h>
using namespace std;
const int MAX = 100;


double A[MAX][MAX], x[MAX], y[MAX];

int main() {
    //inicializar A - x - y
    for (int i=0; i<MAX; i++) {
        for (int j=0; j<MAX; j++) {
            A[i][j] = rand() % 10;
        }
        x[i] = rand() % 10;
        y[i] = 0;
    }

    //1
    auto inicio1 = chrono::high_resolution_clock::now();
    for (int i=0; i<MAX; i++) {
        for (int j=0; j<MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    auto fin1 = chrono::high_resolution_clock::now();
    double tiempo1 = chrono::duration<double>(fin1 - inicio1).count();

    for (int i=0; i<MAX; i++) {
        y[i] = 0;
    }

    //2
    auto inicio2 = chrono::high_resolution_clock::now();
    for (int j=0; j<MAX; j++) {
        for (int i=0; i<MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
    auto fin2 = chrono::high_resolution_clock::now();
    double tiempo2 = chrono::duration<double>(fin2 - inicio2).count();

    return 0;
}