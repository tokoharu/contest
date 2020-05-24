
int LIS(vector<LL>& v, vector<LL>& ans) {
  const LL INF = 1LL << 60;
  vector<LL> dp(v.size(), INF);
  for (auto e : v) {
    *lower_bound(dp.begin(), dp.end(), e) = e;
  }
  ans = dp;
  return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}
