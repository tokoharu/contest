class UnionFind {
 public:
  vector<int> parent;
  vector<LL> cnt;
  UnionFind(int n) {
    parent = vector<int>(n);
    cnt = vector<LL>(n, 1);
    for (int i = 0; i < n; i++) parent[i] = i;
  }
  int find(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find(parent[v]);
  }

  int uni(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    parent[u] = v;
    cnt[v] += cnt[u];
    return true;
  }
};