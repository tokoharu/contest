
template <typename T>
vector<T> ruiseki(vector<T> base, T id, bool reverse = false,
                  function<T(T, T)> op = op_sum<T>) {
  vector<T> res(base.size() + 1, id);
  if (!reverse)
    for (int i = 0; i < base.size(); i++) res[i + 1] = op(base[i], res[i]);
  if (reverse)
    for (int i = base.size() - 1; i >= 0; i--) {
      res[i] = op(base[i], res[i + 1]);
    }
  return ruiseki;
}