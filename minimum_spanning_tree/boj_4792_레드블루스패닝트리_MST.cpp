// https://www.acmicpc.net/problem/4792 레드블루스패닝트리
#include <iostream>
#include <algorithm>
#include <vector>
#define RED 0
#define BLUE 1
using namespace std;
using edge = pair<int, pair<int,int>>;


// red first
bool red_comp(const edge e1, const edge e2){return e1.first<e2.first;}
// blue first
bool blue_comp(const edge e1, const edge e2){return e1.first>e2.first;}


int n,m,k;
int parent[1001];
vector<edge> edges[2];

int f_parent(int a){
    if (parent[a] == a) return a;
    return f_parent(parent[a]);
}

void u_parent(int a, int b){
    parent[f_parent(a)] = f_parent(b);
}


bool init(){
    cin >>n>>m>>k;
    if(n==0 && m==0 && k==0) return false;
    edges[0].clear(); edges[1].clear();
    // input
    for(int i=0; i<m; ++i){
        char c; int s,e;
        cin >>c>>s>>e;
        if(c == 'B'){
            edges[0].push_back(edge(1, {s,e}));
            edges[1].push_back(edge(1, {s,e}));
        }
        else{ // (c == 'R')
            edges[0].push_back(edge(0, {s,e}));
            edges[1].push_back(edge(0, {s,e}));
        }       
    }

    sort(edges[0].begin(), edges[0].end());
    sort(edges[1].begin(), edges[1].end(), blue_comp);

    return true;
}


int kruskal(int c){ // 0 : red, 1 : blue
    int num_edge = 0;
    int num_blue = 0;
    // reset
    for(int i=1; i<=n; ++i){
        parent[i] = i;
    }
    for(int i=0; i<m; ++i){
        int is_blue = edges[c][i].first; // is a blue node?

        int sg = f_parent(edges[c][i].second.first);
        int eg = f_parent(edges[c][i].second.second);
        if(sg != eg){
            u_parent(edges[c][i].second.first, edges[c][i].second.second);
            num_blue += is_blue; // 1 if blue node else 0
            ++num_edge;       // total number of edges
        }

        // all nodes are linked
        if(num_edge == n-1) return num_blue;
    }

    // not all nodes are linked, making MST failed
    return -1;
}

int main(){
    while(init()){
        int min_blue = kruskal(RED); // red first
        int max_blue = kruskal(BLUE); // blue first

        if(min_blue == -1 || max_blue == -1)
            cout << "0\n";
        else if(min_blue <= k && k <= max_blue)
            cout << "1\n";
        else
            cout << "0\n";
    }
}