#include <bits/stdc++.h>
using namespace std;

/*
s : 0<=N<=100000
d : 0<=K<=100000
s -> X-1 or X+1 or 2*X
----------
5 17 
4
*/


int n,k;

bool in_bound(int cur){return cur>=0 && cur<=100000;}
bool found(int cur){return cur == k;}

int main(){
    int visit[100001];
    fill(visit, visit+100001, -1);
    scanf("%d%d", &n,&k);
    visit[n]=0;
    queue<int> que;
    que.push(n);

    int cur; int arr[3]; int target;
    while(visit[k] == -1){
        cur = que.front(); que.pop();
        for(int target : {cur-1, cur+1, 2*cur}){
            if(in_bound(target)==false) continue;
            if(visit[target]!= -1) continue;
            que.push(target);
            visit[target] = visit[cur] +1;
        }
    }
    printf("%d", visit[k]);

}