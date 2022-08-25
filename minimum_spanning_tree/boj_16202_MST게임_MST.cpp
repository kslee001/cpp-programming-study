// https://www.acmicpc.net/problem/16202 MST게임 MST
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using lint = long long;

struct edge{
    int start, end;
    lint cost;
    edge(){}
    edge(int a, int b, int c){
        start = a; end = b; cost = c;
    }
    bool operator<(const edge e){return cost <e.cost;}
};

int n,m,k;
int parent[1001];
vector<edge> edges;
edge minimum_edge;
vector<edge> MST;

int FIND(int a){
    if(parent[a] == a) return a;
    return parent[a] = FIND(parent[a]);
}
void UNION(int a, int b){
    parent[FIND(a)] = FIND(b);
}

lint kruskal(){
    lint curval = 0;
    int num_edges = 0;
    for(int i=0; i<edges.size(); ++i){
        edge cur = edges[i];
        int sg = FIND(cur.start);
        int eg = FIND(cur.end);
        if(sg != eg){
            UNION(cur.start, cur.end);
            curval += cur.cost;
            ++num_edges;
        }
    }
    if(num_edges == n-1) return curval;
    return -1;
}

void reset(){
    for(int i=1; i<=n; ++i)
        parent[i] = i;
}

bool check(){
    int s = parent[0];
    for(int i=1; i<n; ++i){
        if(parent[i] != s) return false;
    }
    return true;
}

void init(){
    cin >>n>>m>>k;
    for(int i=0; i<m; ++i){
        int a,b; cin >>a>>b;
        edges.push_back(edge(a,b,i+1));
    }
    sort(edges.begin(), edges.end());
}

int main(){
    init();
    for(int i=0; i<k; ++i){
        reset();
        lint curval = kruskal();
        if(curval == -1) cout <<"0 ";
        else cout << curval <<" ";
        edges.erase(edges.begin());
    }
}

