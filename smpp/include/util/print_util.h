#ifndef PRINT_UTIL_H
#define PRIT_UTIL_H

#include <iostream>
#include <string>

namespace smpp::print_util {

void printStringAsHex(const std::string& str, std::ostream& os = std::cout);

}
#endif