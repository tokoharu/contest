template <typename TE>
class Edge {
 public:
  int to;
  TE field;
  Edge() {}
  Edge(int t, TE f) : to(t), field(f) {}
};

template <typename TV, typename TE>
class Vertex {
 public:
  int id;
  int depth;
  TV field;
  Edge<TE> parent;
  vector<Edge<TE>> child;
  vector<Edge<TE>> es;
  Vertex() {}
  Vertex(int in) : id(in) {}
};

template <typename TV, typename TE>
class Graph {
 public:
  int root;
  int N;
  vector<Vertex<TV, TE>> vs;
  // vector<vector<Edge>> es;
  Graph(int n) : N(n) {
    for (int i = 0; i < n; i++) {
      vs.push_back(Vertex<TV, TE>(i));
    }
    root = -1;
  }
  // 0-indexed
  void add_edge(int v, int u, TE e, bool directed = false) {
    vs[v].es.push_back(Edge<TE>(u, e));
    if (!directed) {
      vs[u].es.push_back(Edge<TE>(v, e));
    }
  }

  void build_tree(
      int root, function<void(Vertex<TV, TE>&, Vertex<TV, TE>&)> func =
                    [](Vertex<TV, TE>& parent, Vertex<TV, TE>& child) {
                      if (parent.id == -1) {
                        child.depth = 0;
                        return;
                      }
                      child.depth = parent.depth + 1;
                    }) {
    Vertex<TV, TE> dummy(-1);
    this->root = root;
    func(dummy, vs[root]);
    vector<int> used(N);
    stack<int> sta;
    sta.push(root);
    used[root] = true;
    while (!sta.empty()) {
      int v = sta.top();
      sta.pop();
      for (auto e : vs[v].es) {
        int u = e.to;
        if (used[u]) continue;
        used[u] = true;
        vs[u].parent = Edge<TE>(v, e.field);
        vs[v].child.push_back(Edge<TE>(u, e.field));
        func(vs[v], vs[u]);
        sta.push(u);
      }
    }
  }

  vector<LL> dijkstra(int s) {
    LL INF = (1LL << 60);
    priority_queue<PII, vector<PII>, greater<PII>> que;
    vector<LL> d(N, INF);
    d[s] = 0;
    que.push(PII(0, s));
    while (!que.empty()) {
      PII p = que.top();
      que.pop();
      int v = p.second;
      if (d[v] < p.first) continue;

      for (auto e : vs[v].es) {
        if (d[e.to] > d[v] + e.field.cost) {
          d[e.to] = d[v] + e.field.cost;
          que.push(PII(d[e.to], e.to));
        }
      }
    }
    return d;
  }
  /*
  葉からの順番を取得。
  */
  vector<int> get_order() {
    assert(root != -1);
    vector<int> result;
    stack<int> sta;
    sta.push(root);
    while (!sta.empty()) {
      int vid = sta.top();
      sta.pop();
      result.push_back(vid);
      for (auto eu : vs[vid].child) {
        sta.push(eu.to);
      }
    }
    reverse(result.begin(), result.end());
    return result;
  }

  /*
    update : (T parent, vector<T> child, Vertex parent) -> void
  */

  template <typename T>
  vector<T> update_leaf_root(
      function<void(T&, vector<T*>, Vertex<TV, TE>&)> update) {
    vector<int> order = get_order();
    vector<T> table;
    table.resize(N);
    for (auto vid : order) {
      vector<T*> childs;
      for (auto eu : vs[vid].child) {
        int uid = eu.to;
        childs.push_back(*table[uid]);
      }
      update(table[vid], childs, vs[vid]);
    }
    return table;
  }

  /*
  @brief 全方位木DPができるライブラリ
  @detail クラスTで一般化されている。
  このTは有向辺に対応するDPテーブルである。
  要件 : Tどうしは二項演算が可能で、これらは可換で結合法則がある

  @param[in] init 頂点vで初期化するときのTの値
  @param[in] oper 頂点に入ってくる辺のDPテーブル同士の二項演算
  二項演算されたものどうしでも定義されておく必要がある。
  @param[in] finalize 頂点vから辺eを通って出ていくときに行う演算
  @param[out] result 各頂点vに入ってくる辺に蓄えられているDPテーブルを出力する。
  */
  template <typename T>
  vector<vector<T>> update_all(
      function<void(Vertex<TV, TE>&, T&)> init, function<T(T, T)> oper,
      function<void(Vertex<TV, TE>&, Edge<TE>&, T&)> finalize) {
    build_tree(0);
    assert(root != -1);
    vector<vector<T>> result;
    result.resize(N);
    vector<int> order = get_order();
    vector<vector<T>> up(N);
    vector<T> down(N);
    for (auto vid : order) {
      T latest;
      up[vid].push_back(latest);
      init(vs[vid], up[vid].back());
      for (auto eu : vs[vid].child) {
        int uid = eu.to;
        result[vid].push_back(up[uid].back());
        up[vid].push_back(oper(up[vid].back(), up[uid].back()));
      }
      T last = up[vid].back();
      finalize(vs[vid], vs[vid].parent, last);
      up[vid].push_back(last);
    }
    reverse(order.begin(), order.end());
    for (auto vid : order) {
      int m = vs[vid].child.size();
      T tmp;
      init(vs[vid], tmp);
      if (vid != root) {
        tmp = oper(tmp, down[vid]);
        result[vid].push_back(down[vid]);
      }
      for (int i = m - 1; i >= 0; i--) {
        int uid = vs[vid].child[i].to;
        down[uid] = oper(up[vid][i], tmp);
        finalize(vs[vid], vs[vid].child[i], down[uid]);
        tmp = oper(tmp, up[uid].back());
      }
    }
    return result;
  }

  /*
  // example of update-all-direction.

  struct TV {};
  struct TE {
    int w;
  };


  struct DP {
    LL dist;
    LL flip;
  };
  function<void(Vertex<TV, TE>&, DP&)> dp_init = [](Vertex<TV, TE>& v, DP& dp) {
    dp.dist = 0;
    dp.flip = 0;
  };
  function<DP(DP, DP)> dp_eval = [](DP dp1, DP dp2) {
    DP dp;
    dp.dist = max(dp1.dist, dp2.dist);
    dp.flip = dp1.flip + dp2.flip;
    return dp;
  };
  function<void(Vertex<TV, TE> & v, Edge<TE>&, DP&)> dp_finalize =
      [](Vertex<TV, TE>& v, Edge<TE>& out, DP& dp) {
        dp.dist += out.field.weight;
        if (out.to != out.field.to) dp.flip++;
      };

  int N;
  cin >> N;
  Graph graph(N);
  for(int i=0; i<N-1; i++) {
    int v, u;
    cin >> v >> u;
    TE e;
    graph.add_edge(v, u, e);
  }

  auto results = graph.update_all(dp_init, dp_eval, dp_finalize);
  for (auto vec : results) {
    DP base;
    base.ans = 1;
    for (auto val : vec) base = dp_eval(base, val);
    cout << base.ans << endl;
  }
  */
};
