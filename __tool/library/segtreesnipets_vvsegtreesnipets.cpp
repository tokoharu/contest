
namespace SegSnipets{
// reference:  https://betrue12.hateblo.jp/entry/2020/09/23/005940


// (1) 区間加算・区間最小値取得

// using S = long long;
// using F = long long;

// const S INF = 8e18;

// S op(S a, S b){ return std::min(a, b); }
// S e(){ return INF; }
// S mapping(F f, S x){ return f+x; }
// F composition(F f, F g){ return f+g; }
// F id(){ return 0; }

// (2) 区間加算・区間最大値取得
// using S = long long;
// using F = long long;

// const S INF = 8e18;

// S op(S a, S b){ return std::max(a, b); }
// S e(){ return -INF; }
// S mapping(F f, S x){ return f+x; }
// F composition(F f, F g){ return f+g; }
// F id(){ return 0; }

// (3) 区間加算・区間和取得
// struct S{
//     long long value;
//     int size;
// };
// using F = long long;

// S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
// S e(){ return {0, 0}; }
// S mapping(F f, S x){ return {x.value + f*x.size, x.size}; }
// F composition(F f, F g){ return f+g; }
// F id(){ return 0; }


// (4) 区間変更・区間最小値取得
// AOJ（RMQ and RUQ）提出：Aizu Online Judge

// using S = long long;
// using F = long long;

// const S INF = 8e18;
// const F ID = 8e18;

// S op(S a, S b){ return std::min(a, b); }
// S e(){ return INF; }
// S mapping(F f, S x){ return (f == ID ? x : f); }
// F composition(F f, F g){ return (f == ID ? g : f); }
// F id(){ return ID; }


//(5) 区間変更・区間最大値取得
// using S = long long;
// using F = long long;

// const S INF = 8e18;
// const F ID = 8e18;

// S op(S a, S b){ return std::max(a, b); }
// S e(){ return -INF; }
// S mapping(F f, S x){ return (f == ID ? x : f); }
// F composition(F f, F g){ return (f == ID ? g : f); }
// F id(){ return ID; }

// (6) 区間変更・区間和取得
// 区間幅が必要なので値を構造体で持ちます。seg.prod(l, r).value で値を取り出してください。

// AOJ（RSQ and RUQ）提出：Aizu Online Judge

// struct S{
//     long long value;
//     int size;
// };
// using F = long long;

// const F ID = 8e18;

// S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
// S e(){ return {0, 0}; }
// S mapping(F f, S x){
//     if(f != ID) x.value = f*x.size;
//     return x;
// }
// F composition(F f, F g){ return (f == ID ? g : f); }
// F id(){ return ID; }


using Lazy = lazy_segtree<S, op, e, F, mapping, composition, id>;
}



