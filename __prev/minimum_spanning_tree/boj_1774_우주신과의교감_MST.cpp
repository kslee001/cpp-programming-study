// https://www.acmicpc.net/problem/1774 우주신과의 교감 MST
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#define Y first
#define X second
using namespace std;
using lint = long long;
struct edge{
    int start;
    int end;
    long double dist;
    edge(){};
    edge(int s, int e, long double d){
        start = s;
        end = e;
        dist = d;
    }
    bool operator<(const edge e){
        return dist < e.dist;
    }
};
int n,m;
int parent[1000];
long double res;  // target
vector<pair<lint, lint>> V;
map<pair<int,int>, long double> E;
vector<edge> edges;

long double get_dist(lint y1, lint x1, lint y2, lint x2){
    return sqrt((y1-y2)*(y1-y2) + (x1-x2)*(x1-x2));
}

int find_group(int a){
    if(parent[a] == a) return a;
    else return parent[a] = find_group(parent[a]);
}

void union_group(int a, int b){
    parent[find_group(a)] = find_group(b);
}

void init(){
    cin >>n>>m;
    // get vertices
    for(int i=0; i<n; ++i){
        lint y,x;
        cin >>y>>x;
        V.push_back({y,x});
        parent[i] = i;
    }

    // get all possible edges
    for(int i=0; i<n-1; ++i){
        for(int j=i+1; j<n; ++j){
            pair<int,int> cur = make_pair(i,j);
            long double dist = get_dist(V[i].Y, V[i].X, V[j].Y, V[j].X);
            E[cur] = dist;
        }
    }

    // get already linked edges
    for(int i=0; i<m; ++i){
        int s,e; cin >>s>>e;
        --s; --e;
        pair<int,int> cur = make_pair(s,e);
        union_group(s, e);
        E[cur] = 0;
    }

    map<pair<int,int>, long double>::iterator iter;
    for(iter = E.begin(); iter != E.end(); ++iter){
        edges.push_back(edge(iter->first.first, iter->first.second, iter->second));
    }
    sort(edges.begin(), edges.end());
}

int main(){
    init();

    vector<edge>::iterator iter;  
    for(iter = edges.begin(); iter != edges.end(); ++iter){
        int s_group = find_group(iter->start);
        int e_group = find_group(iter->end);
        if(s_group != e_group){
            res += iter->dist;
            union_group(iter->start, iter->end);
        }
    }
    printf("%.2Lf", res);
    
}