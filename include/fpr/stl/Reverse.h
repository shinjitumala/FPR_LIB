#include <iterator>
#include <type_traits>

namespace fpr {
class Reverse
{};
constexpr Reverse reverse;

/// Reverse an stl container with ease. Ranges v3 asap pls
/// @tparam T
template<class T>
struct ReverseWrapper
{
    using Contained = std::remove_reference_t<T>;
    using ContainedIterator = typename Contained::iterator;

    ReverseWrapper(Contained& t)
      : t{ &t }
    {}

    Contained* const t;

    /// Reversed iterator
    struct iterator : public ContainedIterator
    {
        /// Replace it so that it returns the previous value.
        /// @return decltype(T::iterator::operator*())
        typename ContainedIterator::value_type operator*()
        {
            ContainedIterator temp{ *this };
            --temp;
            return *temp;
        }

        /// Replace operator-- with operator++
        /// @return iterator&
        iterator& operator++()
        {
            ContainedIterator::operator--();
            return *this;
        }
    };

    constexpr iterator begin() { return iterator{ t->end() }; };
    constexpr iterator end() { return iterator{ t->begin() }; };
};

// template<class T>
// struct ReverseWrapper
// {
//     T& container;
//     auto begin() { return std::rbegin(container); }
//     auto end() { return std::rend(container); }
// };

template<class T>
// Reversed<T>
ReverseWrapper<std::remove_reference_t<T>> constexpr
operator|(T&& t, Reverse)
{
    return { t };
}
}