/**
 * @file Colors.h
 * @author shinjitumala (funny.pig.run@gmail.com)
 * @version 0.1
 * @date 2020-02-22
 * 
 * @copyright Copyright (c) 2020
 * 
 * Provides macros for color printing
 */
#pragma once

#include <fpr/out/ansicc.h>

#include <iomanip>
#include <iostream>
#include <type_traits>
#include <utility>

namespace fpr {
/** SFINAE to check if a type has operand<< for std::ostream& */
template <class T>
class ostreamable {
    template <class U>
    static auto test(int) -> decltype(
        std::declval<std::ostream &>() << std::declval<U>(),
        std::true_type());
    template <class>
    static auto test(...) -> std::false_type;

  public:
    static constexpr bool v{std::is_same_v<decltype(test<T>(0)), std::true_type>};
};

/** ansicc out: Conveniece class for outputting colored text */
class aout {
  protected:
    std::ostream &os;

  public:
    /**
     * @param cc The color to be set
     * @param out 
     */
    aout(ansicc cc, std::ostream &out = std::cout);
    /** Disallow copy */
    aout(const aout &) = delete;
    ~aout();

    /**
     * @tparam O 
     * @tparam std::enable_if_t<ostreamable<O>::v> 
     * @param o 
     * @return aout& 
     */
    template <class O, class = std::enable_if_t<ostreamable<O>::v>>
    aout &operator<<(O o) {
        os << o;
        return *this;
    }

    using omanip = std::ostream &(&)(std::ostream &);
    aout &operator<<(omanip o) {
        os << o;
        return *this;
    };

    /** ansicc used to reset color of terminal */
    static const ansicc reset;
};
} // namespace fpr
