#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#define Y first
#define X second
using namespace std;

int n,m;
int board[8][8];
bool visit[8][8];
int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

int area;
int expandable;

vector<pair<int,int>> empty_place;
vector<pair<int,int>> virus;
int cases[50000][3];
int s[3];
int num_cases;
int idx = 0;

void input(){
    cin >>n>>m;
    area = n*m;         // board 넓이
    expandable = area;  // board에서 벽 제외한 넓이 
                        // -> bfs시 expandable만큼의 영역을 칠했는지 확인할 것임
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cin >>board[i][j];
            if(!board[i][j]) empty_place.push_back({i,j}); 
            if(board[i][j] == 2) virus.push_back({i,j});
            if(board[i][j] == 1) --expandable;
        }
    }
    // 추가될 wall 고려한 넓이
    expandable = expandable -3;    
    
    int size = empty_place.size();
    num_cases = (size*(size-1)*(size-2))/(3*2*1); // M C 3 
    // printf("empty_place size : %d / num_cases : %d\n", empty_place.size(), num_cases);
}
void make_cases(int k, int st){
    if(k==3){
        for(int i=0; i<3; ++i){
            cases[idx][i]=s[i];
        }
        ++idx;
        return;
    }    
    for(int i=st+1; i<empty_place.size(); ++i){
        if(i <= st) continue;
        st = i;
        s[k] = i;
        make_cases(k+1, st);
    }
}
void start_case(int c_idx){
    int new_wall_idx;
    pair<int,int> new_wall;
    for(int i=0; i<3; ++i){
        new_wall_idx = cases[c_idx][i];
        new_wall = empty_place[new_wall_idx];
        board[new_wall.Y][new_wall.X] = 1; // 벽 세우기
    }
}
void end_case(int c_idx){
    int new_wall_idx;
    pair<int,int> new_wall;
    for(int i=0; i<3; ++i){
        new_wall_idx = cases[c_idx][i];
        new_wall = empty_place[new_wall_idx];
        board[new_wall.Y][new_wall.X] = 0; // 벽 허물기
    }
}
bool oob(int y, int x){return y<0||x<0||y>=n||x>=m;}
int get_safe_area(){
    // reset
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            visit[i][j] = false;
        }
    }

    // bfs
    int safe; // safe area
    int cont = 0; // contaminated area
    queue<pair<int,int>> que;
    pair<int,int> cur;
    for(int i=0; i<virus.size(); ++i){
        cur = virus[i];
        que.push(cur);
    }
    while(que.size()){
        cur = que.front(); que.pop();
        if(visit[cur.Y][cur.X]) continue;
        visit[cur.Y][cur.X] = true;
        ++cont;
        for(int d=0; d<4; ++d){
            int ny = cur.Y + dy[d];
            int nx = cur.X + dx[d];
            if(oob(ny, nx)) continue;
            if(visit[ny][nx]) continue;
            if(board[ny][nx] >= 1) continue; // wall or starting point of virus
            que.push({ny,nx});
            
        }
    }
    safe = expandable - cont;
    return safe;
}

void debug(int mod = 0){
    if(mod){
    printf("\n\n--visit--\n");
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            if(board[i][j] >= 1) visit[i][j] =true;
            printf("%d ", visit[i][j]);
        }printf("\n");
    }
    return;
    }
    printf("\n\n--debug--\n");
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            printf("%d ", board[i][j]);
        }printf("\n");
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int res = 0;
    input();
    make_cases(0, -1);

    for(int c_idx=0; c_idx<num_cases; ++c_idx){
        start_case(c_idx);
        int cur_safe = get_safe_area();   
        if(res < cur_safe) res = cur_safe; 
        end_case(c_idx);
    }
    cout << res;
}