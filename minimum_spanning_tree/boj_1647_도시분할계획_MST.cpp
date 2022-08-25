// https://www.acmicpc.net/problem/1647 도시 분할 계획
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct edge{
    int start;
    int end;
    int dist;
    edge(int a, int b, int c){start = a; end = b; dist = c;}
    bool operator<(const edge e){ return dist < e.dist; }
};

int n,m;
int parent[100001];
vector<edge> edges;

int find_group(int a){
    if(parent[a] == a) return a;
    else               return parent[a] = find_group(parent[a]);
}

void group_union(int a, int b){
    parent[find_group(a)] = find_group(b);
}

void init(){
    cin >>n>>m;
    for(int i=1; i<=n; ++i){
        parent[i] = i; // 등록
    }
    for(int i=0; i<m; ++i){
        int a,b,c; cin >>a>>b>>c;
        edges.push_back(edge(a,b,c));
    }
    sort(edges.begin(), edges.end());
}

int main(){
    init();
    long long res  = 0;
    int max_dist = INT_MIN;
    for(int i=0; i<m; ++i){
        int s_group = find_group(edges[i].start);
        int e_group = find_group(edges[i].end);

        if(s_group != e_group){
            res += edges[i].dist;
            if(max_dist < edges[i].dist) max_dist = edges[i].dist;
            group_union(edges[i].start, edges[i].end);
        }
    }
    cout << res-max_dist;
}