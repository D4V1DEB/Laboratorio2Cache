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

vector<double> winogradRecursivo(const vector<double>& A, const vector<double>& B, int k) {
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

    vector<double> S1 = sumar(A21, A22, mitad);
    vector<double> S2 = restar(S1, A11, mitad);
    vector<double> S3 = restar(A11, A21, mitad);
    vector<double> S4 = restar(A12, S2, mitad);

    vector<double> T1 = restar(B12, B11, mitad);
    vector<double> T2 = restar(B22, T1, mitad);
    vector<double> T3 = restar(B22, B12, mitad);
    vector<double> T4 = restar(T2, B21, mitad);

    vector<double> M1 = winogradRecursivo(A11, B11, mitad);
    vector<double> M2 = winogradRecursivo(A12, B21, mitad);
    vector<double> M3 = winogradRecursivo(S4, B22, mitad);
    vector<double> M4 = winogradRecursivo(A22, T4, mitad);
    vector<double> M5 = winogradRecursivo(S1, T1, mitad);
    vector<double> M6 = winogradRecursivo(S2, T2, mitad);
    vector<double> M7 = winogradRecursivo(S3, T3, mitad);

    vector<double> U1 = sumar(M1, M2, mitad);
    vector<double> U2 = sumar(M1, M6, mitad);
    vector<double> U3 = sumar(U2, M7, mitad);
    vector<double> U4 = sumar(U2, M5, mitad);
    vector<double> U5 = sumar(U4, M3, mitad);
    vector<double> U6 = restar(U3, M4, mitad);
    vector<double> U7 = sumar(U3, M5, mitad);

    vector<double> C(k * k);
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i * k + j] = U1[i * mitad + j];
            C[i * k + (j + mitad)] = U5[i * mitad + j];
            C[(i + mitad) * k + j] = U6[i * mitad + j];
            C[(i + mitad) * k + (j + mitad)] = U7[i * mitad + j];
        }
    }

    return C;
}

void multiplicarWinograd(const vector<double>& A, const vector<double>& B, vector<double>& C, int n) {
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

    vector<double> Cpadded = winogradRecursivo(Apadded, Bpadded, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = Cpadded[i * m + j];
        }
    }
}

int main() {
    ofstream archivo("tiempospart5.csv");
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
        multiplicarWinograd(A, B, C, n);
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double>(fin - inicio).count();

        archivo << n << ", " << tiempo << endl;
    }

    archivo.close();
    return 0;
}
