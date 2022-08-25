// https://www.acmicpc.net/problem/10423 전기가부족해
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int n,m,k;
int group[1001];
bool linked[1001];

int get_group(int a){
    if(group[a] == a) return a;
    else return group[a] = get_group(group[a]);
}
void union_group(int a, int b){
    group[get_group(a)] = get_group(b);
}
void lighten(int a){
    linked[get_group(a)] = true;
}

struct edge{
    int s,e,c;
    edge(){}; 
    edge(int a, int b, int d){s=a; e=b; c=d;}
    bool operator<(const edge e){return c<e.c;}
};

vector<edge> edges;
vector<edge> cal;

int main(){
    long long res = 0;
    cin >> n >> m >> k;
    // 도시 만들기
    for(int i=1; i<=n; ++i){
        group[i] = i;
    }
    // 발전소 체크하기
    for(int i=0; i<k; ++i){
        int x; cin >>x;
        linked[x] = true;
        group[x] = 0;
    }  
    // 간선 만들기
    for(int i=0; i<m; ++i){
        int a,b,d; cin >>a>>b>>d;
        edges.push_back(edge(a,b,d));
    }
    // 간선 정렬
    sort(edges.begin(), edges.end());

    for(int i=0; i<m; ++i){
        int sg = get_group(edges[i].s);
        int eg = get_group(edges[i].e);
        if(sg != eg){
            // 두 도시 모두 연결된 경우
            if(linked[sg] && linked[eg])
                continue;   
            
            // 시작점이 연결되어 있는 경우
            else if(linked[sg] && !linked[eg]){
                lighten(eg);
                union_group(eg, sg);
            }
            // 끝점이 연결되어 있는 경우
            else if(linked[eg] && !linked[sg]){
                lighten(sg);
                union_group(sg, eg);
            }
            else{
                union_group(sg, eg);
            }
            res += edges[i].c;
        }
    }
    cout << res;
}
