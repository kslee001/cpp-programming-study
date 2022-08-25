// https://www.acmicpc.net/problem/1067 이동 FFT
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
const double PI = acos(-1);
typedef complex<double> cpx;

void FFT(vector<cpx> &v, cpx w) {
	// size
    int n = v.size();
    // base case
	if(n == 1) return;
    // even - odd separation
	vector<cpx> even(n/2), odd(n/2);
    for(int i=0; i<n; i++){
        if(i % 2 == 0) even[i/2] = v[i];
        else odd[i/2] = v[i];
    }
	// divide and conquer
    FFT(even, w*w);
    FFT(odd, w*w);
    cpx z(1, 0);

    for(int i=0; i<n/2; i++){
        v[i] = even[i] + z*odd[i];
        v[i + n/2] = even[i] - z*odd[i];
        z *= w;
    }
}

vector<int> output;
void multiply(vector<int> v, vector<int> u) {
    // find max size ( 2*n -1, 2^n format)
	int n = 1;
    while(n <= v.size() || n <= u.size()) n *= 2;
    n *= 2;
	// resize vectors
    v.resize(n); u.resize(n);
    vector<cpx> v_(n), u_(n);
	// generate complex vectors
    for(int i=0; i<n; i++) {
        v_[i] = cpx(v[i], 0);
        u_[i] = cpx(u[i], 0);
    }
	// get DFT values v and u
    cpx unit(cos(2*PI/n), sin(2*PI/n));
    FFT(v_, unit);
    FFT(u_, unit);

	// get DFT values of output
    vector<cpx> w_(n);
    for(int i=0; i<n; i++) w_[i] = v_[i] * u_[i];
    FFT(w_, cpx(1, 0)/unit);

	// get real values of output
    for(int i=0; i<n; i++) w_[i] /= cpx(n, 0);
    for(int i=0; i<output.size(); i++) output[i] = round(w_[i].real());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
	int n; cin >> n;
    vector<int> v(2*n), u(n);
	// all possible overapping areas : 1 2 3 4 1 2 3 4
		// 1 2 3 4 , 2 3 4 1, 3 4 1 2, 1 2 3 4 
	for(int i=0; i<n; ++i){
		cin >> v[i];
		v[i+n] = v[i];
	}
	for(int i=0; i<n; ++i)
		cin >> u[i];
	reverse(u.begin(), u.end()); // reverse filter
	

    output.resize(v.size() + u.size() -1);
	multiply(v, u);
	cout << *max_element(output.begin(), output.end());

}