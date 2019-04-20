
/*
ある系が時間変化するとき、各状態のクエリを返すもの

SegmentTreeライクな構造の各頂点にデータ構造を載せる。
時刻iのクエリにおけるクエリxがあれば、
segmentTreeにおける自身の親たちに適用しそれらを統合した結果を返す。

TNode ... SegmentTreeのノードにおけるクラス.
- query(TQuery q)をサポートしている必要がある
- コンストラクタ (vector<TElement>) をサポートする必要がある。

TElement : 変更クエリを表す。
- メンバstarttime, endtimeにアクセスできる必要がある。

入力

- vector<TQuery>は時刻順に並べる必要がある
- vector<TElement>は時刻順に並べる必要がある
- oper, 各結果を統合するための演算
- results : これは空のvectorにしておく。

*/
template <typename TNode, typename TQuery, typename TElement, typename TResult>
class StreamingQuery {
  int N;
  vector<TNode> base_structure;
  vector<vector<TElement>> elements;

  // query[a, b), 0-indexed
  void add_elements(int a, int b, TElement& elem) {
    add_elements(a, b, 0, 0, N, elem);
  }
  void add_elements(int a, int b, int k, int l, int r, TElement& elem) {
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      elements[k].push_back(elem);
      return;
    }
    int m = (l + r) / 2;
    add_elements(a, b, k * 2 + 1, l, m, elem);
    add_elements(a, b, k * 2 + 2, m, r, elem);
  }

  void construct(int k) {
    k += N - 1;
    for (; k >= 0; k /= 2) {
      base_structure[k] = TNode(elements[k]);
      if (k % 2 == 0) break;
    }
  }

 public:
  StreamingQuery(vector<TQuery> answer_queries,
                 vector<TElement> element_queries,
                 function<TResult(TResult, TResult)> oper,
                 vector<TResult>& result) {
    LL n = 0;
    for (auto query : answer_queries) {
      n = max(n, query.time);
    }
    N = 1;
    while (N <= n + 1) N *= 2;
    base_structure.resize(2 * N);
    elements.resize(2 * N);

    int iter_aq = 0;
    int iter_eq = 0;

    for (int current_time = 0; current_time < N; current_time++) {
      while (element_queries.size() > iter_eq) {
        auto element = element_queries[iter_eq];
        if (element.starttime > current_time) break;

        if (element.endtime > N) element.endtime = N;

        add_elements(element.starttime, element.endtime, element);
        iter_eq++;
      }
      construct(current_time);
      while (answer_queries.size() > iter_aq) {
        auto element = answer_queries[iter_aq];
        if (element.time > current_time) break;

        int k = current_time + N - 1;
        TResult res = TResult();
        for (; k >= 0; k = (k - 1) / 2) {
          TResult tmp = base_structure[k].query(element);
          res = oper(res, tmp);
          if (k == 0) break;
        }
        result.push_back(res);
        iter_aq++;
      }
    }
  }
};

/*
 TNodeの例。
 単に最大値をとる関数。
 この構造はコンストラクタで決定されれば不変である
*/

template <typename TQuery, typename TElement>
class TakeLargest {
  int N;
  int largest;

  void setting(vector<int> data) {
    largest = -1000000;
    for (auto elem : data) {
      largest = max(largest, elem);
    }
  }

 public:
  TakeLargest() { setting(vector<int>()); }
  TakeLargest(vector<TElement> data) {
    vector<int> next;
    transform(data.begin(), data.end(), back_inserter(next),
              [](TElement elem) { return elem.val; });
    setting(next);
  }
  TakeLargest(vector<int> data) { setting(data); }

  int query(TQuery q) { return query(); }
  int query() { return largest; }
};