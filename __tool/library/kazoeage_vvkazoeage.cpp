
vector<mint<>> kaijo;
void init() {
  kaijo.push_back(mint<>(1));
  for (int i = 1; i <= 400000; i++) {
    kaijo.push_back(kaijo.back() * i);
  }
}

mint<> comb(LL N, LL K) {
  if (K < 0) return mint<>(0);
  if (K > N) return mint<>(0);
  return kaijo[N] / kaijo[N - K] / kaijo[K];
}
