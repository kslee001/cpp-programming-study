// https://www.acmicpc.net/problem/14621 나만안되는연애_MST
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge{
    int start;
    int end;
    int dist;
    edge();
    edge(int s, int e, int d){
        start = s;
        end = e;
        dist = d;
    }
};

int n,m;
int parent[1000];
bool color[1000];
bool linked[1000];
vector<edge> edges;

bool operator<(const edge e1, const edge e2){
    return e1.dist < e2.dist;
}

int get_group(int a){
    if(parent[a] == a) return a;
    else return parent[a] = get_group(parent[a]);
}
void union_group(int a, int b){
    parent[get_group(a)] = get_group(b);
}

void input(){
    // 5 7
    cin >> n >> m; 
    // M W W W M  -> color
    for(int i=0; i<n; ++i){
        char c; cin >>c;
        if(c == 'M')
            color[i] = true;
        else // c == 'W'
            color[i] = false;
        parent[i] = i;
    }
    // 1 2 12 ... 5 4 7
    for(int i=0; i<m; ++i){
        int a,b,d; cin >>a>>b>>d;
        edges.push_back(edge(a-1, b-1, d));
    }
    sort(edges.begin(), edges.end());
}

bool check_link(){
    for(int i=0; i<n; ++i)
        if(!linked[i]) return false;
    return true;
}

int main(){
    input();
    long long res = 0;
    for(int i=0; i<m; ++i){
        int s_group = get_group(edges[i].start);
        bool s_color = color[edges[i].start];

        int e_group = get_group(edges[i].end);
        bool e_color = color[edges[i].end];

        if(s_group != e_group && s_color != e_color){
            res += edges[i].dist;
            union_group(edges[i].start, edges[i].end);
            linked[edges[i].start] = true;
            linked[edges[i].end] = true;
        }
    }
    if(check_link()) cout << res;
    else cout << -1;
}