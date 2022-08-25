// https://www.acmicpc.net/problem/16398 행성연결 MST
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int cost[1000][1000];
int parent[1000];
int get_group(int a){
    if(parent[a]==a) return a;
    else return parent[a] = get_group(parent[a]);
}
void union_group(int a, int b){
    parent[get_group(a)] = get_group(b);
}

struct edge{
    int s;
    int e;
    int c;
    edge(){};
    edge(int a, int b, int d){s=a;e=b;c=d;}
    bool operator<(const edge e){return c<e.c;}
};

vector<edge> edges;

int main(){
    cin >>n;
    long long res = 0;
    for(int i=0; i<n; ++i)
        parent[i] = i;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin >> cost[i][j];
        }
    }
    for(int i=0; i<n-1; ++i){
        for(int j=i+1; j<n; ++j){
            edges.push_back(edge(i,j, cost[i][j])); 
        }
    }
    sort(edges.begin(), edges.end());
    for(int i=0; i<edges.size(); ++i){
        int s_group = get_group(edges[i].s);
        int e_group = get_group(edges[i].e);
        if(s_group != e_group){
            res += edges[i].c;
            union_group(edges[i].s, edges[i].e);
        }
    }
    cout << res;
}
