// https://www.acmicpc.net/problem/1717 집합의 표현 Disjoint Set
#include <iostream>
using namespace std;

int parent[1000001];
int level [1000001];

int FIND(int a){
    if(parent[a] == a) return a;
    return parent[a] = FIND(parent[a]);
}

void UNION(int a,int b){
    a = FIND(a);
    b = FIND(b);
    if(a != b){
        if(level[a] < level[b])
            parent[a] = b;
        else
            parent[b] = a;
    }

    if(level[a] == level[b]) level[a]++;
}

bool SAME(int a, int b){
    return FIND(a) == FIND(b);
}

int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin >>n>>m;
    cin.tie(0);
    for(int i=1; i<=n; ++i){
        parent[i] = i;
         level[i] = 0;
    }
    for(int i=0; i<m; ++i){
        int a,b,c; cin>>a>>b>>c;
        if(!a) UNION(b,c);
        else{
            if(SAME(b, c)) cout <<"YES\n";
            else           cout <<"NO\n";
        }
    }
    
}