#pragma once
#include <streambuf>

namespace fpr {
/// This class is used to turn a filedescriptor to a C++ ifstream.
class fdstreambuf : public std::streambuf
{
    /// Alias for convenience
    using traits_type = std::streambuf::traits_type;

    /// Buffer size for both input and output.
    static const int bufsize{ 1024 };
    /// Output buffer
    char output_buf[bufsize];
    /// Input buffer
    char input_buf[bufsize + 16 - sizeof(int)];
    /// Filedescriptor this is mapped to.
    int file_descriptor;

  public:
    /// @param file_descriptor The file_descriptor this will be representing.
    /// NOTE: Ownership of the filedescriptor is taken.
    fdstreambuf(int&& file_descriptor);
    /// Closes the file_descriptor
    ~fdstreambuf();

  protected:
    int overflow(int c);
    int underflow();
    int sync();
};
}