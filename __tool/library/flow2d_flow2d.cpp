struct Data2D {
  LL x;
  LL y;
  LL demand;

  Data2D(LL x, LL y, LL demand) : x(x), y(y), demand(demand){};
  bool operator<(Data2D& o) {
    if (x < o.x) return true;
    if (x > o.x) return false;
    if (y > o.y) return true;
    if (y < o.y) return false;
    if (demand < o.demand) return true;
    if (demand > o.demand) return false;
    return false;
  }
};
/**
 * x,y平面の左上から右下へ流れる最大流で最大のものを出力する。
 *
 */
LL flow2D(vector<Data2D> pts) {
  sort(pts.begin(), pts.end());
  map<LL, LL> mp;
  LL ans = 0;
  for (auto pt : pts) {
    LL y = pt.y;
    LL demand = pt.demand;
    while (demand > 0) {
      auto it = mp.lower_bound(y);
      if (it == mp.end()) break;
      if (it->second <= demand) {
        ans += it->second;
        demand -= it->second;
        mp.erase(it);
      } else {
        it->second -= demand;
        ans += demand;
        demand = 0;
      }
    }
    if (demand < 0) {
      mp[y] -= demand;
    }
  }
  return ans;
}