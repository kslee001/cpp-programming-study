// https://www.acmicpc.net/problem/1922 네트워크 연결
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge{
	int start;
	int end;
	int dist;
	edge(int a, int b, int c){start = a; end = b; dist = c;};
	bool operator<(const edge e){
		return dist < e.dist;
	}
};

int num_v, num_e;
int parent[1001];
vector<edge> edges;

void init(){
	cin >>num_v >> num_e;
	for(int i=1; i<=num_v; ++i){
		parent[i] = i; // 자기 자신을 그룹으로 등록
	}
	for(int i=0; i<num_e; ++i){
		int a,b,c; cin>>a>>b>>c;
		edges.push_back(edge(a,b,c)); // edge입력
	}
	sort(edges.begin(), edges.end());
}

int find_group(int v){
	if(parent[v] == v)	return v;
	else                return parent[v] = find_group(parent[v]); // 재귀적으로 탐색 및 할당
}

void group_union(int a, int b){
	parent[find_group(a)] = find_group(b);
}

int main(){
	init();
	long long res = 0;
	for(int i=0; i<num_e; ++i){
		int s_group = find_group(edges[i].start);
		int e_group = find_group(edges[i].end);
		if(s_group != e_group){
			res += edges[i].dist;
			group_union(edges[i].start, edges[i].end); 
		}
	}
	cout << res;
}