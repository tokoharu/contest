template<typename T>
class PQ{
public:
  priority_queue<T> obj;
  void push(T a) {
    obj.push(a);
  }
  void pop() {
    obj.pop();
  }
  T top() {
    return obj.top();
  }
  bool empty() {
    return obj.empty();
  }
  void print() {
    priority_queue<T> tmp = obj;
    cout << "<  ";
    while(!tmp.empty()) {
      cout << tmp.top() << " ";
      tmp.pop();
    }
    cout << " > " << endl;
  }
  /*
    priority_queueの先頭 x 番目の要素を取得. 時間 O(x)
  */
  T get(int x) {
    stack<T> tmp;
    for(int i=0; i<x; i++) {
      tmp.push(obj.top());
      obj.pop();
    } 
    T ret = obj.top();
    while(!tmp.empty()) {
      obj.push(tmp.top());
      tmp.pop();
    }
    return ret;

  }
  /*
  priority_queueに入っている要素が整合していなければ、修正をしてpriority_queueの中に戻す関数
  functor : 要素 e の本来の値を返す関数
  x : x 番目に小さい要素(0-origin)

  functorのexample:
  
  auto correct = [&](PII input){
    LL v = input.second; 
    return PII(as[v] + bs[v], v);
  };

  */
  template<class tFunctor>
  bool patch(tFunctor functor, int x) {
    stack<T> tmp;
    for(int i=0; i<x; i++) {
      tmp.push(obj.top());
      obj.pop();
    } 
    T prev = obj.top();
    T current = functor(prev);
    bool result = (prev != current);
    if(result) {
      obj.pop();
      obj.push(current);
    }
    while(!tmp.empty()) {
      obj.push(tmp.top());
      tmp.pop();
    }
    return result;
  }

};
