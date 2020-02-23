#pragma once

#include <FPR/out/color.h>
#include <type_traits>
#include <vector>

namespace fpr {
/** Base class for logging */
class log : private aout {
  public:
    enum class type : u_char;
    static constexpr u_char lvl_max{32};
    enum class lvl : u_char {
        MSG,
        ERR,
        WRN,
        INF,
    };

  private:
    static std::vector<bool> t;
    static lvl l;

    static u_char indent;
    static u_char i;

    bool print;

  public:
    log(
        lvl l,
        ansicc cc,
        std::ostream &out = std::cout,
        type t = static_cast<type>(lvl_max - 1));
    log(const log &) = delete;
    /**
     * @tparam O 
     * @tparam std::enable_if_t<ostreamable<O>::v> 
     * @param o 
     * @return aout& 
     */
    template <class O, class = std::enable_if_t<ostreamable<O>::v>>
    log &operator<<(O o) {
        if (print) {
            os << o;
        }
        return *this;
    }

    using omanip = std::ostream &(&)(std::ostream &);
    log &operator<<(omanip o) {
        if (print) {
            os << o;
        }
        return *this;
    };

    /**
     * Increase Indent
     */
    static void ii();
    /**
     * Decrease Indent
     */
    static void di();
};

#ifndef NDEBUG
#define err(msg)                          \
    fpr::log(                             \
        fpr::log::lvl::ERR,               \
        fpr::ansicc{                      \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Color::RED,      \
            fpr::ansicc::Emphasis::NONE}, \
        std::cerr)                        \
        << msg
#define wrn(msg)                          \
    fpr::log(                             \
        fpr::log::lvl::WRN,               \
        fpr::ansicc{                      \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Color::YELLOW,   \
            fpr::ansicc::Emphasis::NONE}, \
        std::cerr)                        \
        << msg
#define out(msg)                          \
    fpr::log(                             \
        fpr::log::lvl::INF,               \
        fpr::ansicc{                      \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Emphasis::NONE}, \
        std::cerr)                        \
        << msg
#define grn(msg)                          \
    fpr::log(                             \
        fpr::log::lvl::INF,               \
        fpr::ansicc{                      \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Color::GREEN,    \
            fpr::ansicc::Emphasis::NONE}, \
        std::cerr)                        \
        << msg
#define blu(msg)                          \
    fpr::log(                             \
        fpr::log::lvl::INF,               \
        fpr::ansicc{                      \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Color::BLUE,     \
            fpr::ansicc::Emphasis::NONE}, \
        std::cerr)                        \
        << msg
#define mag(msg)                          \
    fpr::log(                             \
        fpr::log::lvl::INF,               \
        fpr::ansicc{                      \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Color::MAGENTA,  \
            fpr::ansicc::Emphasis::NONE}, \
        std::cerr)                        \
        << msg
#define cyn(msg)                          \
    fpr::log(                             \
        fpr::log::lvl::INF,               \
        fpr::ansicc{                      \
            fpr::ansicc::Color::NONE,     \
            fpr::ansicc::Color::CYAN,     \
            fpr::ansicc::Emphasis::NONE}, \
        std::cerr                         \
            << msg)
#else
#define err(msg)
#define wrn(msg)
#define out(msg)
#define grn(msg)
#define blu(msg)
#define mag(msg)
#define cyn(msg)
#endif
}; // namespace fpr