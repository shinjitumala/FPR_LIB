#pragma once
#include <functional>
#include <ranges>

namespace fpr {
using namespace std;
/// Use this to invoke the filter.
template<class T>
struct Filter
{
    Filter(T f)
      : f{ f } {};
    T f;
};

template<class T, class F>
class RefView
{
    T& t;
    Filter<F> f;

  public:
    RefView(T& t, Filter<F>&& f)
      : t{ t }
      , f{ move(f) }
    {}

    RefView(RefView&&) = default;

    class iterator : protected T::iterator
    {
        using Base = typename T::iterator;
        using Base::Base;
        using Base::operator*;
        using Base::operator->;

        iterator operator++() { return find_if(*this, t.end(), f); };
    };
};

template<class T>
class TmpView
{};

template<class T, class F>
RefView<T, F>
operator|(T& t, Filter<F>&& f)
{
    return { t, move(f) };
}
};