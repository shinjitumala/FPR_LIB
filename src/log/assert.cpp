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

void my_assert(
    bool cond,
    const string cond_str,
    function<void()> action = []() {},
    function<void()> crash = []() {},
    experimental::source_location location = experimental::source_location::current()) {
    if (cond) {
        return;
    }
    log::log<log::Logger<ansicc::Red, log::Indent>>([&](ostream &unused) {
        cerr << "Assertion Failure: " << cond_str << ", ";
        print_location(location, cerr);
        cerr << endl;
    });
    log::Indent::inc();
    action();
    log::Indent::dec();
    cerr << endl;

    crash();
}
} // namespace fpr