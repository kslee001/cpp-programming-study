// https://www.acmicpc.net/problem/1185 유럽여행 MST
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
using lint = long long;
struct edge{
    int s, e, c;
    edge(){}
    edge(int a,int b,int d){s=a;e=b;c=d;}
    bool operator<(const edge e){return this->c < e.c;}
};

int n, m;
int parent[10000];
int cost[10000];
bool vis[10000];
vector<edge> edges;
int s_point;

int FIND(int a){
    if(parent[a] == a) return a;
    return parent[a] = FIND(parent[a]);
}
void UNION(int a, int b){
    parent[FIND(a)] = FIND(b);
}
void init(){
    cin >>n>>m;
    //vertices
    int min_cost = INT_MAX;
    for(int i=0; i<n; ++i){
        parent[i] = i;
        cin >> cost[i];
        if(min_cost > cost[i]){
            min_cost = cost[i];
            s_point = i;
        }
    }
    //edges
    for(int i=0; i<m; ++i){
        int s,e,c; cin >>s>>e>>c;
        --s; --e;
        c*= 2; // cost 2배
        c += cost[s];
        c += cost[e]; // visit cost
        edges.push_back(edge(s,e,c));
    }
    sort(edges.begin(), edges.end());
}

lint kruskal(){
    lint res = 0;
    for(int i=0; i<edges.size(); ++i){
        edge cur = edges[i];
        int sg = FIND(cur.s);
        int eg = FIND(cur.e);
        if(sg != eg){
            UNION(cur.s, cur.e);
            res += cur.c; // cost
        }
    }
    return res;
}

int main(){
    init();
    cout <<kruskal() + cost[s_point];
}