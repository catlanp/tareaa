#include <iostream>
#include <vector>
using namespace std;
//Rescatado de chatgpt
vector<vector<int>> naive(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();     
    int m = A[0].size();    
    int p = B[0].size();      
     //creacion del vector resultado
    vector<vector<int>> C(n, vector<int>(p, 0));
   
    for (int i = 0; i < n; i++) {        
        for (int j = 0; j < p; j++) {     
            for (int k = 0; k < m; k++) {
                //operacion de la multiplicacion del indice i j
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}