#include <bits/stdc++.h>
using namespace std;


#define Y first
#define X second

int n;
int board[100][100];
int visited[100][100];
int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

void input(){scanf("%d", &n); for(int i=0; i<n; ++i){for(int j=0; j<n; ++j){scanf("%d", &board[i][j]);}}}
void reset(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            visited[i][j] = 0;
        }
    }
}
bool oob(int y, int x){return y<0 || y>=n || x<0 || x>=n;}
void color_islands(){     // DFS
    stack<pair<int,int>> land;
    pair<int,int> cur;
    int color = 1;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            //dfs : land
            if(board[i][j] && !visited[i][j]){
                land.push({i,j});
                visited[i][j] = 1;
                while(land.size()){
                    cur = land.top(); land.pop();
                    int ny, nx;
                    board[cur.Y][cur.X] = color;
                    visited[cur.Y][cur.X] = 1;
                    for(int d=0; d<4; ++d){
                        ny = cur.Y + dy[d];
                        nx = cur.X + dx[d];
                        if(oob(ny, nx)) continue;
                        if(visited[ny][nx])  continue;
                        if(!board[ny][nx]) continue;
                        land.push({ny,nx});
                    }
                }
                ++color;
            }
        }
    }
}
vector <pair<int,int>> target_coord;
vector <int>           target_color;
void search_targets(){        // BFS
    reset();
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            int cur_color = board[i][j];
            if(!cur_color) continue;
            for(int d=0; d<4; ++d){
                int ny = i+dy[d];
                int nx = j+dx[d];
                if(oob(ny,nx)) continue;
                int adj_color = board[ny][nx];
                if(adj_color == 0){
                    target_coord.push_back({i,j});
                    target_color.push_back(cur_color);
                    break;
                }
            }
        }
    }
}


int bfs(pair<int,int> input_coord, int input_color){
    reset();
    queue<pair<int,int>> que;
    que.push(input_coord);
    visited[input_coord.Y][input_coord.X] = 1;
    pair<int,int> cur;

    while(!que.empty()){
        cur = que.front(); que.pop();
        for(int d=0; d<4; ++d){
            int ny = cur.Y + dy[d];
            int nx = cur.X + dx[d];
            if(oob(ny,nx)) continue;
            if(visited[ny][nx]) continue;
            if(board[ny][nx] == input_color) continue;
            if(board[ny][nx]) return visited[cur.Y][cur.X] - 1;
            visited[ny][nx] = visited[cur.Y][cur.X] + 1;
            que.push({ny,nx});
        }
    }
    return INT_MAX;    
}


int main(){
    input();
    color_islands();
    search_targets();
    int res = INT_MAX;
    for(int idx = 0; idx<target_coord.size(); ++idx){
        int cur = bfs(target_coord[idx], target_color[idx]);
        // printf("(%d, %d) : %d\n", target_coord[idx].Y, target_coord[idx].X, cur);
        if(res > cur){
            res = cur;
        }
    }
    if(res == INT_MAX) printf("%d", -1);
    else printf("%d", res);
}