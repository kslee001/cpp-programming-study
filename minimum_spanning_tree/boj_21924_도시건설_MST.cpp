// https://www.acmicpc.net/problem/21924 도시건설 MST
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using lint = long long;

struct edge{
    int start, end; 
    lint cost;
    edge(){}
    edge(int a, int b, lint c){
        start = a;
        end   = b;
        cost  = c;
    }
    bool operator<(const edge e){return cost < e.cost;}
};

int n,m;
lint maxcost = 0;
lint mincost = 0;
vector<edge> edges;
int parent[100001];

int FIND(int a){
    if(parent[a] == a) return a;
    return parent[a] = FIND(parent[a]);
}

void UNION(int a, int b){
    parent[FIND(a)] = FIND(b);
}

void init(){
    cin >>n>>m;
    for(int i=0; i<n; ++i)
        parent[i] = i;
    for(int i=0; i<m; ++i){
        int a,b; lint c; cin >>a>>b>>c;
        edges.push_back(edge(a,b,c));
        maxcost += c; // maximum cost
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
            mincost += cur.cost;
        }
    }
}

bool check(){
    int standard = FIND(0);
    for(int i=1; i<n; ++i){
        if(FIND(i) != standard) return false; 
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    kruskal();

    bool flag = check();
    if(flag)
        cout << maxcost - mincost;
    else
        cout << -1;
}

