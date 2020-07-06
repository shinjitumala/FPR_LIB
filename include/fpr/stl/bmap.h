#pragma once
#include <unordered_map>
namespace fpr {
using namespace std;
/// Bidirectional map.
/// @tparam F First
/// @tparam S Second
template<class F, class S>
class bmap
{
    /// Map from a to b.
    unordered_map<F, S> forward;
    /// Map from b to a.
    unordered_map<S, F> backward;

  public:
    using FMap = decltype(forward);
    using iterator = typename FMap::iterator;
    using value_type = typename FMap::value_type;
    using size_type = typename FMap::size_type;

  public:
    /// Same as insert but bidirectional.
    /// @param v
    /// @return pair<iterator, bool>
    pair<iterator, bool> insert(const value_type& v);
    /// Same as count.
    /// @param f
    /// @return size_type
    size_type fcount(F f) const;
    /// Same as count but backwards.
    /// @param s
    /// @return size_type
    size_type scount(S s) const;
    /// Same as at.
    /// @param f
    /// @return const S&
    const S& fat(const F& f) const;
    /// Same as at but backwards.
    /// @param s
    /// @return const S&
    const F& sat(const S& s) const;
};

template<class F, class S>
pair<typename bmap<F, S>::iterator, bool>
bmap<F, S>::insert(const value_type& v)
{
    backward.insert({ v.second, v.first });
    return forward.insert(v);
}

template<class F, class S>
typename bmap<F, S>::size_type
bmap<F, S>::fcount(F f) const
{
    return forward.count(f);
}

template<class F, class S>
typename bmap<F, S>::size_type
bmap<F, S>::scount(S s) const
{
    return backward.count(s);
}

template<class F, class S>
const S&
bmap<F, S>::fat(const F& f) const
{
    return forward.at(f);
}

template<class F, class S>
const F&
bmap<F, S>::sat(const S& s) const
{
    return backward.at(s);
}
};