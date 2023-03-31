#include <bits/stdc++.h>
using namespace std;

/* 2468 안전영역
5
6 8 2 6 2
3 2 3 4 6
6 7 3 3 2
7 2 5 3 6
8 9 5 2 7

5
*/




int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};
int n;  
int y, x;
int ny,nx;
int max_h = 0;


void debug(int arr[][100]){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            printf("%d ", arr[i][j]);
        } printf("\n");
    }
}

void input(int board[][100], int visit[][100]){
    scanf("%d",&n);
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            scanf("%d", &board[i][j]);
            if(board[i][j]>max_h){
                max_h = board[i][j];  // max_h 정의
            }
        }
    }
}

bool oob(int y, int x){return (y>=0 && y<n && x>=0 && x<n);}

void reset(int visit[][100]){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            visit[i][j] = 0;
        }
    }
}


int dfs(int rain, int board[][100], int visit[][100]){
    reset(visit); // reset visit map

    stack<pair<int,int>> stk;
    pair<int,int> cur;
    int num_area = 0;
    // dfs
    int idx = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if      (visit[i][j])        continue;
            else if (board[i][j]<= rain) continue;
            else {
                num_area ++;
                // printf(" dfs begin with (%d %d)\n",i, j );
                stk.push({i,j});
                while(!stk.empty()){
                    cur = stk.top(); stk.pop();
                    y = cur.first;
                    x = cur.second;
                    if(oob(y,x)==false || visit[y][x]) continue;
                    idx++;
                    visit[y][x] = idx;
                    // ENQUEUE
                    for(int d=0; d<4; ++d){
                        ny = y + dy[d];
                        nx = x + dx[d];
                        if(oob(ny,nx) && !visit[ny][nx] && board[ny][nx]>rain){ stk.push({ny,nx}); }
                    }  
                }
            }
        }
    }    

    // dfs begin with starting area


    return num_area; 
}

//  1 <= h    <= 100 
//  1 <= rain <= 100

int main(){
    int board[100][100];
    int visit[100][100];
    input(board, visit);


    int res = 0;
    int temp = 0;
    for(int i=0; i<max_h; ++i){
        temp = dfs(i, board, visit);
        if(temp > res){
            res = temp;
        }
    }
    printf("%d", res);

    // debug_visit();
}