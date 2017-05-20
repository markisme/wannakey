#ifndef WKEY_BIGINT_H
#define WKEY_BIGINT_H

#include <vector>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>


// Use boost::multiprecision for big int handling. It has the advantage to be
// header-only and saves us the pain of supporting third-party libraries within
// windows...

namespace wkey {

typedef boost::multiprecision::cpp_int BigIntTy;

void writeIntegerToFile(FILE* f, BigIntTy const& N, uint32_t padSize);
BigIntTy mulInv(BigIntTy a, BigIntTy b);
BigIntTy getInteger(uint8_t const* const Data, size_t const Len);
std::vector<uint8_t> getDataFromInteger(BigIntTy const& N);

static bool isPrime(BigIntTy const& n)
{
  return boost::multiprecision::miller_rabin_test(n, 40);
}

static bool isPrime(uint8_t const* const Data, size_t const Len)
{
  const auto n = getInteger(Data, Len);
  return isPrime(n);
}

} // wkey

#endif
