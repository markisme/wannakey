#ifndef WKEY_TOOLS_H
#define WKEY_TOOLS_H

#include <vector>
#include <system_error>

namespace wkey {

void dumpHex(const char* Name, uint8_t const* Data, size_t const Len);
double normalizedEntropy(uint8_t const* Data, const size_t Len);
std::vector<uint8_t> readFile(const char* path, std::error_code& EC);
bool fileHasString(const char* path, const char* str);

std::error_code getLastEC();
std::string getLastErrorMsg();
std::error_code getLastErrno();

} // wkey

#endif WKEY_TOOLS_H
