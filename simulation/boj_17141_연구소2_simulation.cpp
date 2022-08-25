#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

#define Y first
#define X second

int n,m;
int area;
int num_wall;
int expandable;
int num_cases;
int num_virus;

int room[50][50];
int visit[50][50];
int cases[252][11]; // max number of cases = 252 ( = 10 C 5)
int s[11];
int res[252];

int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};
vector<pair<int,int>> virus;
vector<pair<int,int>> cur_virus;

void debug();
int init(){
    cin >>n>>m;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cin >>room[i][j];
            if(room[i][j] == 2) virus.push_back({i,j});
            if(room[i][j] == 1) ++num_wall;
        }
    }
    area = n*n;
    expandable = area - num_wall;
    num_virus = virus.size();
    
    
    // get the output of combination(num_virus, m)
    int up = 1;
    for(int i=0; i<m; ++i){ up *= (num_virus - i);}
    int down = 1;
    for(int i=0; i<m; ++i){ down*= m-i; }
    num_cases = up/down; 
    return virus.size();
}

int __idx = -1;
void make_cases(int k=0, int st=-1){
    if(k == m){
        ++__idx;
        for(int i=0; i<m; ++i){
            cases[__idx][i] = s[i]; // store index of the virus
        }
    }
    for(int i=st+1; i<num_virus; ++i){
        if(i<st) continue;
        st = i;
        s[k] = i;
        make_cases(k+1, st);
    }
}
void reset(){ for(int i=0; i<n; ++i){for(int j=0; j<n; ++j){visit[i][j] = 0;}}}
bool oob(int y, int x){return y<0||x<0||y>=n||x>=n;}

void start_case(int c_idx){
    for(int i=0; i<m; ++i){
        int cur_idx = cases[c_idx][i];
        cur_virus.push_back(virus[cur_idx]);
    }
}

void end_case(){
    cur_virus.clear();
}

int get_time(){
    int time = 0;
    int expanded = 0;
    pair<int,int> cur;
    queue<pair<int,int>> que;
    for(int i=0; i<m; ++i){
        cur = cur_virus[i];    
        que.push(cur);
        ++expanded;
        visit[cur.Y][cur.X] = 1;

    }
    while(que.size()){
        cur = que.front(); que.pop();
        if(time < visit[cur.Y][cur.X]) time = visit[cur.Y][cur.X];
        for(int d=0; d<4; ++d){
            int ny = cur.Y+dy[d];
            int nx = cur.X+dx[d];
            if(oob(ny,nx)) continue;        // oob
            if(room[ny][nx] == 1) continue; // wall
            if(visit[ny][nx]) continue;     // visited
            visit[ny][nx] = visit[cur.Y][cur.X] + 1;
            que.push({ny,nx});
            ++expanded;
        }
    }    
    reset(); // reset visit array
    if(expanded != expandable) return INT_MAX; // confined
    return time-1;
}
void debug(){
    cout << "\n\n--debug\n";
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            cout << visit[i][j] << " ";
        }
        cout <<"\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int num_virus = init();
    make_cases();

    for(int c_idx = 0; c_idx<num_cases; ++c_idx){
        start_case(c_idx);
        res[c_idx] = get_time();
        end_case();
    }

    int res_val = INT_MAX;
    for(int i=0; i<num_cases; ++i){
        int cur = res[i];
        if(res_val > cur) res_val = cur;
    }

    if(res_val == INT_MAX){
        cout << -1; 
        return 0;
    }
    cout << res_val;

}


