// 指定された関数で最適な値をとるエレメントとその場所を返す。
// minimize=falseであれば、最大化を行う
//
// (ex)
//  vector<int> y = {1,2,3};
//  auto func = [](int t){return t * t;};
//  auto ret = get_optimal(y, func);
//  cout << ret <<endl;

template<typename T, typename V>
pair<LL, LL> get_optimal(vector<T> val, V func, bool minimize=true) {
  auto maxim = func(val[0]);
  auto minim = func(val[0]);
  int max_idx = 0;
  int min_idx = 0;
  for(int i=0; i<val.size(); i++) {
    auto tmp = func(val[i]);
    if(maxim < tmp) {maxim  = tmp, max_idx = i;} 
    if(minim > tmp) {minim = tmp, min_idx = i;}  
  }

  return minimize ? make_pair(minim, min_idx) : make_pair(maxim, max_idx);
  // return make_pair(maxim, minim); // 最大値と最小値を両方取りたいとき
}