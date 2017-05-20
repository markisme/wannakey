#include <set>

#include <wkey/bigint.h>
#include <wkey/search_primes.h>
#include <wkey/tools.h>

#define PALIGN 4
wkey::BigIntTy wkey::searchPrimes(uint8_t const* Data, size_t const Len, SetPrimes& Primes, BigIntTy const& N, const size_t PrimeSize)
{
  if (Len < PrimeSize) {
    return 0;
  }

  size_t const LenStop = ((Len - PrimeSize) / PALIGN) * PALIGN;
  uint8_t const* Block;
  for (size_t i = 0; i < LenStop; i += PALIGN) {
    Block = &Data[i];
    double E = normalizedEntropy(Block, PrimeSize);
    //printf("%0.4f\n", E);
    if (E >= 0.8) {
      // Checks whether we have a prime
      const auto P = getInteger(Block, PrimeSize);
      if (isPrime(P)) {
        if (Primes.insert(P).second) {
          printf("We found a new prime: %p!\n", Block);
          dumpHex("Prime", Block, PrimeSize);
          if (N % P == 0) {
            printf("PRIME FOUND: this prime divides N!\n");
            return P;
          }
        }
      }
    }
  }
  return 0;
}
