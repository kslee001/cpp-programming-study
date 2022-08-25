// https://www.acmicpc.net/problem/11403 경로찾기
#include <iostream>
using namespace std;
int n;

int W[100][100];
int D[100][100];

void init(){
    cin >>n;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin >>W[i][j];
            if(W[i][j] == 0) W[i][j] = 100000;
        }
    }
}

void FW(){
    for(int k=0; k<n; ++k)
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j)
                if(W[i][k] + W[k][j] < W[i][j]) W[i][j] = W[i][k] + W[k][j];
}

void check(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            if(W[i][j]>=100000) cout <<"0 ";
            else                cout <<"1 ";
        cout <<"\n";
    }
}

int main(){
    init();
    FW();
    check();
}