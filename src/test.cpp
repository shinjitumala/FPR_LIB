#include <chrono>
#include <fpr/log.h>
#include <fpr/log/BufNewLine.h>
#include <fpr/log/ansicc.h>
#include <fpr/util/repeat.h>
#include <iostream>
#include <ratio>
#include <vector>

using namespace fpr;
using namespace std;

struct hoge
{
    int call(streambuf& a)
    {
        static const string indent{ "    " };
        static const size_t indent_size{ indent.size() };
        return a.sputn(indent.c_str(), indent_size);
    };
};
struct foo
{
    int call(streambuf& a)
    {
        static const string indent{ "penis" };
        static const size_t indent_size{ indent.size() };
        return a.sputn(indent.c_str(), indent_size);
    };
};

int
main(void)
{
    ulong standard;
    ulong news;
    ulong olds;
    {
        auto start{ chrono::high_resolution_clock::now() };
        repeat(10000, [&]() {
            cout << "    apple\n    banana\n    cat\n";
            cout << "    a\n    b\n    c\n";
        });
        auto end{ chrono::high_resolution_clock::now() };
        auto diff{ chrono::duration_cast<chrono::nanoseconds>(end - start) };
        standard = diff.count();
    }

    {
        auto start{ chrono::high_resolution_clock::now() };
        log::BufNewLine<log::CombinedCallback<hoge>> a{ cout };
        ostream hage{ &a };

        repeat(10000, [&]() {
            hage << "apple\nbanana\ncat\n";
            hage << "a\nb\nc";
        });
        auto end{ chrono::high_resolution_clock::now() };
        auto diff{ chrono::duration_cast<chrono::nanoseconds>(end - start) };
        news = diff.count();
    }

    {
        using fuck = log::Logger<log::Indent>;
        log::Indent::inc();
        auto start{ chrono::high_resolution_clock::now() };
        repeat(10000, [&]() {
            log::log<fuck>([](ostream& os) { os << "apple\n"; });
            log::log<fuck>([](ostream& os) { os << "banana\n"; });
            log::log<fuck>([](ostream& os) { os << "cat\n"; });
            log::log<fuck>([](ostream& os) { os << "a\n"; });
            log::log<fuck>([](ostream& os) { os << "b\n"; });
            log::log<fuck>([](ostream& os) { os << "c\n"; });
        });
        auto end{ chrono::high_resolution_clock::now() };
        auto diff{ chrono::duration_cast<chrono::nanoseconds>(end - start) };
        olds = diff.count();
    }
    cout << standard << endl;
    cerr << news << " x" << (float)news / standard << endl;
    cerr << olds << " x" << (float)olds / standard << endl;
}