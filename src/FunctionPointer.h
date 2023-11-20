#include <type_traits>
#include <utility>

using namespace std;

template<typename _Tp>
using decay_t_ = typename decay<_Tp>::type;

template<typename Callable>
union storage
{
    storage() {}
    decay_t_<Callable> callable;
};

template<int, typename Callable, typename Ret, typename... Args>
auto FunctionPointer_(Callable&& c, Ret (*)(Args...))
{
    static bool used = false;
    static storage<Callable> s;
    using type = decltype(s.callable);

    if(used)
        s.callable.~type();
    new (&s.callable) type(std::forward<Callable>(c));
    used = true;

    return [](Args... args) -> Ret {
        return Ret(s.callable(std::forward<Args>(args)...));
    };
}

template<typename Fn, int N = 0, typename Callable>
Fn* FunctionPointer(Callable&& c)
{
    return FunctionPointer_<N>(std::forward<Callable>(c), (Fn*)nullptr);
}
