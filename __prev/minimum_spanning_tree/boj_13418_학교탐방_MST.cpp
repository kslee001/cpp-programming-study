// https://www.acmicpc.net/problem/13418 학교탐방 MST
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using lint = long long;
struct edge{
    int s,e,c;
    edge(){}
    edge(int a,int b,int d){s=a;e=b;c=d;}
};

// 0 first
bool uphill_first(const edge& e1, const edge& e2){
    return e1.c < e2.c; 
}
// 1 first
bool downhill_first(const edge& e1, const edge& e2){
    return e1.c > e2.c;
}

int n,m;
int max_val, min_val;
int parent[1000];
int starting_point;
vector<edge> edges;

int FIND(int a){
    if(parent[a] == a) return a;
    return parent[a] = FIND(parent[a]);
}
void UNION(int a,int b){
    parent[FIND(a)] = FIND(b);
}
void init(){
    cin >>n>>m;
    int s, e, c; cin >>s>>e>>c;
    starting_point = 1-c;

    for(int i=0; i<m; ++i){
        cin >>s>>e>>c;
        edges.push_back(edge(s,e,1-c));
    }
}
int kruskal(int mod){
    int res = 0;
    // reset
    for(int i=1; i<=n; ++i)
        parent[i] = i;
    
    // sort edges
    if(mod == 0)
        sort(edges.begin(), edges.end(), uphill_first);
    else
        sort(edges.begin(), edges.end(), downhill_first);
    
    // get MST
    for(int i=0; i<edges.size(); ++i){
        edge cur = edges[i];
        int sg = FIND(cur.s);
        int eg = FIND(cur.e);
        if(sg == eg) continue;
        UNION(cur.s, cur.e);
        res += cur.c;
    }
    return res;
}

int main(){
    init();
    max_val = kruskal(1) + starting_point;
    min_val = kruskal(0) + starting_point;
    cout << max_val*max_val - min_val*min_val;
}
