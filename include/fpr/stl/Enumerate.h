#pragma once

#include <type_traits>
#include <utility>

namespace fpr {
/// Used to invoke enumerator.
class Enumerate
{};
constexpr Enumerate enumerate;

template<class T, class I = typename T::iterator>
struct EnumerationItr : public I
{
    using base_iterator = I;
    /// Pair of index and the item at the index.
    using value_type =
      std::pair<const std::size_t, const typename I::reference>;

  private:
    /// Index of the item.
    int pos;

  public:
    EnumerationItr(T& t, base_iterator itr)
      : base_iterator{ itr }
      , pos{ distance(t.begin(), itr) }
    {}

    value_type operator*() { return { pos, base_iterator::operator*() }; }

    EnumerationItr& operator++()
    {
        pos++;
        base_iterator::operator++();
        return *this;
    }
};

/// Enumeration that gives a range based loop with index.
/// @tparam T Container to iterate.
template<class T>
struct EnumerationTmp : public T
{
    EnumerationTmp(T&& t)
      : T{ std::move(t) }
    {}
    using iterator = EnumerationItr<T>;

    iterator begin() { return { *this, this->T::begin() }; };
    iterator end() { return { *this, this->T::end() }; };
};

template<class T, class I = typename T::iterator>
struct EnumerationRef
{
    T& t;
    EnumerationRef(T& t)
      : t{ t }
    {}

    using iterator = EnumerationItr<T, I>;
    iterator begin() const { return { t, t.begin() }; };
    iterator end() const { return { t, t.end() }; };
};

template<class T>
const EnumerationRef<const T, typename T::const_iterator> constexpr
operator|(const T& t, Enumerate)
{
    return t;
};

template<class T, std::enable_if_t<!std::is_const_v<T>, bool> = true>
EnumerationRef<T> constexpr
operator|(T& t, Enumerate)
{
    return t;
};

// template<class T>
// EnumerationTmp<T> constexpr
// operator|(T&& t, Enumerate)
// {
//     return EnumerationTmp<T>{ std::move(t) };
// }
};