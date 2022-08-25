// https://www.acmicpc.net/problem/15576 큰 수 곱셈(2) FFT (platinum 1)
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
const double PI = acos(-1);
typedef complex<double> cpx;
typedef long long lint;

void FFT(vector<cpx> &v, cpx w) {
	// size
    lint n = v.size();
    // base case
	if(n == 1) return;
    // even - odd separation
	vector<cpx> even(n/2), odd(n/2);
    for(lint i=0; i<n; i++){
        if(i % 2 == 0) even[i/2] = v[i];
        else odd[i/2] = v[i];
    }
	// divide and conquer
    FFT(even, w*w);
    FFT(odd, w*w);
    cpx z(1, 0);

    for(lint i=0; i<n/2; i++){
        v[i] = even[i] + z*odd[i];
        v[i + n/2] = even[i] - z*odd[i];
        z *= w;
    }
}

vector<lint> output;
void multiply(vector<int> v, vector<int> u) {
    // find max size ( 2*n -1, 2^n format)
	lint n = 1;
    while(n <= v.size() || n <= u.size()) n *= 2;
    n *= 2;
	// resize vectors
    v.resize(n); u.resize(n);
    vector<cpx> v_(n), u_(n);
	// generate complex vectors
    for(lint i=0; i<n; i++) {
        v_[i] = cpx(v[i], 0);
        u_[i] = cpx(u[i], 0);
    }
	// get DFT values v and u
    cpx unit(cos(2*PI/n), sin(2*PI/n));
    FFT(v_, unit);
    FFT(u_, unit);

	// get DFT values of output
    vector<cpx> w_(n);
    for(lint i=0; i<n; i++) w_[i] = v_[i] * u_[i];
    FFT(w_, cpx(1, 0)/unit);

	// get real values of output
    for(lint i=0; i<n; i++) w_[i] /= cpx(n, 0);
    for(lint i=0; i<output.size(); i++) output[i] = round(w_[i].real());
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string n1,n2; cin >> n1>>n2;
    vector<int> num1;
    vector<int> num2;

    stringstream s1(n1);
    stringstream s2(n2);
    char c;
    while(s1 >>c)
        num1.push_back((int)c - 48);
    while(s2 >> c)
        num2.push_back((int)c - 48);

    lint new_size = 1LL*(num1.size()+num2.size() -1);
    output.resize(new_size);
    multiply(num1, num2);

    lint res[new_size];

    lint C[new_size];
    for(lint i=0; i<new_size; ++i) C[i] = output[i];

    lint carry = 0;
    for(lint i=new_size-1; i>=0; --i){
        carry = C[i] / 10;
        C[i - 1] += carry;
        C[i] = C[i] % 10;
    }
    if(carry) cout<< carry;
    int cnt = new_size-1;
    while (C[cnt] == 0) {
        cnt--;
        if (cnt == 0) break;
    }
    for (lint i=0; i<new_size; ++i) cout << C[i];
}