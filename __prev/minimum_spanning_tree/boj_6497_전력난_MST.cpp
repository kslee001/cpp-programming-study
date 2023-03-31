// https://www.acmicpc.net/problem/6497 전력난 MST
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct edge{
    int s,e,c;
    edge(){}
    edge(int a,int b, int d){s=a;e=b;c=d;}
    bool operator<(const edge e){return this->c<e.c;}
};

int n,m;
int max_val;
int min_val;
int parent[200000];
vector<edge> edges;

int FIND(int a){
    if(parent[a] == a) return a;
    return parent[a] = FIND(parent[a]);
}
void UNION(int a, int b){
    parent[FIND(a)] = FIND(b);
}
bool init(){
    cin >>n>>m;
    if(n==0 && m==0) return false; // input 0 0
    // reset
    edges.clear();
    max_val = 0;
    min_val = 0;

    // vertices
    for(int i=0; i<n; ++i){
        parent[i] = i;
    }
    // edges
    for(int i=0; i<m; ++i){
        int s,e,c; cin>>s>>e>>c;
        max_val = max_val + 1LL*c; // 모든 집 연결할 때의 cost
        edges.push_back(edge(s,e,c));
    }
    sort(edges.begin(), edges.end());
    return true;
}

int kruskal(){
    int res = 0;
    for(int i=0; i<edges.size(); ++i){
        edge cur = edges[i];
        int sg = FIND(cur.s);
        int eg = FIND(cur.e);
        if(sg != eg){
            UNION(cur.s, cur.e);
            res += cur.c;
        }
    }
    return res;
}

int main(){
    init();
    cout << max_val-kruskal();
    while(init()){
        cout <<"\n";
        cout << max_val - kruskal();
    }
}
