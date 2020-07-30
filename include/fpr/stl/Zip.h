#include <utility>
#include <vector>

namespace fpr {
template<class L, class R>
struct ZippedRef
{
    L& l;
    R& r;

    using LItr = decltype(l.begin());
    using RItr = decltype(r.begin());

    struct iterator
    {
        LItr l;
        RItr r;

        using value_type =
          std::pair<typename LItr::value_type&, typename RItr::value_type&>;

        value_type operator*() { return { *l, *r }; };

        bool operator==(const iterator& rhs) const { return l == rhs.l; }
        bool operator!=(const iterator& rhs) const { return !(*this == rhs); }

        iterator& operator++()
        {
            l++;
            r++;
            return *this;
        };
    };

    iterator begin() { return { l.begin(), r.begin() }; };
    iterator end() { return { l.end(), r.end() }; };
};

template<class L, class R>
ZippedRef<L, R>
zip(L& l, R& r)
{
    return { l, r };
}
};