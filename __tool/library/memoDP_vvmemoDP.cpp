template <typename T, size_t NDIMS>
class MemoDP {
 public:
  template <typename... SIZE_T>
  MemoDP(int n, SIZE_T... sizes) {
    N = n;
    dp = exvector(T(), sizes...);
    used = exvector(int(0), sizes...);
  }

  template <typename... SIZE_T>
  T do_dp_recursive(SIZE_T... pos) {
    // 3次元を仮定
    int x, y, z;
    tie(x, y, z) = tie(pos...);
    if (used[x][y][z]) {
      return dp[x][y][z];
    }
    if (x == 0 && y == 0 && z == 0) {
      return 0;
    }
    used[x][y][z] = 1;
    // 遷移
    double base = (double)(x + y + z) / N;
    T result = 1 / base;
    if (z >= 1) result += do_dp_recursive(x, y + 1, z - 1) * z / base / N;
    if (y >= 1) result += do_dp_recursive(x + 1, y - 1, z) * y / base / N;
    if (x >= 1) result += do_dp_recursive(x - 1, y, z) * x / base / N;

    // cout << x << " " << y << " " << z << " " << result << endl;
    return dp[x][y][z] = result;
  }

  template <typename... SIZE_T>
  typename detail::vector_builder<T, NDIMS>::type do_dp(SIZE_T... pos) {
    do_dp_recursive(pos...);
    return dp;
  }

 private:
  int N;
  typename detail::vector_builder<T, NDIMS>::type dp;
  typename detail::vector_builder<int, NDIMS>::type used;
};