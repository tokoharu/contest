

// 普通の転倒数数え上げ
LL inversion_counting() {
  fenwick_tree<LL> fw(N+5);
  LL inv = 0;
  for(int i=0; i<N; i++) {
    LL q = fw.sum(a[i], N+1);
    inv += q;
    fw.add(a[i], 1);
  }
}

//  出典 :
//  http://noshi91.hatenablog.com/entry/2018/12/28/210907#comment-17680117127061434756
//  K値のみからなる転倒数の数え上げを効率的にできる型
//  群構造になっているため、BITに適用可能
// 
template <int K>
class InversionCountingValueK {
 public:
  ::std::array<int, K> x;
  int z;

  InversionCountingValueK() : x(), z(0) {}
  InversionCountingValueK(int c) : x(), z(0) { x[c] = 1; }
};

template <int K>
InversionCountingValueK<K> operator+(const InversionCountingValueK<K> &s,
                                     const InversionCountingValueK<K> &t) {
  InversionCountingValueK<K> ret;
  for (int i = 0; i < K; ++i) {
    ret.x[i] = s.x[i] + t.x[i];
  }
  ret.z = s.z + t.z;
  int sum = 0;
  for (int i = 0; i < K; ++i) {
    ret.z += s.x[i] * sum;
    sum += t.x[i];
  }
  return ret;
}

template <int K>
InversionCountingValueK<K> operator-(const InversionCountingValueK<K> &s) {
  InversionCountingValueK<K> ret;
  for (int i = 0; i < K; ++i) {
    ret.x[i] = -s.x[i];
  }
  ret.z = -(ret + s).z;
  return ret;
}

// 使用例
/*
int main() {
  vector<int> input = {1, 5, 4, 3, 2};
  vector<InversionCountingValueK<7>> data;
  transform(input.begin(), input.end(), back_inserter(data),
            [](int val) { return InversionCountingValueK<7>(val); });

  InversionCountingValueK<7> answer =
      accumulate(data.begin(), data.end(), InversionCountingValueK<7>(0));

  cout << answer.z << endl;

  return 0;
}

*/