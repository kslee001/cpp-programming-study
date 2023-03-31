// https://www.acmicpc.net/problem/10531 Golf Bot , FFT
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <complex>
#include <climits>

using namespace std;
using cpx = complex<double>;
using lint = long long;
const double PI = acos(-1);

void FFT(vector<cpx>&v, cpx w){
    int n = v.size();
    if(n == 1) return;
    
    vector<cpx> even(n/2), odd(n/2);
    for(int i=0; i<n; ++i){
        if(i%2) odd[i/2] = v[i];
        else   even[i/2] = v[i];
    }

    FFT(odd, w*w);
    FFT(even, w*w);
    cpx z(1,0);

    for(int i=0; i<n/2; ++i){
        v[i]     = even[i] + z*odd[i];
        v[i+n/2] = even[i] - z*odd[i];
        z*=w; 
    }
}

vector<int> output;
void mul(vector<int> a, vector<int> b){
    int n =1;
    while(n <= a.size() && n <= b.size() ) n*=2;
    n*=2;
    a.resize(n); b.resize(n);
    output.resize(n);

    vector<cpx> a_(n), b_(n);
    for(int i=0; i<n; ++i){
        a_[i] = cpx(a[i], 0);
        b_[i] = cpx(b[i], 0);
    }

    cpx unit(cos(2*PI/n), sin(2*PI/n));
    FFT(a_, unit);
    FFT(b_, unit);

    vector<cpx> output_(n); 
    for(int i=0; i<n; ++i){
        output_[i] = a_[i]*b_[i];
    }
    FFT(output_, cpx(1,0)/unit);
    for(int i=0; i<n; ++i){
        output_[i] /= cpx(n,0);
    }
    for(int i=0; i<n; ++i){
        output[i] = round(output_[i].real());
    }
}


vector<int> bot(200001);
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int res = 0;
    int input;
    
    int n;    
    // reduce overhead
    int maxval = INT_MIN;
    cin >>n;
    for(int i=0; i<n; ++i){
        cin >>input;
        bot[input] = 1;
        if(input > maxval) maxval = input;
    }
    bot[0] = 1;
    // reduce overhead
    bot.resize(maxval+1);
    mul(bot, bot);

    int m;
    cin >>m;
    for(int i=0; i<m; ++i){
        cin >>input;
        // some inputs are too faraway from the distance 
        // that golfbot can send a ball
        if(input < output.size() && output[input]) 
            ++res;
    }

    cout << res;
}