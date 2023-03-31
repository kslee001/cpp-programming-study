#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
using namespace std;
using pii = pair<int,int>;
#define Y first
#define X second

int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

using namespace std;


int n,m;
int board[10][10];
int visit[10][10];
int path[6][6];
vector<pii> starting;
int num_islands;

void init(){
    cin >>n>>m; 
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cin >>board[i][j];
        }
    }
    for(int i=0; i<6; ++i){
        for(int j=0; j<6; ++j){
            path[i][j] = INT_MAX;
        }
    }
}
void debug(){
    printf("\n\n--board--\n");
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            printf("%d ", board[i][j]);
        }printf("\n");
    }
    printf("\n--path dist--\n");
    for(int i=0; i<num_islands; ++i){
        for(int j=0; j<num_islands; ++j){
            if(path[i][j] == INT_MAX) printf("0 ");
            else printf("%d ", path[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void debug_set(set<int>);

bool oob(int y, int x){return y<0||y>=n||x<0||x>=m;}
void reset(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            visit[i][j] = 0;
        }
    }
}

int color_islands(){
    pii cur;
    stack<pii> stk;
    int color = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            if(!board[i][j]) continue; // water
            if(visit[i][j]) continue; // visited
            stk.push({i,j});
            ++color;
            while(stk.size()){
                cur = stk.top(); stk.pop();
                if(visit[cur.Y][cur.X]) continue;
                board[cur.Y][cur.X] = color; // coloring
                visit[cur.Y][cur.X] = 1;
                for(int d=0; d<4; ++d){
                    int ny = cur.Y + dy[d];
                    int nx = cur.X + dx[d];
                    if(oob(ny,nx)) continue;
                    if(!board[ny][nx]) continue; //water
                    stk.push({ny,nx});
                }
            }
        }
    }
    reset();
    return color;
}

void find_startings(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            if(visit[i][j]) continue;
            if(!board[i][j]) continue;
            for(int d=0; d<4; ++d){
                int ny = i+dy[d];
                int nx = j+dx[d];
                if(oob(ny,nx)) continue;
                if(board[ny][nx]) continue;
                starting.push_back({i,j});
                break;
            }
        }
    }
    reset();
}

void update_path(pii cur){
    int source_color = board[cur.Y][cur.X];
    int target_color;
    for(int d=0; d<4; ++d){
        int ny = cur.Y+dy[d];
        int nx = cur.X+dx[d];
        if(oob(ny,nx)) continue;
        if(board[ny][nx]) continue;

        int dist = 0;
        bool flag = false;        
        while(true){
            ny += dy[d];
            nx += dx[d];
            ++dist;
            if(oob(ny,nx)) break;
            if(board[ny][nx] == source_color) break;
            if(board[ny][nx]){
                flag = true; // found new island
                target_color = board[ny][nx];
                break;
            }
        }
        if(dist <2) continue;
        if(flag && path[source_color-1][target_color-1] > dist)
            path[source_color-1][target_color-1] = dist; // 업데이트
    }
}

set<int> S[7];
struct edge{
    int start;
    int end;
    int val;
    edge(){}; 
    edge(int s, int e, int v){
        start = s; end = e; val = v;
    };
};
bool operator<(edge e1, edge e2){
    return e1.val > e2.val;
}

void make_edges(priority_queue<edge> &edges){
    for(int i=0; i<num_islands; ++i){
        for(int j=i+1; j<num_islands; ++j){
            if(path[i][j] != INT_MAX)
            // printf("edge made : (%d, %d), %d\n", 1+i, 1+j, path[i][j]);
            edges.push(edge(i+1, j+1, path[i][j])); // start, end, value
        }
    }
}

bool check_set(set<int> S_from, int to){
    return S_from.find(to) != S_from.end();
}

set<int> set_merge_aux(set<int> S1, set<int> S2){
    set<int> merged;
    set<int>::iterator iter;
    for(iter = S1.begin(); iter != S1.end(); ++iter){
        merged.insert(*iter);
    }
    for(iter = S2.begin(); iter != S2.end(); ++iter){
        merged.insert(*iter);
    }
    return merged;
}

void set_update_aux(set<int> S_input, set<int> merged){
    int arr[num_islands+1];
    set<int>::iterator iter;
    int idx = -1;
    for(iter = S_input.begin(); iter!= S_input.end(); ++iter){
        idx++;
        arr[idx] = *iter;
    }
    for(int i=0; i<=idx; ++i){
        S[arr[i]] = merged;
    }
}
void set_merge(set<int> S1, set<int> S2){
    set<int> merged = set_merge_aux(S1, S2);
    set_update_aux(S1, merged);
    set_update_aux(S2, merged);
}

void debug_set(set<int> S){
    printf("\n");
    set<int>::iterator iter;
    for(iter = S.begin(); iter!= S.end(); ++iter){
        printf("%d ", *iter);
    }
    printf("\n");
}
void debug_set(set<edge> S){
    printf("\n");
    set<edge>::iterator iter;
    for(iter = S.begin(); iter!= S.end(); ++iter){
        printf("%d , %d", iter->start, iter->end);
    }
    printf("\n");
}
int kruskal(){
    int res = 0;
    set<edge> MST;
    // init
    
    for(int i=1; i<=num_islands; ++i){
        S[i].insert(i);
    }
    priority_queue<edge> edges;
    make_edges(edges);

    edge cur;
    while(edges.size()){
        cur = edges.top(); edges.pop();
        int from = cur.start;
        int to   = cur.end;
        int val  = cur.val;
        int temp[6];
        // printf("(%d, %d) are selected, val : %d\n", from, to, val);
        // debug_set(S[from]); printf("\n");
        // debug_set(S[to]); printf("\n");
        // same group
        if(check_set(S[from], to)|| check_set(S[to], from)) {
            // printf(" -- %d, %d are in the same group !\n", from, to);
            set_merge(S[from], S[to]);
            continue;
        } 
        // not in the same group
        set_merge(S[from], S[to]);
        res += val;
        MST.insert(cur);
        // printf(" -- %d, %d : linked and merged !\n", from, to);
    }
    
    set<int> checker = S[1];
    // for(int i=1; i<=num_islands; ++i){
    //     printf("group[%d] : ", i);
    //     debug_set(S[i]);
    // }
    for(int i=1; i<=num_islands; ++i){
        if(checker != S[i]) return -1;
    }

    return res;
}


int main(){
    init();
    num_islands = color_islands();
    find_startings();
    for(int i=0; i<starting.size(); ++i){
        update_path(starting[i]);
    }
    // debug();
    int res = kruskal();
    if(res == 0 || res == INT_MAX) res = -1;
    printf("%d", res);


}