auto dfs_func = [&](int root) {
  // Graph : g

  vector<int> used(g.N, 0);
  stack<int> sta;
  sta.push(root);
  while (!sta.empty()) {
    int v = sta.top();
    sta.pop();
    used[v] = true;
    for (auto edge : g.vs[v].es) {
      int u = edge.to;
      // int w = edge.field; // OPTION
      if (used[u]) continue;
      // FROM HERE

      // TO HERE
      sta.push(u);
    }
  }
};
dfs_func(0);