#include <iostream>
#include <stack>
using namespace std;

int main(){
    int n; cin >>n;
            // first : 값, second : 중복개수
    stack <pair<int,int>> stk;
    long long res = 0;
    int cur;
    for(int i=0; i<n; ++i){
        cin >> cur;
        int cnt = 1; // 중복 개수
        // top (마지막) value보다 입력값이 크거나 같은경우
        while(stk.size() && stk.top().first <= cur){
            res += stk.top().second; // 맨 위에놈 중복값 res에 더하고
            // 만약 cur랑 top이 같으면 중복값 업데이트하고 (이따 넣을거임)
            if(stk.top().first == cur) cnt += stk.top().second;
            stk.pop(); // 맨 위엣놈 빼버림
        }
        if(stk.size()) ++res; 
        stk.push({cur, cnt});
    }
    cout << res;
}
