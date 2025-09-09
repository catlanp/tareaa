#include <bits/stdc++.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <fstream>   // para std::ifstream
#include <unistd.h>
using namespace std;
//el quicksort implementado esta basado en el video https://youtu.be/pM-6r5xsNEY?si=v2ciyhAFq5VV1zD6
//este es la version Middle Element
#define sz(x) (int)(x).size()
size_t getCurrentRSS();
int partition(vector<int>& arr, int l, int r , int pivot,size_t& countmerge){
    auto muestra = [&](){
        countmerge = max(countmerge, getCurrentRSS());
    };
    muestra();
    while( l <= r ){
        //ver mover todos los elementos de un lado del pivot si son mayor o menor
        while (arr[l] < pivot) l++;
        while (arr[r] > pivot) r--;
        if (l <= r){
            swap(arr[l], arr[r]);
            muestra();
            l++;
            r--;
        }

    }
    muestra();
    return l;
}

void quickSortAux(vector<int>& arr,int s, int e,size_t& countmerge){
    if( s >= e) return;
    int mid = (s+e)/2;
    int pivot = arr[mid];//obtener el pivote
    int index = partition(arr,s,e,pivot,countmerge);
    //dividir
    quickSortAux(arr, s , index - 1,countmerge);
    quickSortAux(arr , index, e,countmerge);
}

void quickSort(vector<int>& arr,size_t&countmerge){
    quickSortAux(arr, 0, sz(arr)-1,countmerge);
}
