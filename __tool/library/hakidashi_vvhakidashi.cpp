
void xor_hakidashi(vector<vector<mint<1>>> table) {
  mint<1> one = 1;
  mint<1> zero = 0;
  int N = table.size();
  int M = table[0].size();
  int piv = 0;
  for (int j = 0; j < M; j++) {
    if (piv == N) continue;
    int pos = -1;
    for (int i = piv; i < N; i++) {
      if (table[i][j] == one) {
        pos = i;
      }
    }
    if (pos == -1) continue;
    swap(table[pos], table[piv]);
    for (int i = 0; i < N; i++) {
      if (i == piv) continue;
      if (table[i][j] == zero) continue;
      for (int j = 0; j < M; j++) {
        table[i][j] += table[piv][j];
      }
    }
    piv++;
  }
}