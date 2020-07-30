#pragma once

#include <type_traits>
#include <utility>

namespace fpr {
/// Used to invoke enumerator.
class WithIndex
{};
constexpr WithIndex with_index;

template<class T>
struct IndexIterator : public decltype(std::declval<T>().begin())
{
    using Base = decltype(std::declval<T>().begin());
    /// Pair of index and the item at the index.
    using value_type =
      std::pair<const std::size_t, const typename Base::reference>;

  private:
    /// Index of the item.
    std::size_t pos;

  public:
    IndexIterator(std::size_t pos, Base itr)
      : Base{ itr }
      , pos{ pos }
    {}

    value_type operator*() { return { pos, Base::operator*() }; }

    IndexIterator& operator++()
    {
        pos++;
        Base::operator++();
        return *this;
    }
};

/// Enumeration that gives a range based loop with index.
/// @tparam T Container to iterate.
template<class T>
struct WithIndexTmp : public T
{
    WithIndexTmp(T&& t)
      : T{ std::move(t) }
    {}
    using iterator = IndexIterator<T>;

    iterator begin() { return { 0, this->T::begin() }; };
    iterator end() { return { this->size() - 1, this->T::end() }; };
};

template<class T>
struct WithIndexRef
{
    T& t;
    WithIndexRef(T& t)
      : t{ t }
    {}

    using iterator = IndexIterator<T>;
    iterator begin() const { return { 0, t.begin() }; };
    iterator end() const { return { t.size() - 1, t.end() }; };
};

template<class T>
WithIndexTmp<T>
operator|(T&& t, WithIndex)
{
    return move(t);
}

template<class T>
WithIndexRef<T> constexpr
operator|(T& t, WithIndex)
{
    return t;
};

struct AsIterator
{};
constexpr AsIterator as_itr;

template<class I>
struct AsIteratorIterator : public I
{
    using value_type = I;
    value_type operator*() { return *this; }
};

template<class T>
struct AsIteratorRef
{
    T& t;
    using iterator = AsIteratorIterator<decltype(std::declval<T>().begin())>;
    iterator begin() { return { t.begin() }; };
    iterator end() { return { t.end() }; };
};

template<class T>
struct AsIteratorTmp : public T
{
    AsIteratorTmp(T&& t)
      : T{ std::move(t) } {};

    using iterator = AsIteratorIterator<decltype(std::declval<T>().begin())>;

    iterator begin() { return { T::begin() }; };
    iterator end() { return { T::end() }; };
};

template<class T>
AsIteratorRef<T>
operator|(T& t, AsIterator)
{
    return { t };
}
template<class T>
AsIteratorTmp<T>
operator|(T&& t, AsIterator)
{
    return std::move(t);
}
};