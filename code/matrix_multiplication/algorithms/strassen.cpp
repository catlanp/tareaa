#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//Este algoritmo fue sacado de https://www.geeksforgeeks.org/dsa/strassens-matrix-multiplication/
// Realiza la suma o resta de matrices de tamaño size×size
// sign = 1 para suma, -1 para resta
vector<vector<int>> add(vector<vector<int>> a, vector<vector<int>> b, int size, int sign = 1) {
    vector<vector<int>> res(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            res[i][j] = a[i][j] + sign * b[i][j];
    return res;
}

// Implementación recursiva de la multiplicación de matrices con Strassen
// Supone que ambas matrices son de tamaño size×size 
// y que size es potencia de 2
vector<vector<int>> strassen(vector<vector<int>> mat1, 
                                    vector<vector<int>> mat2) {
    int n = mat1.size();
    
    // Caso base: multiplicación de matrices 1×1
    vector<vector<int>> res(n, vector<int>(n, 0));
    if (n == 1) {
        res[0][0] = mat1[0][0] * mat2[0][0];
        return res;
    }

    // Dividir las matrices en 4 submatrices
    int newSize = n / 2;
    vector<vector<int>> a11(newSize, vector<int>(newSize));
    vector<vector<int>> a12(newSize, vector<int>(newSize));
    vector<vector<int>> a21(newSize, vector<int>(newSize));
    vector<vector<int>> a22(newSize, vector<int>(newSize));
    vector<vector<int>> b11(newSize, vector<int>(newSize));
    vector<vector<int>> b12(newSize, vector<int>(newSize));
    vector<vector<int>> b21(newSize, vector<int>(newSize));
    vector<vector<int>> b22(newSize, vector<int>(newSize));

    // Llenar las submatrices
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = mat1[i][j];
            a12[i][j] = mat1[i][j + newSize];
            a21[i][j] = mat1[i + newSize][j];
            a22[i][j] = mat1[i + newSize][j + newSize];
            b11[i][j] = mat2[i][j];
            b12[i][j] = mat2[i][j + newSize];
            b21[i][j] = mat2[i + newSize][j];
            b22[i][j] = mat2[i + newSize][j + newSize];
        }

    // Calcular los 7 productos usando las fórmulas de Strassen
    auto m1 = strassen(add(a11, a22, newSize), add(b11, b22, newSize));
    auto m2 = strassen(add(a21, a22, newSize), b11);
    auto m3 = strassen(a11, add(b12, b22, newSize, -1));
    auto m4 = strassen(a22, add(b21, b11, newSize, -1));
    auto m5 = strassen(add(a11, a12, newSize), b22);
    auto m6 = strassen(add(a21, a11, newSize, -1), add(b11, b12, newSize));
    auto m7 = strassen(add(a12, a22, newSize, -1), add(b21, b22, newSize));

    // Calcular los cuadrantes del resultado a partir de m1...m7
    auto c11 = add(add(m1, m4, newSize), add(m7, m5, newSize, -1), newSize);
    auto c12 = add(m3, m5, newSize);
    auto c21 = add(m2, m4, newSize);
    auto c22 = add(add(m1, m3, newSize), add(m6, m2, newSize, -1), newSize);

    // Combinar los cuadrantes en la matriz final
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            res[i][j] = c11[i][j];
            res[i][j + newSize] = c12[i][j];
            res[i + newSize][j] = c21[i][j];
            res[i + newSize][j + newSize] = c22[i][j];
        }

    return res;
}

// Multiplica mat1 (n×m) y mat2 (m×q) usando el método de Strassen
vector<vector<int>> multiply(vector<vector<int>> &mat1, 
                vector<vector<int>> &mat2) {
    
    vector<vector<int>> cPad = strassen(mat1, mat2);
    int n = mat1.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <n; j++)
            C[i][j] = cPad[i][j];

    return C ;
}
