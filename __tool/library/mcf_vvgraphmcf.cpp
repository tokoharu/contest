#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
struct edge {
  int to, cap, cost, rev;
};

class Graph {
 private:
  vector<vector<edge>> G;
  vector<int> h;
  vector<int> dist;
  vector<int> prevv;
  vector<int> preve;
  int N;
  int INF = 1000000;

 public:
  Graph(int n) {
    N = n;

    G.resize(N);
    h.resize(N);
    dist.resize(N);
    prevv.resize(N);
    preve.resize(N);
  }

  void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back((edge){to, cap, cost, G[to].size()});
    G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
  }

  int min_cost_flow(int s, int t, int f) {
    int res = 0;
    for (int i = 0; i < N; i++) h[i] = 0;

    while (f > 0) {
      priority_queue<PII, vector<PII>, greater<PII>> que;
      for (int i = 0; i < N; i++) dist[i] = INF;
      dist[s] = 0;
      que.push(PII(0, s));
      while (!que.empty()) {
        PII p = que.top();
        que.pop();

        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i = 0; i < G[v].size(); i++) {
          edge &e = G[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            que.push(PII(dist[e.to], e.to));
          }
        }
      }

      if (dist[t] == INF) {
        return -1;
      }

      for (int v = 0; v < N; v++) h[v] += dist[v];

      int d = f;
      for (int v = t; v != s; v = prevv[v]) {
        d = min(d, G[prevv[v]][preve[v]].cap);
      }

      f -= d;
      res += d * h[t];
      for (int v = t; v != s; v = prevv[v]) {
        edge &e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }

    return res;
  }
};
/*
int main() {
  Graph graph(6);
  graph.add_edge(1, 2, 3, 4);
  graph.add_edge(2, 4, 4, 2);
  cout << graph.min_cost_flow(1, 4, 2) << endl;
}
*/
