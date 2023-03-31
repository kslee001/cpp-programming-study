// https://www.acmicpc.net/problem/14574 헤븐스 키친

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <stack>
using namespace std;

int parent[1000];
vector<pair<int,int>> player;
struct edge{
    int start;
    int end;
    int score;
    edge(){}
    edge(int a, int b, int c){start =a; end = b; score = c;}
    bool operator<(const edge e){return score>e.score;}
};
vector<edge> edges;
vector<pair<int,int>> versus;
vector<pair<int,int>> adj[1000];  // pos, score

int get_parent(int a){
    if(parent[a]==a) return a;
    else return parent[a] = get_parent(parent[a]); 
}
void union_parent(int a, int b){
    parent[get_parent(a)] = get_parent(b);
}
int get_score(int a, int b){
    pair<int,int> p1 = player[a];
    pair<int,int> p2 = player[b];
    int up = p1.second + p2.second;
    int down = abs(p1.first - p2.first);
    int ret = floor(up/down);
    return ret;
}


bool visit[1000];
void print_func(int here){
    visit[here]=true;
    for(int i=adj[here].size()-1;i>=0;--i){
        int next = adj[here][i].first;
        if(!visit[next]){
            print_func(next);
            printf("%d %d\n", here+1,next+1);
        }
    }
}

int n;
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
    cin >>n;
    for(int i=0; i<n; ++i){
        int p,c; cin >>p >> c;
        player.push_back(make_pair(p,c));
        parent[i] = i;
    }
    for(int i=0; i<n-1; ++i){
        for(int j=i+1; j<n; ++j){
            int sc = get_score(i, j);
            edges.push_back(edge(i,j,sc));
        }
    }
    sort(edges.begin(), edges.end());

    long long res = 0;
    int temp = 0;
    for(int i=0; i<edges.size(); ++i){
        int sg = get_parent(edges[i].start);
        int eg = get_parent(edges[i].end);
        if(sg != eg){
            union_parent(edges[i].start, edges[i].end);     
            res += edges[i].score;       
            // cnt[edges[i].start] = temp;
            // cnt[edges[i].end]   = temp;
            // cout << edges[i].start << " " << edges[i].end << "\n";
            adj[edges[i].start].push_back({edges[i].end, edges[i].score});
            adj[edges[i].end].push_back({edges[i].start, edges[i].score});
        }
    }

    cout << res <<"\n";
    print_func(n-1);

}


