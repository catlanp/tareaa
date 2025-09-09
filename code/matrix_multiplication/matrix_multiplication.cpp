#include <bits/stdc++.h>
#include<sys/time.h>
#include<dirent.h>
#include <filesystem>
#include<sstream>
#include<fstream>

namespace fs = std::filesystem;

using namespace std;
using namespace fs;



long long obtenerTiempo(){
    struct timeval inicio;
    gettimeofday(&inicio,NULL);
    return inicio.tv_sec*1000000 + inicio.tv_usec;
}


vector<vector<int>> naive(const vector<vector<int>>& A, const vector<vector<int>>& B);
vector<vector<int>> multiply(vector<vector<int>> &mat1, vector<vector<int>> &mat2);
void replace_last_char(string& s, char c) {
    if (!s.empty()) s.back() = c;
}
void multiplicarMatrices(vector<vector<int>> mat1, vector<vector<int>> mat2,path matrix1, path matrix2, path salida,path mediciones){
    int n = mat1.size();
    ifstream in(matrix1);
    for(int i  =0; i < n; i++){
        for(int j = 0; j < n; j++){
            int b;
            if (!(in >> b)) break; 
            mat1[i][j] = b;
            
        }
   
    }
    in.close();
    ifstream in2(matrix2);
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n ;j++){
            int b;
            if (!(in2 >> b)) break; 
            mat2[i][j] = b;
        }
    }
    in2.close();
    long long inicioNaive = obtenerTiempo();
    vector<vector<int>> naiveM = naive(mat1,mat2);
    long long finalNaive = obtenerTiempo();

    long long inicioStrassen = obtenerTiempo();
    vector<vector<int>> strassenM = multiply(mat1,mat2);
    long long finalStrassen = obtenerTiempo();
    ofstream out(salida,ios::app);
    ofstream out2(mediciones,ios::app);
    out<<"Strassen:"<<endl;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j< n ; j++){
            out<<strassenM[i][j]<<" ";
        }
        out<<endl;
    }
    out<<endl;
    out<<"Naive:"<<endl;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j< n ; j++){
            out<<naiveM[i][j]<<" ";
        }
        out<<endl;
    }
    out2<<"Strassen:"<<finalStrassen - inicioStrassen<<endl;
    out2<<"Naive:"<<finalNaive - inicioNaive<<endl;
  

}
void listDir(){
    path dir = current_path()/"data"/"matrix_input";
    DIR *directorio; 
    struct dirent *elemento;
    string elem;
    if(directorio=opendir(dir.string().c_str())){
        while(elemento = readdir(directorio)){
            elem = elemento->d_name;
            string nombre = elemento->d_name;
            path matrix1 = dir/elemento->d_name;
            replace(nombre.begin(), nombre.end(), '_', ' ');
            replace(nombre.begin(), nombre.end(), '.', ' ');
            stringstream ss(nombre);
            int n = 0, f;
            string t,d,m;
            ss>>n>>t>>d>>m>>f;
            if(!n || f == 2){
                continue;
            }
            string nombre2 = to_string(n) + "_" + t + "_" + d +"_" + m + "_"+ "2.txt";
            string nombreout = to_string(n) + "_" + t + "_" + d +"_" + m + "_"+ "out.txt";
            cout<<nombre2<<endl;
            path matrix2 = dir/nombre2;
            path salida = current_path()/"data"/"matrix_output"/nombreout;
            path salidaTiempo = current_path()/"data"/"measurements"/nombreout;
            vector<vector<int>> mat1(n, vector<int>(n, 0)) ,mat2(n,vector<int>(n,0));
          
            multiplicarMatrices(mat1 , mat2,matrix1,matrix2,salida,salidaTiempo);
         
            
            
        }
    }
    closedir(directorio);
}






int main(){
    listDir();
}