/**
 * Project Euler - Problem 134
 * Prime Pair Connection
 *
 * Given two conscutive prime numbers, 5 < p < q, we need to find the smallest
 * natural number S whose last digits are p and which is divisible by q. In
 * other words, if we let d be the number of digits in p, then we need to find
 * the smallest
 *
 *                        S = k(10^d) + p = 0   (mod q)
 *
 * We know d, p, and q in this expression, so we just need to find k.
 *
 *                      k = (q - p)(10^d)^(-1)   (mod q)
 *
 * This hinges on finding the multiplicative inverse of 10^d modulo q. By
 * Euler's Theorem, this is just (10^d)^(q-2) and we use fast modular
 * exponentiation to compute this value.
 */

#include <iostream>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

// const int  MAX_P  = 102;
const int  MAX_P  = 1000004;
const bool OUTPUT = false;



long solve(long p, long q, long offset)
{
  long k, offset_inv;

  offset_inv = fastmodpow(offset, q - 2, q);
  k = (offset_inv * (q - p)) % q;

  return offset * k + p;
}



int main(int argc, char * argv[])
{
  vector<int> primes;
  long p, q, S, sum = 0, offset = 10;

  genPrimes(&primes, MAX_P);

  // Starting at primes[2] = 5
  for (int i = 2; i < primes.size() - 1; i++)
  {
    p = primes[i];
    q = primes[i + 1];
    if (p > offset)
      offset *= 10;
    S = solve(p, q, offset);
    if (OUTPUT)
      cout << "p = " << p << ", q = " << q << ", S = " << S << endl;
    sum += S;
  }

  cout << sum << endl;

  return 0;
}
