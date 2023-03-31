// https://www.acmicpc.net/problem/11404 플로이드
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
using lint = long long;

int n,m;
lint dist[100][100];
lint parent[100][100];

int main(){
    cin >>n>>m;
    // initialize
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            dist[i][j] = 10000001;
        }
    }
    for(int i=0; i<m; ++i){
        lint a, b, c; cin >>a>>b>>c;
        --a; --b;
        if(dist[a][b] > c)
            dist[a][b]   = c;
    }
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(i==j) 
                dist[i][j] = 0;
            else{
                if(dist[i][j]==0) dist[i][j] = 10000001;
            }
        }
    }
    // compare distances
    for(int k=0; k<n; ++k){
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    // cout <<" i : " << i << ", j : " << j << 
                    // " \ndist[i][j]: " << dist[i][j] << " | dist [i][k] : "<<dist[i][k] << " | dist[k][j] :"<<dist[k][j] <<"\n";
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
    // print result
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(dist[i][j] >= 10000001)
                cout << "0";
            else
                cout << dist[i][j];
            if(j!= n-1) cout <<" ";    
        }
        if(i != n-1) cout <<"\n";
    }
}