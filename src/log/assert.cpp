#include <chrono>
#include <experimental/source_location>
#include <filesystem>
#include <functional>
#include <iostream>
#include <ostream>
#include <thread>

#include <sys/wait.h>
#include <unistd.h>

#include <fpr/log.h>
#include <fpr/log/ansicc.h>

namespace fpr {
using namespace std;
using namespace std::filesystem;

void print_location(const experimental::source_location &loc, ostream &os) {
    os << "Location: " << loc.file_name() << ":" << std::to_string(loc.line()) << ":" << std::to_string(loc.column()) << " " << loc.function_name() << "()";
};

struct ToCerr {
    static bool should_print() { return true; };
    static ostream &get_os() { return cerr; };
    static void prefix(ostream &os){};
    static void postfix(ostream &os){};
};

void do_if(
    bool cond,
    function<void()> action = []() {}) {
    if (cond) {
        return;
    }
    action();
}

void my_assert(
    bool cond,
    const string cond_str,
    function<void()> action = []() {},
    experimental::source_location location = experimental::source_location::current()) {
    do_if(cond, [&]() {
        log::log<log::Logger<ToCerr, ansicc::Red, log::Indent>>([&](ostream &os) {
            os << "Assertion Failure: " << cond_str << ", ";
            print_location(location, os);
            os << endl;
        });
        log::Indent::inc();
        action();
        log::Indent::dec();
        cerr.flush();
        ::abort();
    });
}

void my_warn(
    bool cond,
    const string cond_str,
    function<void()> action = []() {},
    experimental::source_location location = experimental::source_location::current()) {
    do_if(cond, [&]() {
        log::log<log::Logger<ToCerr, ansicc::Yellow, log::Indent>>([&](ostream &os) {
            os << "Warning: " << cond_str << ", ";
            print_location(location, os);
            os << endl;
        });
        log::Indent::inc();
        action();
        log::Indent::dec();
        cerr.flush();
    });
}
} // namespace fpr