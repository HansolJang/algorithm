//https://www.acmicpc.net/problem/1162
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define SIZE 10001
int inf = 1000000000;
struct Edge {
	int to;
	int cost;
	Edge(int to, int cost) : to(to), cost(cost) {
	}
};
//큐의 원소가 되는 구조체: 현재의 거리, 정점, 포장회수를 저장
struct Cur {
	int d;
	int vertex;
	int wrap_cnt;
	bool operator > (const Cur& c) const { return d > c.d; } 
	Cur(int d, int vertex, int wrap_cnt) : d(d), vertex(vertex), wrap_cnt(wrap_cnt) {
	}
};
vector<Edge> city[SIZE];
bool check[SIZE][21];
int dist[SIZE];
int n, m, k, s, e, w, flen, nv, t;
int main() {
	memset(check, 0, sizeof(check));
	for(int i=0; i<SIZE; i++)
		dist[i] = inf;
	scanf("%d %d %d", &n, &m, &k);
	for(int i=0; i<m; i++) {
		scanf("%d %d %d", &s, &e, &w);
		city[s].push_back(Edge(e, w));
		city[e].push_back(Edge(s, w));
	}
	priority_queue<Cur, vector<Cur>, greater<Cur> > q;
	//시작점 = 1(서울)
	dist[1] = 0;
	q.push(Cur(dist[1], 1, 0));
	while(!q.empty()) {
		Cur f = q.top();
		q.pop();
		if(check[f.vertex][f.wrap_cnt]) continue;
		else check[f.vertex][f.wrap_cnt] = true;
		flen = city[f.vertex].size();
		for(int i=0; i<flen; i++) {
			nv = city[f.vertex][i].to;
			//t = 그대로 지나가는 비용
			t = f.d + city[f.vertex][i].cost;
			if(!check[nv][f.wrap_cnt])
				q.push(Cur(t, nv, f.wrap_cnt));
			//포장이 가능할 경우 포장
			if(f.wrap_cnt < k && !check[nv][f.wrap_cnt + 1]) {
				q.push(Cur(f.d, nv, f.wrap_cnt + 1));
				t = min(t, f.d);
			}
			//모든 경우 중 최소값을 dist 배열에 저장
			dist[nv] = min(dist[nv], t);
		}
	}
	printf("%d\n", dist[n]);
	return 0;
}