#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <sys/resource.h>
#include <sys/time.h>
#include <fstream>   // para std::ifstream
#include <unistd.h>
using namespace std;



size_t getCurrentRSS();

vector<int> sortArray(vector<int> arr,size_t& countmerge) {
    auto muestra = [&](){
        countmerge = max(countmerge, getCurrentRSS());
    };
    int n = arr.size();
    muestra();
    if (n <= 1) return arr;
    muestra();
    int block_size = std::sqrt(n);
    int block_count = (n + block_size - 1) / block_size;
    std::vector<std::queue<int>> block_queue(block_count);
    
    // Ordenar cada bloque usando selection sort
    for (int i = 0; i < block_count; i++) { //O(srqrt(n))
        int l = i * block_size;
        int r = std::min((i + 1) * block_size - 1, n - 1);
        
        // Selection sort en el bloque [l, r]
        for (int j = l; j <= r; j++) {//O(sqrt(n) * sqrt(n)))
            int min_idx = j;
            for (int k = j + 1; k <= r; k++) {//O(n * (sqrt(n))))
                if (arr[k] < arr[min_idx]) {
                    min_idx = k;
                }
            }
            if (min_idx != j) {
                std::swap(arr[j], arr[min_idx]);
                muestra();
            }
        }
        
        // Llenar la cola con elementos ordenados del bloque
        for (int j = l; j <= r; j++) {
            block_queue[i].push(arr[j]);
        } // O(sqrt(n) * sqrt(n) )= O(n)
        muestra();
    }
    
    // Merge de todos los bloques
    for (int i = 0; i < n; i++) { //O(n)
        int mn = INT_MAX, mni = -1;
        for (int j = 0; j < block_count; j++) {//O(n*sqrt(n))
            if (block_queue[j].empty()) continue;
            int cur = block_queue[j].front();
            muestra();
            if (cur < mn) {
                mni = j;
                mn = cur;
            }
        }
        arr[i] = mn;
        block_queue[mni].pop();
        muestra();
    }

    //final  O(n* sqrt(n))




    return arr;
}
void sortArrayAux(vector<int>& arr,size_t& countmerge){
    arr  = sortArray(arr,countmerge);
}