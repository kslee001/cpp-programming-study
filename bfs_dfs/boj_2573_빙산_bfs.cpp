// https://www.acmicpc.net/problem/2573
// 빙산 (BFS)
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <tuple>
#define Y first
#define X second
using namespace std;

int n,m;
int board[300][300];
int color[300][300];
bool visit[300][300];
int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};
tuple<int,int,int> pos;
stack<tuple<int,int,int>> melting;

bool oob(int y, int x){return y<0||x<0||y>=n||x>=m;}
void input(){
    cin >>n>>m;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cin >>board[i][j];
        }
    }
}
void reset(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            visit[i][j] = false;
        }
    }
}
int dfs(){
    reset();
    stack<pair<int,int>> stk;
    int c = 1;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            if(visit[i][j]) continue;
            if(board[i][j] == 0) continue; //water
            stk.push({i,j}); 
            visit[i][j] = true;
            color[i][j] = c;
            pair<int,int> cur;
            while(stk.size()){
                cur = stk.top(); stk.pop();
                int num_water = 0;
                for(int d=0; d<4; ++d){
                    int ny = cur.Y+dy[d];
                    int nx = cur.X+dx[d];
                    if(oob(ny,nx)) continue;
                    if(board[ny][nx] == 0 ){
                        ++num_water;
                        continue;
                    }
                    if(visit[ny][nx]) continue;
                    visit[ny][nx] = true;
                    color[ny][nx] = c;
                    stk.push({ny,nx});
                }
                if(num_water){
                    melting.push({cur.Y, cur.X, num_water}); // save
                }
            }
            ++c; 
        }
    }
    return c-1;
}
void melt(){
    while(melting.size()){
        tuple<int,int,int> cur = melting.top(); melting.pop();
        int y = get<0>(cur);
        int x = get<1>(cur);
        int z = get<2>(cur);
        board[y][x] = board[y][x] - z;
        if(board[y][x]<0) board[y][x] = 0;
    }
}

void debug(){
    printf("\n-debug-\n");
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    input();
    if(dfs() >=2){
        cout << 0;
        return 0;
    }
    //// 
    int time = 0;
    while(true){
        ++time;
        melt();
        int n_ice = dfs();
        if(n_ice>=2){
            debug();
            break;
        }
        if(n_ice ==0){
            time = 0;
            break;
        }
    }
    cout << time;    
}