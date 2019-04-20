inline LL take_mod(LL a, LL m) { return (a % m + m) % m; }

LL ext_gcd(LL a, LL b, LL &p, LL &q) {
  if (b == 0) {
    p = 1;
    q = 0;
    return a;
  }
  LL d = ext_gcd(b, a % b, q, p);
  q -= a / b * p;
  return d;
}

pair<LL, LL> crt(const vector<LL> &b, const vector<LL> &m) {
  LL r = 0, M = 1;
  for (int i = 0; i < (int)b.size(); ++i) {
    LL p, q;
    LL d = ext_gcd(M, m[i], p, q);
    if ((b[i] - r) % d != 0) return make_pair(0, -1);
    LL tmp = (b[i] - r) / d * p % (m[i] / d);
    r += M * tmp;
    M *= m[i] / d;
  }
  return make_pair(take_mod(r, M), M);
}
