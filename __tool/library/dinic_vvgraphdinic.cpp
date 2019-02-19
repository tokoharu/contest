// #include <bits/stdc++.h>
// using namespace std;

template <typename T>
class Edge {
 public:
  int to;
  T cap;
  int rev;
  Edge(int to, T cap, int rev) {
    this->to = to;
    this->cap = cap;
    this->rev = rev;
  }
};
template <typename T>
class Graph {
 private:
  T inf;
  vector<vector<Edge<T>>> G;
  vector<int> level;
  vector<int> iter;
  int N;  // node

 public:
  explicit Graph(int n) {
    inf = (int)1e8;  //
    N = n;
    level.resize(N);
    G.resize(N);
    iter.resize(N);
  }

  void add_edge(int from, int to, T cap) {
    Edge<T> a(to, cap, G[to].size());
    Edge<T> b(from, 0, G[from].size() - 1);
    G[from].push_back(a);
    G[to].push_back(b);
  }
  void bfs(int s) {
    for (int a = 0; a < N; a++) level[a] = -1;
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (int i = 0; i < G[v].size(); i++) {
        Edge<T> &e = G[v][i];
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          que.push(e.to);
        }
      }
    }
  }

  T dfs(int v, int t, T f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
      Edge<T> &e = G[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
        int d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  T max_flow(int s, int t) {
    T flow = 0;

    for (;;) {
      bfs(s);
      if (level[t] < 0) return flow;
      for (int a = 0; a < N; a++) iter[a] = 0;
      T f;
      while ((f = dfs(s, t, inf)) > 0) {
        flow += f;
      }
    }
  }

  // traverseも追加
  void traverse(int s, vector<int> &vis) {
    vis.resize(N);
    for (int i = 0; i < N; i++) vis[i] = 0;
    vis[s] = 1;
    queue<int> qu;
    qu.push(s);
    while (!qu.empty()) {
      int v = qu.front();
      qu.pop();
      for (int i = 0; i < G[v].size(); i++) {
        int u = G[v][i].to;
        int c = G[v][i].cap;
        if (c != 0 && vis[u] == 0) {
          vis[u] = 1;
          qu.push(u);
        }
      }
    }
  }
};
// int main() {
//  Graph<int> graph(10);
//  Graph<long long> hoge(20);
//  graph.add_edge(1, 2, 3);
//  graph.add_edge(2, 4, 5);
//  cout << graph.max_flow(1, 4) << endl;
//  return 0;/
//}