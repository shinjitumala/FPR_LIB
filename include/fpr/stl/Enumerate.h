#pragma once

#include <type_traits>

namespace fpr {
/// Used to invoke enumerator.
class Enumerate
{};
constexpr Enumerate enumerate;

/// Enumeration that gives a range based loop with index.
/// @tparam T Container to iterate.
template<class T, class Itr>
struct EnumerationBase
{
    EnumerationBase(T& t)
      : t{ &t }
    {}

    T* const t;

    /// Pair of index and the item at the index.
    struct Item
    {
        const int index;
        decltype(*t->begin())&& item;
    };

    /// Wrapper iterator
    struct iterator : public Itr
    {
        using value_type = Item;

        /// Index of the item.
        int pos;

        explicit iterator(T* t, Itr itr)
          : Itr{ itr }
          , pos{ distance(t->begin(), itr) }
        {}

        value_type operator*()
        {
            Item i{ pos, Itr::operator*() };
            return i;
        }

        iterator& operator++()
        {
            pos++;
            Itr::operator++();
            return *this;
        }
    };

    constexpr iterator begin() { return iterator{ t, t->begin() }; };
    constexpr iterator end() { return iterator{ t, t->end() }; };
};

template<class T, bool = std::is_const_v<T>>
class Enumeration
{};

template<class T>
struct Enumeration<T, false> : public EnumerationBase<T, typename T::iterator>
{};

template<class T>
struct Enumeration<T, true>
  : public EnumerationBase<T, typename T::const_iterator>
{};

template<class T>
Enumeration<T> constexpr
operator|(T& t, Enumerate)
{
    return Enumeration<T>{ t };
};
};