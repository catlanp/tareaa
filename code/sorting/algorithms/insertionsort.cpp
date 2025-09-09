#include <algorithm>
#include <vector>
#include <fstream>   // para std::ifstream
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
using namespace std;
#define sz(x) (int)(x).size()

//La idea para la implementacion fue sacada de
//https://youtu.be/6GU6AGEWYJY?si=SW0MjKo3l-PqMVNY 
size_t getCurrentRSS();
void insertionSort(vector<int>& arr,size_t& countmerge){
    auto muestra = [&](){
        countmerge = max(countmerge, getCurrentRSS());
    };
    muestra();
    for(int i = 1; i < sz(arr); i ++){
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            muestra();
            j--;
        }
        arr[j + 1] = key;
        muestra();
    }
    muestra();
}