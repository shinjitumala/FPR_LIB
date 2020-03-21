#include <iostream>

#include <fpr/log.h>

namespace fpr::log {
uint indent{0U};
void increase_indent() {
    indent++;
}
void decrease_indent() {
    indent--;
}
const string indent_str{"  "};

bool DefaultLogger::should_print() { return true; };
ostream &DefaultLogger::get_os() { return cout; };
void DefaultLogger::prefix(ostream &os){};
void DefaultLogger::postfix(ostream &os) { os << "\n"; };

bool Indent::should_print() { return true; };
ostream &Indent::get_os() { return cout; };
void Indent::prefix(ostream &os) {
    for (auto i{0U}; i < indent; i++) {
        os << indent_str;
    }
}
void Indent::postfix(ostream &os){};
} // namespace fpr::log