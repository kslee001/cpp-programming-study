#include <bits/stdc++.h>
using namespace std;

int board[1000][1000];
int svisit[1000][1000];
int fvisit[1000][1000];
int c; 
int n,m;


bool bound(int y, int x)   { return y == 0 || y == n-1 || x == 0 || x == m-1 ;}

bool oob    (int y, int x) { return y < 0 || y>=n || x<0 || x>=m ;}
bool is_wall(int y, int x) { return board[y][x] == 1;}
bool fire_arrived(int y, int x, int cur_turn){
    return fvisit[y][x] <= cur_turn+1;
}


int main(){
    cin >>c;

    int dy[4] = {1,0,-1,0};
    int dx[4] = {0,1,0,-1};

    queue<pair<int,int>> fq;
    queue<pair<int,int>> sq;


    for(int _ = 0; _<c; ++_){
        // queue initialization 
        while(!fq.empty()) fq.pop();    
        while(!sq.empty()) sq.pop();

        // input & init visit map
        cin >> m >> n; // w 먼저 입력
        char input;
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                cin >> input;
                fvisit[i][j] = -1;
                svisit[i][j] = -1;
                
                switch(input){
                    case '#':
                        board[i][j] = 1;  // wall = 1
                        break;
                    case '.':
                        board[i][j] = 0;  // empty = 0
                        break;
                    case '*':
                        board[i][j] = 4;  // fire = 4
                        fq.push({i,j});  
                        fvisit[i][j] = 0;
                        break;
                    case '@':
                        board[i][j] = 7;   // 상범 = 7
                        sq.push({i,j});
                        svisit[i][j] = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        // sb check


        // fire bfs
        int cur_turn;
        int y,x;
        int ny, nx;
        pair<int,int> cur;

        while(!fq.empty()){
            cur = fq.front(); fq.pop();
            y = cur.first; x = cur.second;
            cur_turn = fvisit[y][x];

            for(int d=0; d<4; ++d){
                ny = y+dy[d];
                nx = x+dx[d];

                if(oob(ny, nx)) continue;
                if(is_wall(ny, nx))   continue;
                if(fvisit[ny][nx]!= -1) continue;

                fvisit[ny][nx] = cur_turn +1;
                fq.push({ny,nx});
            }
        }

        // sangbum bfs
        bool flag = true;
        while(!sq.empty() && flag){
            cur = sq.front(); sq.pop();
            y = cur.first; x = cur.second;
            cur_turn = svisit[y][x];
            if(bound(y,x)){
                cout << cur_turn + 1<<"\n";
                flag = false;
                break;
            }

            for(int d=0; d<4; ++d){
                ny = y+dy[d];
                nx = x+dx[d];

                if(oob(ny,nx)){
                    cout << cur_turn +1 << "\n";
                    flag = false; 
                    break;
                }
                if(is_wall(ny,nx)) continue;
                if(svisit[ny][nx]!= -1) continue;
                if(fvisit[ny][nx]!= -1 && fire_arrived(ny,nx, cur_turn)) continue;
                svisit[ny][nx] = cur_turn +1;
                sq.push({ny,nx});
            }
        }
        if(flag) cout << "IMPOSSIBLE\n";
    }
}