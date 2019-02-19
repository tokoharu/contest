
template <typename T>
class SegmentTree {
  int N;
  vector<T> dat;
  function<T(T, T)> oper;
  T identity;

 public:
  SegmentTree(int n, function<T(T, T)> op, T id) {
    oper = op;
    identity = id;
    N = 1;
    while (N < n) N *= 2;
    dat.resize(2 * N, identity);
  }
  // update k th element, 0-indexed
  void update(int k, T a) {
    k += N - 1;  // leaf
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = oper(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }
  // query[a, b), 0-indexed
  T query(int a, int b) { return query(a, b, 0, 0, N); }
  T query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return identity;
    if (a <= l && r <= b) return dat[k];
    int m = (l + r) / 2;
    return oper(query(a, b, k * 2 + 1, l, m), query(a, b, k * 2 + 2, m, r));
  }
};