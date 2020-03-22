#include <iostream>

#include <fpr/log.h>

namespace fpr::log {

string indent_string_internal{""};

bool DefaultLogger::should_print() { return true; };
ostream &DefaultLogger::get_os() { return cout; };
void DefaultLogger::prefix(ostream &os){};
void DefaultLogger::postfix(ostream &os) { os << "\n"; };

bool Indent::should_print() { return true; };
ostream &Indent::get_os() { return cout; };
void Indent::prefix(ostream &os) {
    os << indent_string_internal;
}
void Indent::postfix(ostream &os){};

uint Indent::indent{0U};
const string one_indent{"    "};
const string &Indent::indent_str() {
    return indent_string_internal;
}
void Indent::inc() {
    indent++;
    indent_string_internal += one_indent;
}
void Indent::dec() {
    indent--;
    indent_string_internal.erase(indent_string_internal.end() - one_indent.length(), indent_string_internal.end());
}
} // namespace fpr::log