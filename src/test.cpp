#include <chrono>
#include <experimental/source_location>
#include <fpr/log/LineCallbackBuf.h>
#include <fpr/log/Location.h>
#include <fpr/log/ansicc.h>
#include <fpr/log/callback/Indent.h>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace fpr;
using namespace log;
using namespace ansi;

struct time_callback
{
    int call(streambuf& a)
    {
        auto time{ chrono::system_clock::to_time_t(
          chrono::system_clock::now()) };
        stringstream ss;
        ss << put_time(localtime(&time), "%X");
        string output{ ss.str() };
        return a.sputn(output.c_str(), output.size());
    };
};

#define asrt(cond, action)                                                     \
    if (auto loc = experimental::source_location::current(); !cond) {          \
        using namespace fpr::log;                                              \
        cerr << loc;                                                           \
        action;                                                                \
        ::exit(1);                                                             \
    }

int
main(void)
{
    Indent ind{};
    time_callback tc;
    CombinedCallback cb{ ind, tc };
    LineCallbackBuf a{ cerr, cb };
    ostream hage{ &a };

    //     repeat(10000, [&]() {
    hage << "apple\nbanana\ncat\n";
    Magenta.print(hage);
    ind.inc();
    hage << "haha\n";
    ind.dec();
    auto blnk{ Colorizer<Color::BLUE, Color::NONE, Effect::UNDERLINE>{} };
    ind.inc();
    ind.inc();
    blnk.print(hage);
    hage << "IBLINK\n";
    Reset::print(hage);
    asrt(0, cout << "message before error." << endl;);
}