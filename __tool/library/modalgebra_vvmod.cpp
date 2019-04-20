

long long mul(long long a, long long b, const long long MOD) {
  return b ? (mul(a * 2, b / 2, MOD) + (b & 1 ? a : 0)) % MOD : 0;
}

long long bpow(long long a, long long b, const long long MOD) {
  return (b ? bpow(a * a % MOD, b / 2, MOD) * (b & 1 ? a : 1) : 1) % MOD;
}

long long inv(long long a, const long long MOD) {
  return bpow(a, MOD - 2, MOD);
}

vector<long long> MODS = {1000000007};
template <int kind = 0>
class mint {
 public:
  long long v;

  mint() : v(0) {}
  mint(long long v) : v((v % MODS[kind] + MODS[kind]) % MODS[kind]) {}
  long long get_mod() { return MODS[kind]; }
  long long get_val() { return v; }
};

template <int kind>
ostream& operator<<(ostream& os, const mint<kind>& x) {
  return os << x.v;
}

template <int kind>
bool operator==(mint<kind>& a, mint<kind> b) {
  return a.v == b.v;
}
template <int kind>
mint<kind>& operator+=(mint<kind>& a, mint<kind> b) {
  return a = a.v + b.v;
}
template <int kind>
mint<kind>& operator-=(mint<kind>& a, mint<kind> b) {
  return a = a.v - b.v;
}
template <int kind>
mint<kind>& operator*=(mint<kind>& a, mint<kind> b) {
  return a = a.v * b.v;
}
template <int kind>
mint<kind>& operator/=(mint<kind>& a, mint<kind> b) {
  return a = a.v * inv(b.v, a.get_mod());
}
template <int kind>
mint<kind> operator+(mint<kind> a, mint<kind> b) {
  return a += b;
}
template <int kind>
mint<kind> operator-(mint<kind> a, mint<kind> b) {
  return a -= b;
}
template <int kind>
mint<kind> operator*(mint<kind> a, mint<kind> b) {
  return a *= b;
}
template <int kind>
mint<kind> operator/(mint<kind> a, mint<kind> b) {
  return a /= b;
}
template <int kind>
mint<kind>& operator+=(mint<kind>& a, long long b) {
  return a = a.v + b;
}
template <int kind>
mint<kind>& operator-=(mint<kind>& a, long long b) {
  return a = a.v - b;
}
template <int kind>
mint<kind>& operator*=(mint<kind>& a, long long b) {
  return a = a.v * b;
}
template <int kind>
mint<kind>& operator/=(mint<kind>& a, long long b) {
  return a = a.v * inv(b, a.get_mod());
}
template <int kind>
mint<kind> operator+(mint<kind> a, long long b) {
  return a += b;
}
template <int kind>
mint<kind> operator-(mint<kind> a, long long b) {
  return a -= b;
}
template <int kind>
mint<kind> operator*(mint<kind> a, long long b) {
  return a *= b;
}
template <int kind>
mint<kind> operator/(mint<kind> a, long long b) {
  return a /= b;
}