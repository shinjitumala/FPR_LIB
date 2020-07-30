#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

namespace fpr {
class Reverse
{};
constexpr Reverse reverse;

template<class T>
struct RevRef
{
    T& t;
    RevRef(T& t)
      : t{ t }
    {}
    using iterator = decltype(t.rbegin());
    iterator begin() { return t.rbegin(); };
    iterator end() { return t.rend(); };
    size_t size() { return t.size(); };
};

template<class T>
struct RevTmp : public T
{
    RevTmp(T&& t)
      : T{ move(t) }
    {}
    using iterator = decltype(std::declval<T>().rbegin());
    iterator begin() { return this->rbegin(); };
    iterator end() { return this->rend(); };
};

template<class T>
RevRef<T>
operator|(T& t, Reverse)
{
    return t;
}

template<class T>
RevTmp<T>
operator|(T&& t, Reverse)
{
    return move(t);
}
}