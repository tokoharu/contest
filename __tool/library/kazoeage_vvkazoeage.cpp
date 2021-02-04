
template <int size = 2000000, bool preserve = false>
class CombinationTool {
  vector<mint> invs;

 public:
  vector<mint> kaijo;
  vector<vector<mint>> table;

  CombinationTool() {
    int N = size;
    if (preserve) {
      table.resize(N + 5);
      for (int i = 0; i < N + 5; i++) table[i].resize(i + 1);
      for (int i = 0; i < N; i++) {
        table[i][0] = 1;
        table[i][i] = 1;
      }
      for (int i = 1; i < N + 5; i++)
        for (int j = 1; j < i; j++)
          table[i][j] = table[i - 1][j - 1] + table[i - 1][j];

    } else {
      kaijo.resize(N + 5);
      invs.resize(N + 5);
      kaijo[0] = 1;
      invs[0] = 1;
      for (int i = 1; i < N + 5; i++) {
        kaijo[i] = kaijo[i - 1] * i;
        invs[i] = mint(1) / kaijo[i];
      }
    }
  }

  mint get(int n, int m) {
    if (m < 0 || m > n) return mint(0);
    if (preserve) return table[n][m];
    return kaijo[n] * invs[m] * invs[n - m];
  }
};
