const long long MOD_CONST = 998244353;
long long mul_mod(long long a, long long b, const long long MOD) {
  return b ? (mul_mod(a * 2, b / 2, MOD) + (b & 1 ? a : 0)) % MOD : 0;
}

long long bpow_mod(long long a, long long b, const long long MOD) {
  return (b ? bpow_mod(a * a % MOD, b / 2, MOD) * (b & 1 ? a : 1) : 1) % MOD;
}

long long inv_mod(long long a, const long long MOD) {
  return bpow_mod(a, MOD - 2, MOD);
}
template <long long param = MOD_CONST, bool fast = false>
class mint {
 private:
  using Z = int;
  using N = unsigned int;
  using ZZ = long long;
  using NN = unsigned long long;
  struct {
  } constexpr static exact{};
  // Using Z deliberately to avoid Z -> N promotion.
  template <class Ret = ZZ&>
  static auto modulo() -> std::enable_if_t<(param <= 0), Ret> {
    static ZZ mod = 0;
    return mod;
  }
  template <class Ret = const ZZ>
  static auto mod() -> std::enable_if_t<(param <= 0), Ret> {
    return modulo();
  }
  template <class Ret = const ZZ>
  static constexpr auto mod() -> std::enable_if_t<(param > 0), Ret> {
    return param;
  }

 public:
  template <class Arg = ZZ>
  static void set_modulo(const std::enable_if_t<(param <= 0), Arg> mod) {
    modulo() = mod;
  }
  long long v;

  constexpr mint() : v(0) {}

  constexpr mint(long long v)
      : v(fast ? (v)
               : (v < 0 ? (v % mod() + mod()) % mod()
                        : (v >= mod() ? v % mod() : v))) {}
  constexpr long long get_mod() { return mod(); }
  long long get_val() { return v; }
  void take_mod() { v %= mod(); }
};
template <long long param, bool fast>
ostream& operator<<(ostream& os, mint<param, fast>& x) {
  return os << (x.v % x.get_mod() + x.get_mod()) % x.get_mod();
}

template <long long param, bool fast, bool fast2>
bool operator==(mint<param, fast>& a, mint<param, fast2> b) {
  return a.v == b.v;
}
template <long long param, bool fast, bool fast2>
mint<param, fast>& operator+=(mint<param, fast>& a, mint<param, fast2> b) {
  return a = a.v + b.v;
}
template <long long param>
mint<param>& operator-=(mint<param>& a, mint<param> b) {
  return a = a.v - b.v;
}
template <long long param>
mint<param>& operator*=(mint<param>& a, mint<param> b) {
  return a = a.v * b.v;
}
template <long long param>
mint<param>& operator/=(mint<param>& a, mint<param> b) {
  return a = a.v * inv_mod(b.v, a.get_mod());
}
template <long long param, bool fast, bool fast2>
mint<param, fast> operator+(mint<param, fast> a, mint<param, fast2> b) {
  return a += b;
}
template <long long param>
mint<param> operator-(mint<param> a, mint<param> b) {
  return a -= b;
}
template <long long param>
mint<param> operator*(mint<param> a, mint<param> b) {
  return a *= b;
}
template <long long param>
mint<param> operator/(mint<param> a, mint<param> b) {
  return a /= b;
}
template <long long param, bool fast>
mint<param, fast>& operator+=(mint<param, fast>& a, long long b) {
  return a = a.v + b;
}
template <long long param>
mint<param>& operator-=(mint<param>& a, long long b) {
  return a = a.v - b;
}
template <long long param>
mint<param>& operator*=(mint<param>& a, long long b) {
  return a = a.v * b;
}
template <long long param>
mint<param>& operator/=(mint<param>& a, long long b) {
  return a = a.v * inv_mod(b, a.get_mod());
}
template <long long param, bool fast>
mint<param, fast> operator+(mint<param> a, long long b) {
  return a += b;
}
template <long long param>
mint<param> operator-(mint<param> a, long long b) {
  return a -= b;
}
template <long long param>
mint<param> operator*(mint<param> a, long long b) {
  return a *= b;
}
template <long long param>
mint<param> operator/(mint<param> a, long long b) {
  return a /= b;
}
