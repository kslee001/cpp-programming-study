// https://www.acmicpc.net/problem/4386 별자리 만들기
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;


struct vertex{
    float x, y;
    vertex(float a, float b){x = a; y = b;}
};

struct edge{
    int start;
    int end;
    float dist;
    edge(int a, int b, float c){start = a; end = b; dist = c;}
};
bool operator<(const edge e1, const edge e2){return e1.dist > e2.dist;}

int n;
int parent[101];
vector<vertex> V;
priority_queue<edge> E;
float get_dist(vertex a, vertex b){ 
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); 
}

int s[10];
void get_edges(){
    for(int i=0; i<n-1; ++i){
        for(int j=i+1; j<n; ++j){
            vertex a = V[i];
            vertex b = V[j];
            float dist = get_dist(a, b);
            E.push({i,j,dist});
        }
    }
}

int find_parent(int a){
    if(parent[a] == a) return a;
    else               return parent[a] = find_parent(parent[a]);
}

void group_union(int a, int b){
    parent[find_parent(a)] = find_parent(b);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >>n;
    for(int i=1; i<=n; ++i){
        float a, b; cin >>a>>b;
        V.push_back(vertex(a,b));
        parent[i] = i;
    }
    // get all possible edges
    get_edges();

    float res = 0;
    while(E.size()){
        edge cur = E.top(); E.pop();
        int s_group = find_parent(cur.start);
        int e_group = find_parent(cur.end);

        if(s_group != e_group){
            res += cur.dist;
            group_union(cur.start, cur.end);        
        }
    }
    printf("%.2lf", res);
}


