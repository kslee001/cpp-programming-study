// boj_14503_로봇청소기_simulation



#include <bits/stdc++.h>
using namespace std;

int room[50][50];
int vis[50][50];
int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};
int idx;
#define Y first
#define X second

int n,m, sy,sx, sdir;
int y, x, dir;
void input(){
    cin >> n >> m >> sy >> sx >> sdir;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cin >> room[i][j];
        }
    }
}
// void debug(int mod=0){
//     if(!mod){
//         printf("\n\n");
//         for(int i=0; i<n; ++i){
//             for(int j=0; j<m; ++j){
//                 if(room[i][j]==1) vis[i][j] = -1;
//                 if(vis[i][j]>= 10 || vis[i][j] == -1) printf(" %d ", vis[i][j]);
//                 else printf("  %d ", vis[i][j]);
//             }printf("\n");
//         }
//     }
//     if(mod) printf("(%d, %d), dir = %d \n", y,x,dir);
// }

bool wall(pair<int,int> look){return room[look.Y][look.X];}
bool cleaned(pair<int,int> look){return vis[look.Y][look.X];}


void clean_room(int y, int x){ // check vis & add area cleaned
    vis[y][x] = 1;
}

pair<int,int> left_aux(int ny, int nx, int dir){
    pair<int,int> look;
    if(dir == 0){look = {ny, nx-1};} // 북->서
    if(dir == 1){look = {ny-1, nx};} // 동->북
    if(dir == 2){look = {ny, nx+1};} // 남->동
    if(dir == 3){look = {ny+1, nx};} // 서->남
    return look;
}

bool check_left(int y, int x, int dir){
    // 0 : 북쪽,  1: 동쪽,  2:남쪽  , 3: 서쪽
    pair<int,int> look = left_aux(y,x,dir);
    if(wall(look))    return false;
    if(cleaned(look)) return false;
    return true;
}

void turn_left(int &dir){
    dir = (dir-1+4)%4;
}

void move_front(int &y, int &x, const int dir){ // update y and x
    pair<int,int> front;
    int ny = y; int nx= x;
    if(dir==0){front = {ny-1, nx};} // 북-> 위로 한칸
    if(dir==1){front = {ny, nx+1};} // 동 -> 동쪽으로 한칸
    if(dir==2){front = {ny+1, nx};} // 남 -> 아래로 한칸
    if(dir==3){front = {ny, nx-1};} // 서 -> 서쪽으로 한칸   
    y = front.Y;
    x = front.X;
}

bool move_back(int &y, int &x, const int dir){ // update y and x
    pair<int,int> back;
    int ny = y; int nx = x;
    if(dir==0){back = {ny+1, nx};} // 북-> 아래로 한칸
    if(dir==1){back = {ny, nx-1};} // 동 -> 서쪽으로 한칸
    if(dir==2){back = {ny-1, nx};} // 남 -> 위로 한칸
    if(dir==3){back = {ny, nx+1};} // 서 -> 동쪽으로 한칸    
    if(wall(back)) return false; // 벽으로 막히면 false
    y = back.Y;
    x = back.X; // 아니라면 업데이트 후 true
    // printf("move back ! : (%d, %d) - %d\n", y, x, vis[y][x]);
    return true;
}

int result(){
    int res = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            res += vis[i][j]; 
        }
    }
    return res;
}

int main(){
    input();
    bool power = true;
    bool left; int left_cnt;
    y = sy; x = sx; dir = sdir;
    
    while(power){
        // 1. 현재 위치를 청소한다
        clean_room(y,x);
        
        // 2. 현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색
        left_cnt = 0; left = false; 
        int original_dir = dir;
        while(left_cnt<=4){
            ++left_cnt;
            // 2-1. 왼쪽 방향에 아직 청소하지 않은 공간이 존재하는 경우
            if(check_left(y,x,dir)){
                turn_left(dir);      // 그 방향으로 회전하고
                move_front(y,x,dir); // 한 칸 전진 후 1번부터 진행
                left = true; 
                break;
            }
            // 2-2. 왼쪽 방향에 청소할 공간이 없는 경우, 회전한 다음 2번으로 돌아감 
            turn_left(dir);            
        }
        if(left) continue; // (2-1의 연장, 1번부터 진행)

        // 2-3 네 방향 모두 청소가 되어 있거나 벽인 경우, 바라보는 방향을 유지한 채로 한 칸 후진한 뒤 2번으로 돌아감
        dir = original_dir;
        power = move_back(y,x,dir);
        if(vis[y][x] >= 59) break;
        // 2-4 만약 뒤로 후진할 수 없는 경우 power 가 false 가 되면서 종료됨
    }
    // debug();
    int res = result();
    cout << res;
}