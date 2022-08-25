#include <iostream>
using namespace std;
using lint = long long;

lint arr[1000000];
lint sorted[1000000];
lint inv;
void merge(lint* arr, lint start, lint mid, lint end){
    lint i = start;
    lint j = mid+1;
    lint k = start;
    while(i <= mid && j <= end){
        // left < right -> inv x
        if(arr[i] < arr[j])
            sorted[k++] = arr[i++];
        // left > right -> inv 발생
        // {5,6,9,15}  {1,2,10,12} 인 경우 어떻게 될까?
        // (left의 개수 4) 1이 올라가면서 {5,1}, {6,1}, {7,1}, {8,1} 의 inversion 확인
        // (left의 개수 4) 2가 올라가면서 {5,2}, {6,2}, {7,2}, {8,2} 의 inversion 확인
        // 5,6,9가 올라갈 때는 inversion x
        // (left의 개수 1) 10이 올라가면서 {10,9} 발생
        // (left의 개수 1) 12가 올라가면서 {15,12} 발생
        // -> 남아있는 left의 개수 확인하면 됨
        else{                 // start = 0, end = 7인 경우 mid는 3 
                              // i는 0부터 3까지
                              // i=0일 때 남은 개수는 mid-i+1 = 4 
            inv += (mid-i+1); // mid - i + 1 : 남아있는 개수 
            sorted[k++] = arr[j++];
        }
    }
    while(i <= mid)
        sorted[k++] = arr[i++];
    while(j <= end)
        sorted[k++] = arr[j++];
    for(lint x=start; x<=end; ++x)
        arr[x] = sorted[x];
}

void msort(lint*arr, lint start, lint end){
    if(start >= end) return;
    lint mid = start + (end-start)/2;
    msort(arr, start, mid);
    msort(arr, mid+1, end);
    merge(arr, start, mid, end);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    lint n; cin >>n;
    for(lint i=0; i<n; ++i)
        cin >> arr[i];
    msort(arr, 0, n-1);
    cout <<inv;
}