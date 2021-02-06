template<class>
struct get_sig_impl {};

template<class F, class R, class H, class ...Args>
struct get_sig_impl<R (F::*)(H, Args...) const > {
using return_type=R;
using arg_type=std::tuple<Args...>;
};

template <class F> class memo_impl {
    using sig_impl =get_sig_impl<decltype(&F::template operator()<memo_impl<F> &>)>;
    using R = typename sig_impl::return_type;
    using Arg = typename sig_impl::arg_type;

  std::map<Arg, R> memo;
  F func;

  memo_impl(F &&func_) : memo(), func(std::forward<F>(func_)) {}

  template <std::size_t... I>
  R apply(const Arg &arg, std::index_sequence<I...>) {
    return func(*this, std::get<I>(arg)...);
  }

public:
    template<class ...Args>
  R operator()(Args &&... args) {
    Arg arg(std::forward<Args>(args)...);
    {
      const auto itr = memo.find(arg);
      if (itr != memo.end()) {
        return itr->second;
      }
    }
    R res =
        apply(arg, std::make_index_sequence<
                               std::tuple_size<std::tuple<Args...>>::value>());
    memo.insert(std::make_pair(std::move(arg), res));
    return res;
  }

  template <class F_>
  friend auto memorized(F_ &&);
};

template<class F_>
auto memorized(F_ &&func) {
    return memo_impl<F_>(std::forward<F_>(func));
}

//  ex : 
  // auto fib = memorized(
  //     [&](auto &&fib, int n) -> u32 {
  //       if (n <= 1) {
  //         return 1;
  //       } else {
  //         return fib(n - 2) + fib(n - 1);
  //       }
  //     });

  // std::cout << fib(10000);


