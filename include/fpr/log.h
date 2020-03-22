#pragma once

#include <functional>
#include <ostream>

namespace fpr {
using namespace std;
namespace log {

/**
 * The default logger. 
 * Automatic newline at the end.
 */
struct DefaultLogger {
    static bool should_print();
    static ostream &get_os();
    static void prefix(ostream &os);
    static void postfix(ostream &os);
};

/**
 * Combines multiple loggers into one. 
 * should_print() -> bool: Will print if all Loggers return true.
 * get_os() -> ostream &: The Left most Logger's get_os() will be used.
 * prefix(ostream&os) -> Called from left to right.
 * postfix(ostream &os) -> Called from left to right.
 * @tparam Combined 
 * @tparam Loggers 
 */
template <class Combined, class... Loggers>
struct Logger {
    inline static bool should_print() { return Combined::should_print(); }
    inline static ostream &get_os() { return Combined::get_os(); };
    inline static void prefix(ostream &os) { Combined::prefix(os); }
    inline static void postfix(ostream &os) { Combined::postfix(os); }
};

/**
 * Logger's requirements:
 * should_print() -> bool: Return true if log should be outputted.
 * get_os() -> ostream &: Output destination.
 * prefix(ostream&os) -> Called before printer is called.
 * postfix(ostream &os) -> Called after printer is called.
 * @tparam Combined 
 * @tparam ToBeCombined 
 * @tparam Tail 
 */
template <class Combined, class ToBeCombined, class... Tail>
struct Logger<Combined, ToBeCombined, Tail...> {
    inline static bool should_print() {
        return Combined::should_print() && Logger<ToBeCombined, Tail...>::should_print();
    }
    inline static ostream &get_os() { return Combined::get_os(); };
    inline static void prefix(ostream &os) {
        Combined::prefix(os);
        Logger<ToBeCombined, Tail...>::prefix(os);
    }
    inline static void postfix(ostream &os) {
        Combined::postfix(os);
        Logger<ToBeCombined, Tail...>::postfix(os);
    }
};

/** The indent tracker */
struct Indent {
    static bool should_print();
    static ostream &get_os();
    static void prefix(ostream &os);
    static void postfix(ostream &os);

    /** Current indent */
    static uint indent;
    /** Increases indent */
    static void inc();
    /** Decreases indent */
    static void dec();

  private:
    static const string &indent_str();
};

/**
 * @tparam DefaultLogger Logger to be used.
 * @param printer Printer to be used.
 */
template <class Logger = DefaultLogger>
inline void log(function<void(ostream &)> printer = [](ostream &) {}) {
    if (!Logger::should_print()) {
        return;
    }
    auto &os{Logger::get_os()};
    Logger::prefix(os);
    printer(os);
    Logger::postfix(os);
}

}; // namespace log
} // namespace fpr