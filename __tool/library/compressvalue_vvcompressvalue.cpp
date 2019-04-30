
/**
 * 座標圧縮を行うライブラリ
 */
class CompressingValues {
  map<LL, LL> mapping;
  vector<LL> restration;

 public:
  CompressingValues(vector<LL> data) {
    sort(data.begin(), data.end());
    restration.resize(data.size());
    for (int i = 0; i < data.size(); i++) {
      mapping[data[i]] = i;
      restration[i] = data[i];
    }
  }

  LL get_compressed(LL x) {
    if (mapping.find(x) == mapping.end()) assert(false);
    return mapping[x];
  }

  LL get_original(LL x) {
    if (x < 0 || x >= restration.size()) assert(false);
    return restration[x];
  }
};

// 使用例
/*

int main() {
  vector<LL> data = {1, 100, 10000, 100000, 100000000};
  CompressingValues cx(data);
  cout << cx.get_compressed(10000) << endl; // 2
  cout << cx.get_original(4) << endl; // 100000000
  return 0;
}

*/