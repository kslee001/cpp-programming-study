// https://www.acmicpc.net/problem/1389 케빈베이컨 6단계법칙 FW
#include <iostream>
using namespace std;

int n,m;
int INF = 10000000;
int W[101][101];

void init(){
    cin >>n>>m;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            W[i][j] = INF;
        }
    }
    for(int i=0; i<m; ++i){
        int a,b; cin >>a>>b;
        W[a][b] = 1;
        W[b][a] = 1;
    }
}

void FW(){
    for(int k=1; k<=n; ++k){
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                if(W[i][k] + W[k][j] < W[i][j]) W[i][j] = W[i][k] + W[k][j];
            }
        }
    }
}

int check(){
    int res = INF;
    int idx = 0;
    for(int i=1; i<=n; ++i){
        int cur = 0;
        for(int j=1; j<=n; ++j){
            cur += W[i][j];
        }
        if(res > cur){
            res = cur;
            idx = i;
        }
    }
    return idx;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);    
    init();
    FW();
    cout << check();
}