/* Project Euler - Problem 146
 * Investigating a Prime Pattern
 *
 *   Here, we simply do a brute force search on all integers 1 <= n <= 150,000,000 and check which
 * ones satisfy the desired condition. This search is made feasible by using Rabin-Miller for
 * primality testing. Rabin-Miller is a probabilistic test, but can be made deterministic for all
 * n < 2^64 by testing over the first 12 primes as bases, which we do here.
 *   Some other observations include that n must be congruent to 0 modulo 10, cutting down on much
 * of the work. This means we also don't have to check if n^2 + 5, n^2 + 15, and n^2 + 25 are
 * prime, since they are certainly divisble by 5 if we search only over multiples of 10. Similary,
 * n^2 is congruent to 1 modulo 3, which means we need not test n^2 + 11, n^2 + 17, and n^2 + 23.
 * By also noticing that n^2 must be 2 modulo 7, and therefore n is 3 or 4 modulo 7, the algorithm
 * is now fast enough to run under one minute (approx 25 seconds).
 */



#include <cmath>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::uint128_t;
using namespace std;

const bool OUTPUT = true;



unsigned long long fmp(unsigned long long a, unsigned long long n, unsigned long long m)
{
  // 128-bit representation is needed here to avoid overflow.
  uint128_t ret = 1, A = a, N = n, M = m;

  while (N) {
    if (N & 1)
      ret = (ret * A) % M;
    N >>= 1;
    A = (A * A) % M;
  }
  
  return ret.convert_to<unsigned long long>();
}



// Rabin-Miller test
// Return true if n is (probably) prime.
bool prime(unsigned long long n)
{
  if (n < 2)         return false; // 0 and 1 aren't prime
  if (n == 2)        return true;  // 2 is prime
  if ( (n & 1) == 0) return false; // Even n other than 2 are not prime

  // n is odd, and greater than 2.
 
  // Set q and t such that n - 1 = 2^t*q with q odd.
  unsigned long long q = n - 1;
  unsigned long long t = 0;
  while ( (q & 1) == 0 ) {
    q >>= 1;
    t++;
  }

  // Rabin-Miller test is made deterministic for all 64-bit integers by
  // iterating over the first 12 primes as bases.
  unsigned long long arr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (unsigned long long a : arr) {
    if (n == a) return true;
    
    unsigned long long b = fmp(a, q, n);
    int e = 0;

    if (b == 1) continue;
    while ( (b != n - 1) && (e < t - 1) ) {
      b = fmp(b, 2, n);
      e++;
    }
    if (b != n - 1) return false;
  }
  return true;
}



int main(int argc, char * argv[])
{
  unsigned long long sum = 0;
  int hits = 0;

  for (unsigned long long n = 10; n < 150000000; n += 10)
  {
    if ( (n % 3 == 0) || (n % 13 == 0) ) continue;
    if ( (n % 7 != 3) && (n % 7 != 4) ) continue;
    unsigned long long nn = n * n;
    if ( ( prime(nn +  1)) &&
	 ( prime(nn +  3)) &&
//	 (!prime(nn +  5)) &&
	 ( prime(nn +  7)) &&
	 ( prime(nn +  9)) &&
//	 (!prime(nn + 11)) &&
	 ( prime(nn + 13)) &&
//	 (!prime(nn + 15)) &&
//	 (!prime(nn + 17)) &&
	 (!prime(nn + 19)) &&
	 (!prime(nn + 21)) &&
//	 (!prime(nn + 23)) &&
//	 (!prime(nn + 25)) &&
	 ( prime(nn + 27)) ) {
      if (OUTPUT)
        cout << "Match #" << ++hits << ": " << n << endl;
      sum += n;
    }
  }
  cout << sum << endl;

  return 0;
}
