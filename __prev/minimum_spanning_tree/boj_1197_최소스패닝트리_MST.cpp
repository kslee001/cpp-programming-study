// https://www.acmicpc.net/problem/1197 최소 스패닝 트리
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class edge{
public:
    int start,end,dist;
    edge(int a, int b, int c){start = a; end = b; dist = c;};
};
bool operator<(const edge& e1, const edge& e2){
    return e1.dist < e2.dist;
}

int num_v, num_e;
long long res;
int parent[10001];
vector<edge> edges;

void init(){
    cin >> num_v >>num_e;
    for(int i=1; i<=num_v; ++i){
        parent[i]=i; // 자기 자신을 새로운 그룹으로 등록
    }

    for(int i=0; i<num_e; ++i){
        int a,b,c; cin >>a>>b>>c;
        edges.push_back(edge(a,b,c));
    }
    sort(edges.begin(), edges.end());
}

int find_group(int v){
    if(parent[v] == v) 
        return v;
    else            
        return parent[v] = find_group(parent[v]); // 
        // 할당 및 return 
}

void group_union(int a, int b){
    parent[find_group(a)] = find_group(b);
}

int main(){
    init();
    for(int i=0; i<num_e; ++i){
        int s_group = find_group(edges[i].start);
        int e_group = find_group(edges[i].end);

        if(s_group != e_group){
            res+= edges[i].dist; // 거리 더하기
            group_union(edges[i].start, edges[i].end);
        }
    }
    cout << res;
}