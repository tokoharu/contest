// slide min
template <class VAL, class TIME>
struct SlideMin {
  const VAL INF = 1LL << 60;  // to be set appropriately
  const TIME nul = -1;        // to be set appropriately

  deque<pair<VAL, TIME> > deq;
  SlideMin() {}

  // get minimum
  pair<VAL, TIME> get() {
    if (deq.empty()) return make_pair(INF, nul);
    return deq.front();
  }

  // push (v, t), "t is non-decreasing" is necessary
  void push(VAL v, TIME t) {
    while (!deq.empty() && deq.back().first >= v) deq.pop_back();
    deq.emplace_back(v, t);
  }

  // pop "< t", "t it non-decreasing" is necessary
  void pop(TIME t) {
    while (!deq.empty() && deq.front().second < t) deq.pop_front();
  }
};
