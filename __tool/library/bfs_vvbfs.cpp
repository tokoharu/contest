auto bfs_func = [&](int root) {
  // graph : g

  vector<int> used(g.N, 0);
  queue<int> qu;
  qu.push(root);
  while (!qu.empty()) {
    int v = qu.front();
    qu.pop();
    used[v] = true;
    for (auto edge : g.vs[v].es) {
      int u = edge.to;
      // int w = edge.field; // OPTION
      if (used[u]) continue;
      // FROM

      // TO
      qu.push(u);
    }
  }
};
bfs_func(0);