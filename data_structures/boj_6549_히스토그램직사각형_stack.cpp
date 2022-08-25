// https://www.acmicpc.net/problem/6549 히스토그램에서 가장 큰 직사각형 stack

#include <iostream>
#include <stack>
using namespace std;
using lint = long long;

stack<int> stk;
lint arr[100001];
lint res;
int n;

bool init(){
    res = 0;
    cin >>n;
    if(n == 0) return false;
    for(int i=0; i<n; ++i){
        cin >>arr[i];
    }
    // arr[n] = 0;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(init()){
        for(int i=0; i<n; ++i){
            while(stk.size() && arr[stk.top()] > arr[i]){
                int height = arr[stk.top()];
                stk.pop();
                int width = i;
                if(stk.size())
                    width = i - stk.top() - 1;
                lint area = 1LL * height * width;
                if(area > res) res = area;
            }
            stk.push(i);
        }


        while(stk.size()){
            int height = arr[stk.top()];
            stk.pop();
            int width = n; // last idx
            if(stk.size())
                width = n - stk.top() - 1;
            lint area = 1LL * height * width;
            if(area > res) res = area;
        }
        cout << res << "\n";
    }
}