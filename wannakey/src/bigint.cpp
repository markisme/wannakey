#include <wkey/bigint.h>

namespace wkey {

// Thanks to wine for this!
void writeIntegerToFile(FILE* f, BigIntTy const& N, uint32_t padSize)
{
  auto NData = getDataFromInteger(N);
  // Padding with zeros
  NData.resize(padSize);
  if (fwrite(&NData[0], 1, NData.size(), f) != NData.size()) {
    std::cerr << "Error while writing!" << std::endl;
  }
}

// Adapted from https://rosettacode.org/wiki/Modular_inverse#C.2B.2B
BigIntTy mulInv(BigIntTy a, BigIntTy b)
{
  BigIntTy b0 = b, t, q;
  BigIntTy x0 = 0, x1 = 1;
  if (b == 1) return 1;
  while (a > 1) {
    q = a / b;
    t = b, b = a % b, a = t;
    t = x0, x0 = x1 - q * x0, x1 = t;
  }
  if (x1 < 0) x1 += b0;
  return x1;
}

BigIntTy getInteger(uint8_t const* const Data, size_t const Len)
{
  BigIntTy n;
  boost::multiprecision::import_bits(n,
      Data, Data + Len, 8, false);
  return n;
}

std::vector<uint8_t> getDataFromInteger(BigIntTy const& N)
{
  std::vector<uint8_t> Ret;
  boost::multiprecision::export_bits(N, std::back_inserter(Ret), 8, false);
  return Ret;
}

} // wkey
