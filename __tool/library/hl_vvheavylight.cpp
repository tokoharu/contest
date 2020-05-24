struct HLDecomposition {
  int n, pos;
  vector<vector<int> > G;
  vector<int> vid, head, sub, hvy, par, dep, inv, type;

  HLDecomposition() {}
  HLDecomposition(int sz)
      : n(sz),
        pos(0),
        G(n),
        vid(n, -1),
        head(n),
        sub(n, 1),
        hvy(n, -1),
        par(n),
        dep(n),
        inv(n),
        type(n) {}

  void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }

  void build(vector<int> rs = vector<int>(1, 0)) {
    int c = 0;
    for (int r : rs) {
      dfs(r);
      bfs(r, c++);
    }
  }

  void dfs(int rt) {
    using T = pair<int, int>;
    stack<T> st;
    par[rt] = -1;
    dep[rt] = 0;
    st.emplace(rt, 0);
    while (!st.empty()) {
      int v = st.top().first;
      int& i = st.top().second;
      if (i < (int)G[v].size()) {
        int u = G[v][i++];
        if (u == par[v]) continue;
        par[u] = v;
        dep[u] = dep[v] + 1;
        st.emplace(u, 0);
      } else {
        st.pop();
        int res = 0;
        for (int u : G[v]) {
          if (u == par[v]) continue;
          sub[v] += sub[u];
          if (res < sub[u]) res = sub[u], hvy[v] = u;
        }
      }
    }
  }

  void bfs(int r, int c) {
    int& k = pos;
    queue<int> q({r});
    while (!q.empty()) {
      int h = q.front();
      q.pop();
      for (int i = h; i != -1; i = hvy[i]) {
        type[i] = c;
        vid[i] = k++;
        inv[vid[i]] = i;
        head[i] = h;
        for (int j : G[i])
          if (j != par[i] && j != hvy[i]) q.push(j);
      }
    }
  }

  // for_each(vertex)
  // [l,r] <- attention!!
  void for_each(int u, int v, const function<void(int, int)>& f) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      f(max(vid[head[v]], vid[u]), vid[v]);
      if (head[u] != head[v])
        v = par[head[v]];
      else
        break;
    }
  }

  // for_each(edge)
  // [l,r] <- attention!!
  void for_each_edge(int u, int v, const function<void(int, int)>& f) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      if (head[u] != head[v]) {
        f(vid[head[v]], vid[v]);
        v = par[head[v]];
      } else {
        if (u != v) f(vid[u] + 1, vid[v]);
        break;
      }
    }
  }

  int lca(int u, int v) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      if (head[u] == head[v]) return u;
      v = par[head[v]];
    }
  }

  int distance(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
};