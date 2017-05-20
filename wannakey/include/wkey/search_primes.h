#ifndef WKEY_SEARCH_PRIMES_H
#define WKEY_SEARCH_PRIMES_H

#include <cstdint>
#include <set>

#include <wkey/bigint.h>

namespace wkey {

typedef std::set<BigIntTy> SetPrimes;
BigIntTy searchPrimes(uint8_t const* Data, size_t const Len, SetPrimes& Primes, BigIntTy const& N, const size_t PrimeSize);

} // wkey

#endif
