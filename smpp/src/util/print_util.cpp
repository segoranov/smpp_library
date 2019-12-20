#include "util/print_util.h"

#include <algorithm>
#include <iomanip>

namespace smpp::print_util {
void printStringAsHex(const std::string& str, std::ostream& os) {
  os << std::hex;
  std::for_each(str.begin(), str.end(), [&os](char c) {
    os << "0x" << std::setfill('0') << std::setw(2) << static_cast<int>(c) << " ";
  });
}
}  // namespace smpp::print_util