/*
 *
 */

namespace euler{



// Raises a to the power n
template <class T> T ipow(const T a, const int n)
{
  T ret = 1, N = n, b = a;
  while (N > 0)
  {
    if (N & 1)
      ret *= b;
    b *= b;
    N >>= 1;
  }
  return ret;
}



// Digit sum function
// Returns the sum of the xth powers of the digits of n.
// E.g. digit_sum(123) = 1 + 2 + 3
//      digit_sum(123,5) = 1^5 + 2^5 + 3^5
template <class T> T digit_sum(const T n, const int x = 1)
{
  T ret = 0, N = n, d = 0;

  while (N > 0)
  {
    d = N % ((T)10);
    ret += ipow(d, x);
    N /= (T)10;
  }

  return ret;
}



// Sum of divisors function. XXX: UNIMPLEMENTED
// Returns the sum of the xth powers of the positive integer divisors of n.
// E.g. divisor_sum(12) = 1 + 2 + 3 + 4 + 6 + 12
//      divisor_sum(12,2) = 1 + 4 + 9 + 16 + 36 + 144.
template <class T> T divisor_sum(const T n, const int x = 1)
{
  T ret = 0;
  
  // ...
  
  return ret;
}



// Sieve of Eratosthenes.
// Returns a list of all prime numbers less than or equal to the given bound.
// This function is templated such that it works for any integral type,
// int, unsigned char, boost::uint128_t, etc.
template <class T> typename std::enable_if<std::is_integral<T>::value, std::vector<T>>::type
prime_sieve(T bound)
{
  std::vector<bool> sieve(bound - 1, true);
  std::vector<T> ret;

  for (T i = 0; i < bound - 1; i++)
  {
    if (sieve[i])
    {
      T p = i + 2;
      ret.push_back(p);
      for (T j = i + p; j < bound - 1; j += p)
        sieve[j] = false;
    }
  }
  return ret;
}
} // namespace
