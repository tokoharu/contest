// chmax, chmin
template <class T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
template <class T>
inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}

template <typename T>
function<T(T, T)> op_max = [](T a, T b) -> T { return max(a, b); };
template <typename T>
function<T(T, T)> op_min = [](T a, T b) -> T { return min(a, b); };

template <typename T>
function<T(T, T)> op_sum = [](T a, T b) -> T { return a + b; };

namespace detail {
template <typename T, std::size_t NDIMS>
struct vector_builder {
  using type = std::vector<typename vector_builder<T, NDIMS - 1>::type>;

  static type make(std::vector<std::size_t> dims, const T& v = {}) {
    const auto vec = std::vector<T>(dims.empty() ? 0 : dims.back(), v);
    if (!dims.empty()) dims.pop_back();
    return vector_builder<std::vector<T>, NDIMS - 1>::make(dims, vec);
  }
};

template <typename T>
struct vector_builder<T, 1> {
  using type = std::vector<T>;

  static type make(std::vector<std::size_t> dims, const T& v = {}) {
    return type(dims.empty() ? 0 : dims.back(), v);
  }
};
}  // namespace detail

template <typename T, typename... SIZE_T>
auto exvector(const T& v, SIZE_T... dims) {
  static_assert(sizeof...(dims) != 0, "invalid dimension");
  std::vector<std::size_t> vec_dims{dims...};
  return detail::vector_builder<T, sizeof...(dims)>::make(vec_dims, v);
}

using namespace std;
//********************  dumps ************************//

template <typename T>
void dump(const T& data, vector<int>& iter) {
  cout << data << " ";
}
template <typename T>
void dump(const vector<T>& data, vector<int>& iter) {
  for (auto elem : data) dump(elem, iter);
  cout << endl;
}

template <typename T>
void dump(const vector<vector<T>>& data, vector<int>& iter) {
  for (auto elem : iter) {
    cout << "[" << elem << "]";
  }
  cout << endl;
  for (int i = 0; i < data.size(); i++) {
    iter.push_back(i);
    dump(data[i], iter);
    iter.pop_back();
  }
  cout << endl;
}

template <typename T>
void dump(const vector<T>& data, int dummy) {
  for (int i = 0; i < data.size(); i++) {
    cout << "[" << i << "] " << data[i] << endl;
  }
}
template <typename T>
void dump(const T& data) {  // T : data, U = base type val.
  vector<int> iter;
  dump(data, iter);
}
