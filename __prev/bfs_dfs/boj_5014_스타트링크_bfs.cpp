#include <bits/stdc++.h>
using namespace std;

int f,s,g,u,d;

void input(){
    scanf("%d%d%d%d%d", &f,&s,&g,&u,&d
    );}

int main(){
    input();
    int visit[1000002];
    memset(visit, -1, 1000002*sizeof(int));

    int target = g;
    int cur_floor = s; // 변수가 눈에 잘 안보여서 변경
    visit[cur_floor] = 0;
    if(cur_floor == target){
        printf("%d", 0);
        return 0;
    }

    queue<int> que; //  < position >    
    que.push(cur_floor);
    while(!que.empty()){
        cur_floor = que.front(); 
                    que.pop();
        if(cur_floor == target){
            printf("%d", visit[cur_floor]);
            return 0;
        }
        // printf("%d / %d\n", cur_floor, visit[cur_floor]); 
        // up ENQUE
        if(cur_floor+u<=f && visit[cur_floor+u]==-1 && u){
            visit[cur_floor+u]= visit[cur_floor]+1;
            que.push(cur_floor+u);
        }
        // down ENQUE
        if(cur_floor-d>0 && visit[cur_floor-d]==-1 && d){
            visit[cur_floor-d]= visit[cur_floor]+1;
            que.push(cur_floor-d);
        }
    }
    printf("use the stairs");


}