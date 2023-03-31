#include <iostream>
#include <vector>
#include <queue>
#define Y first
#define X second
using namespace std;

int n,m,p;
char board[1000][1000];
int  max_step[9];
int  visit[1000][1000];
int  dy[4] = {1,0,-1,0};
int  dx[4] = {0,1,0,-1};
int score_arr[9];
vector<pair<int,int>> pos[9]; // strorage for positions : player 0 to 8
queue<pair<int,int>> expand_targets;   // storage for next positions

void init(){
    cin>>n>>m>>p;
    for(int i=0; i<p; ++i){
        cin >>max_step[i]; // max step for i-th player
    }
    char c;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cin >> c;
            board[i][j] = c;
            if((int) board[i][j]-49 >= 0 && (int) board[i][j]-49 <=9){
                pos[(int) board[i][j]-49].push_back({i,j}); // save initial positions of players
                ++score_arr[(int) board[i][j]-49];
            }
        }
    }
}

void DEBUG(){
    printf("\n\n--debug--\n");
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            printf("%c ", board[i][j]);
        }printf("\n");
    }
}


bool oob(int y, int x){return y<0||x<0||y>=n||x>=m;}
bool turn(int player){

    bool flag = false; // expanded?

    // initialize p-player's turn 
    int step = max_step[player];
    queue<pair<int,int>> que;
    for(int i=0; i<pos[player].size(); ++i){
        que.push(pos[player][i]);
        visit[pos[player][i].Y][pos[player][i].X] = 1;
    }
    pos[player].clear();

    // bfs
    pair<int,int> cur;
    while(que.size()){
        cur = que.front(); que.pop();
        if(visit[cur.Y][cur.X] == step+1){
            pos[player].push_back({cur.Y, cur.X}); // nextpos  (중복 가능)
            visit[cur.Y][cur.X] = 0;
            continue;
        }
        for(int d=0; d<4; ++d){
            int ny = cur.Y+dy[d];
            int nx = cur.X+dx[d];
            if(oob(ny,nx)) continue;
            if(visit[ny][nx]) continue;
            // 같은 컬러이거나 '.' 인경우
            if( (int) board[ny][nx]-49 == player || board[ny][nx] == '.'){
                visit[ny][nx] = visit[cur.Y][cur.X] + 1;
                que.push({ny,nx});
                expand_targets.push({ny,nx});  // 색칠할 영역
            }
        }
    }

    // coloring
    while(expand_targets.size()){
        cur = expand_targets.front(); expand_targets.pop();
        char c = (char) player+49;
        if(board[cur.Y][cur.X] != c){
            board[cur.Y][cur.X] = c; // coloring
            ++score_arr[player];
            flag = true;
        }
    }
    return flag;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int cur = 0;
    while(true){
        cur = 0;
        for(int i=0; i<p; ++i){
            cur += pos[i].size();
        }
        if(!cur) break;
        for(int player=0; player<p; ++player){
            turn(player);
        }
    }
    for(int player=0;player<p; ++player){
        cout << score_arr[player] << " ";
    }
    

}