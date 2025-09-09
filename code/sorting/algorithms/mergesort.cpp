#include <bits/stdc++.h>
#include <sys/resource.h>
#include <fstream>   // para std::ifstream
#include <unistd.h>
#include <sys/time.h>
using namespace std;
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define sz(x) (int)(x).size()
//la idea para la implementacion del codigo fue https://youtu.be/ACFZn_xQcz8?si=aHXHDB4RiD_8Z1XC
size_t getCurrentRSS() {
    long rss_pages = 0, dummy = 0;
    ifstream f("/proc/self/statm");
    f >> dummy >> rss_pages;
    size_t page = sysconf(_SC_PAGESIZE);
    return rss_pages * page; // bytes
}

void merge(vector<int>& arr, int l , int mid , int r,size_t& countmerge){
    vector<int> ans;
    int i = l, j = mid + 1;

    auto muestra = [&](){
        countmerge = max(countmerge, getCurrentRSS());
    };
    while(i <= mid && j <= r){
        if(arr[i] <= arr[j]){
            ans.pb(arr[i]);
            i++;
        }else{
            ans.pb(arr[j]);
            j++;
        }
        muestra();
    }
    while (i <= mid){
        ans.pb(arr[i]);
        i++;
        muestra();
    }
    while (j <= r){
        ans.pb(arr[j++]);
        muestra();
        
    }
    muestra();
    copy(all(ans), arr.begin() + l); 
}
void mergeSortAux(vector<int>&arr, int l, int r,size_t& countmerge){
    if (l >= r)  return; 
    int mid = l + (r - l)/ 2 ;
    //divide
    mergeSortAux(arr,l,mid,countmerge);
    mergeSortAux(arr,mid + 1 , r,countmerge);
    //unir los sub arreglos
    merge(arr, l , mid ,r,countmerge);
   
}
void mergeSort(vector<int>& arr,size_t& countmerge){

    mergeSortAux(arr, 0, sz(arr)-1,countmerge);
}