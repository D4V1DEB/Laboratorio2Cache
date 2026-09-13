#include <bits/stdc++.h>
using namespace std;

vector<int> sizes = {100, 250, 500, 1000, 2000, 3000, 4000, 5000};
const int UMBRAL = 64;

void multiplicarClasica(const vector<double>& A, const vector<double>& B, vector<double>& C, int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            double suma = 0.0;
            for (int p = 0; p < k; p++) {
                suma += A[i * k + p] * B[p * k + j];
            }
            C[i * k + j] += suma;
        }
    }
}

vector<double> sumar(const vector<double>& A, const vector<double>& B, int k) {
    vector<double> C(k * k);
    for (int i = 0; i < k * k; i++) {
        C[i] = A[i] + B[i];
    }
    return C;
}

vector<double> restar(const vector<double>& A, const vector<double>& B, int k) {
    vector<double> C(k * k);
    for (int i = 0; i < k * k; i++) {
        C[i] = A[i] - B[i];
    }
    return C;
}

vector<double> strassenRecursivo(const vector<double>& A, const vector<double>& B, int k) {
    if (k <= UMBRAL) {
        vector<double> C(k * k, 0.0);
        multiplicarClasica(A, B, C, k);
        return C;
    }

    int mitad = k / 2;
    int tamSub = mitad * mitad;

    vector<double> A11(tamSub), A12(tamSub), A21(tamSub), A22(tamSub);
    vector<double> B11(tamSub), B12(tamSub), B21(tamSub), B22(tamSub);

    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            A11[i * mitad + j] = A[i * k + j];
            A12[i * mitad + j] = A[i * k + (j + mitad)];
            A21[i * mitad + j] = A[(i + mitad) * k + j];
            A22[i * mitad + j] = A[(i + mitad) * k + (j + mitad)];

            B11[i * mitad + j] = B[i * k + j];
            B12[i * mitad + j] = B[i * k + (j + mitad)];
            B21[i * mitad + j] = B[(i + mitad) * k + j];
            B22[i * mitad + j] = B[(i + mitad) * k + (j + mitad)];
        }
    }

    vector<double> M1 = strassenRecursivo(sumar(A11, A22, mitad), sumar(B11, B22, mitad), mitad);
    vector<double> M2 = strassenRecursivo(sumar(A21, A22, mitad), B11, mitad);
    vector<double> M3 = strassenRecursivo(A11, restar(B12, B22, mitad), mitad);
    vector<double> M4 = strassenRecursivo(A22, restar(B21, B11, mitad), mitad);
    vector<double> M5 = strassenRecursivo(sumar(A11, A12, mitad), B22, mitad);
    vector<double> M6 = strassenRecursivo(restar(A21, A11, mitad), sumar(B11, B22, mitad), mitad);
    vector<double> M7 = strassenRecursivo(restar(A12, A22, mitad), sumar(B21, B22, mitad), mitad);

    vector<double> C11 = sumar(restar(sumar(M1, M4, mitad), M5, mitad), M7, mitad);
    vector<double> C12 = sumar(M3, M5, mitad);
    vector<double> C21 = sumar(M2, M4, mitad);
    vector<double> C22 = sumar(sumar(restar(M1, M2, mitad), M3, mitad), M6, mitad);

    vector<double> C(k * k);
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i * k + j] = C11[i * mitad + j];
            C[i * k + (j + mitad)] = C12[i * mitad + j];
            C[(i + mitad) * k + j] = C21[i * mitad + j];
            C[(i + mitad) * k + (j + mitad)] = C22[i * mitad + j];
        }
    }

    return C;
}

void multiplicarStrassen(const vector<double>& A, const vector<double>& B, vector<double>& C, int n) {
    int m = 1;
    while (m < n) m *= 2;

    vector<double> Apadded(m * m, 0.0);
    vector<double> Bpadded(m * m, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Apadded[i * m + j] = A[i * n + j];
            Bpadded[i * m + j] = B[i * n + j];
        }
    }

    vector<double> Cpadded = strassenRecursivo(Apadded, Bpadded, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = Cpadded[i * m + j];
        }
    }
}

int main() {
    ofstream archivo("tiempospart4.csv");
    archivo << "N, Tiempo" << endl;

    for (int n : sizes) {
        vector<double> A(n * n);
        vector<double> B(n * n);
        vector<double> C(n * n, 0.0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i * n + j] = rand() % 10;
                B[i * n + j] = rand() % 10;
            }
        }

        auto inicio = chrono::high_resolution_clock::now();
        multiplicarStrassen(A, B, C, n);
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double>(fin - inicio).count();

        archivo << n << ", " << tiempo << endl;
    }

    archivo.close();
    return 0;
}
