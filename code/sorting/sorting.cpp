
#include <sys/resource.h>
#include <sys/time.h>

#include <bits/stdc++.h>
#include<sys/time.h>
#include<dirent.h>
#include <filesystem>
#include<sstream>
#include<fstream>
#include<chrono>

namespace fs = std::filesystem;

using namespace std;
using namespace fs;
using namespace std::chrono;
using Clock = std::chrono::steady_clock;
using us = std::chrono::microseconds;

typedef long long l;

size_t getMemoryUsage() {
    long rss_pages = 0, dummy = 0;
    std::ifstream f("/proc/self/statm");
    f >> dummy >> rss_pages;
    size_t page = sysconf(_SC_PAGESIZE);
    return rss_pages * page;  // bytes
}
void mergeSort(vector<int>& a,size_t& countmerge);
void insertionSort(vector<int>& arr,size_t& countmerge);
void quickSort(vector<int>& arr,size_t& countmerge);
void sortArrayAux(vector<int>& arr,size_t& countmerge);

void sa(vector<int>& s){
    sort(s.begin(),s.end());
}



l merge_Sort(vector<int>& m){
    size_t count;
    auto inicio = Clock::now();
    mergeSort(m,count);
    auto fin = Clock::now();
    return chrono::duration_cast<us>(fin - inicio).count();
}

l insertion_Sort(vector<int>& ins){
    auto inicio = Clock::now();
    size_t count;
    insertionSort(ins,count);
    auto fin = Clock::now();
    return chrono::duration_cast<us>(fin - inicio).count();
}

l quick_Sort(vector<int>& q){
    auto inicio = Clock::now();
    size_t count;
    quickSort(q,count);
    auto fin = Clock::now();
    return chrono::duration_cast<us>(fin - inicio).count();
}

l sortAux(vector<int>& s){
    auto inicio = Clock::now();
    sort(s.begin(), s.end());
    auto fin = Clock::now();
    return chrono::duration_cast<us>(fin - inicio).count();
}

l pandaSortAux(vector<int>& p){
    auto inicio = Clock::now();
    size_t count;
    sortArrayAux(p,count);
    auto fin = Clock::now();
    return chrono::duration_cast<us>(fin - inicio).count();
}
void printVector(vector<int> ans){
    for(int element: ans){
        cout<<element<<" ";
    }
}

void escribirArchivoOutput(ofstream& out,vector<int>m){
    for(int a: m){
        out<< a <<" ";
    }
    out<<endl;
}
l medirMemoriaSort(vector<int>& p, function<void(vector<int>&, size_t&)> f){
    size_t h = 0;
    f(p,h);
    
    return h;
}
void medirMemoria(int a , const path& name, string nombreArchivo){
    
        vector<int> m,ins,q,p,s;
        l  h,b,c,d,e;
        ifstream in(name);
        for(int i = 0;i < a ;i++){
            int b;
            if (!(in >> b)) break; 
            m.push_back(b);
            ins.push_back(b);
            q.push_back(b);
            p.push_back(b);
            s.push_back(b);
        }

        
        
        path dir2 = current_path()/"data"/"measurements"/nombreArchivo;
        ofstream out(dir2);
        cout<<nombreArchivo<<endl;
        out<<"InsertionSort ";
        h = medirMemoriaSort(ins,insertionSort);
        out<<h<<endl;
        out<<"MergeSort ";
        b = medirMemoriaSort(m,mergeSort);
        out<<b<<endl;
        out<<"Quicksort ";
        c = medirMemoriaSort(q,quickSort);
        out<<c<<endl;
        out<<"PandaSort ";
        out<<medirMemoriaSort(p,sortArrayAux);
        out<<d<<endl;
    

        
        
    

}
void ordenamiento(int a,const path& name,string nombreArchivo){
    vector<int> m,ins,q,p,s;
    l  h,b,c,d,e;
    ifstream in(name);
    for(int i = 0;i < a ;i++){
        int b;
        if (!(in >> b)) break; 
        m.push_back(b);
        ins.push_back(b);
        q.push_back(b);
        p.push_back(b);
        s.push_back(b);
    }
    path dir = current_path()/"data"/"array_output"/nombreArchivo;
    path dir2 = current_path()/"data"/"measurements"/nombreArchivo;

    ofstream out(dir,ios::app);
    ofstream ot(dir2, ios::app);
    if(a!= 10e7){
        out<<"InsertionSort ";
        h = insertion_Sort(ins);
        escribirArchivoOutput(out,ins);
        ot<<"InsertionSort ";
        ot<<h<<endl;
    }
    
        out<<"MergeSort ";
        b = merge_Sort(m);
        escribirArchivoOutput(out,m);
        out<<"QuickSort ";
        c = quick_Sort(q);
        escribirArchivoOutput(out,q);
        out<<"PandaSort ";
        d = pandaSortAux(p);
        escribirArchivoOutput(out,p);
        out<<"Sort ";
        e = sortAux(s);
        escribirArchivoOutput(out,s);

        ot<<"MergeSort ";
        ot<<b<<endl;

        ot<<"QuickSort ";
        ot<<c<<endl;

        ot<<"PandaSort ";
        ot<<d<<endl;

        ot<<"Sort ";
        ot<<e<<endl;
    
}

void listDir(){
    path dir = current_path()/"data"/"array_input";
    DIR *directorio; 
    struct dirent *elemento;
    string elem;
    if(directorio=opendir(dir.string().c_str())){
        while(elemento = readdir(directorio)){
            elem = elemento->d_name;
            string nombre = elemento->d_name;
            
            path pathInput = dir/elemento->d_name;
            replace(nombre.begin(), nombre.end(), '_', ' ');
            replace(nombre.begin(), nombre.end(), '.', ' ');
            stringstream ss(nombre);
            int n = 0;
            string t,d,m;
            ss>>n>>t>>d>>m;
            if(!n){
                continue;
            }
            string nombreSalida = to_string(n) + "_" + t  + "_" + d  +"_" + m +"_outm.txt";
            
            //ordenamiento(n,pathInput,nombreSalida);
            
            medirMemoria(n,pathInput,nombreSalida);
            
           
        }
    }
    closedir(directorio);
}







int main(){
    listDir();

    return 0; 
}