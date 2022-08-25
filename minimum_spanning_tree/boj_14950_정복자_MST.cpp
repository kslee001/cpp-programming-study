// https://www.acmicpc.net/problem/14950 정복자 MST

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using lint = long long;

struct edge{
    int start, end;
    lint cost;
    edge(){}
    edge(int a,int b,lint c){
        start = a;
        end   = b;
        cost  = c;
    }
    bool operator<(const edge e){return cost<e.cost;}
};

int n,m,t;
int curt = 0;
lint maxcost;
lint mincost;
int parent[10001];
vector<edge> edges;

int FIND(int a){
    if(parent[a] == a) return a;
    return parent[a] = FIND(parent[a]);
}
void UNION(int a, int b){
    parent[FIND(a)] = FIND(b);
}

void init(){
    cin >>n>>m>>t;
    for(int i=0; i<n; ++i)
        parent[i] = i;
    for(int i=0; i<m; ++i){
        int a,b,c; cin >>a>>b>>c;
        edges.push_back(edge(a,b,c));
        maxcost += c;
    }
    sort(edges.begin(), edges.end());
}
void kruskal(){
    for(int i=0; i<edges.size(); ++i){
        edge cur = edges[i];
        int sg = FIND(cur.start);
        int eg = FIND(cur.end);
        if(sg != eg){
            UNION(cur.start, cur.end);
            mincost += cur.cost + curt;
            curt += t;
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    init();
    kruskal();
    cout << mincost;
}
