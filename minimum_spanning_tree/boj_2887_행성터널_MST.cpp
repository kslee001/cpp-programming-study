// https://www.acmicpc.net/problem/2887 행성터널 MST
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

int n;
struct edge{
    int start, end, dist;
    edge(int a, int b, int c){start = a; end = b; dist = c;}
};
bool operator<(const edge e1, const edge e2){
    return e1.dist > e2.dist;
}

int parent[100001];

struct vertex{
    int idx, val;
    bool operator<(const vertex v){
        return val<v.val;
    }
};
vector<vertex> V_x;
vector<vertex> V_y;
vector<vertex> V_z;
priority_queue<edge> E;

int s[2];

void init(){
    cin >>n;
    // vertices
    for(int i=0; i<n; ++i){
        int x,y,z; cin >>x>>y>>z;
        V_x.push_back({i,x});
        V_y.push_back({i,y});
        V_z.push_back({i,z});
        parent[i] = i;
    }
    // edges
    sort(V_x.begin(), V_x.end());
    sort(V_y.begin(), V_y.end());
    sort(V_z.begin(), V_z.end());
    for(int i=0; i<n-1; ++i){
        vertex cur = V_x[i];
        vertex nxt = V_x[i+1];
        int dist   = abs(cur.val - nxt.val);
        E.push(edge(cur.idx, nxt.idx, dist));
    }
    for(int i=0; i<n-1; ++i){
        vertex cur = V_y[i];
        vertex nxt = V_y[i+1];
        int dist   = abs(cur.val - nxt.val);
        E.push(edge(cur.idx, nxt.idx, dist));
    }
    for(int i=0; i<n-1; ++i){
        vertex cur = V_z[i];
        vertex nxt = V_z[i+1];
        int dist   = abs(cur.val - nxt.val);
        E.push(edge(cur.idx, nxt.idx, dist));
    }
}

int find_group(int a){
    if(parent[a] == a) return a;
    else               return parent[a] = find_group(parent[a]);
}
void union_group(int a, int b){
    parent[find_group(a)] = find_group(b);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    long long res = 0;

    while(E.size()){
        edge cur = E.top(); E.pop();
        int s_group = find_group(cur.start);
        int e_group = find_group(cur.end);
        if(s_group != e_group){
            res += cur.dist;
            union_group(cur.start, cur.end);
        }
    }
    cout << res;


}
