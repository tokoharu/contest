
template <typename T>
class CumulativeSum {
  const int n;
  std::vector<T> sum_data;
  function<T(T, T)> plus;
  function<T(T, T)> minus;
  T id;

 public:
  CumulativeSum(vector<T> data, T id = T(0),
                function<T(T, T)> plus = op_plus<T>,
                function<T(T, T)> minus = op_minus<T>)
      : n(data.size()), id(id), plus(plus), minus(minus) {
    sum_data.resize(n + 1, id);
    for (int i = 0; i < n; i++) {
      sum_data[i + 1] = plus(sum_data[i], data[i]);
    }
  }

  // 区間 [l, r) 番目の範囲の和を求める．(l >= r のときは 0 を返す．)
  T sum(int l, int r) const {
    if (l >= r) return id;
    return minus(sum_data[r], sum_data[l]);
  }
};

template <typename T>
vector<T> ruiseki(vector<T> base, T id, bool reverse = false,
                  function<T(T, T)> op = op_plus<T>) {
  vector<T> res(base.size() + 1, id);
  if (!reverse)
    for (int i = 0; i < base.size(); i++) res[i + 1] = op(base[i], res[i]);
  if (reverse)
    for (int i = base.size() - 1; i >= 0; i--) {
      res[i] = op(base[i], res[i + 1]);
    }
  return ruiseki;
}
