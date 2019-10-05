/**
 * Project Euler - Problem 127
 * abc-hits
 *
 * A few observations:
 *
 *   (i)   If c = a + b, then gcd(a, b) = gcd(a, c) = gcd(b, c) -- we don't
 *         need to compute three gcd's; they are always equal.
 *   (ii)  If a, b, c are relatively prime, then
 *
 *                            rad(abc) = rad(a)rad(b)rad(c),
 *
 *         so we can precompute rad(n) for all 1 <= n < 120000 and keep it in
 *         RAM, multplying them as needed.
 *   (iii) Rather than computing the gcd for every a, b, it is faster to
 *         precompute which b's are relatively prime with a using a sieve
 *         method.
 *
 *   First we generate all primes less than 120,000. Then we use a sieve method
 * to compute rad(n) and the prime divisors of n for all 1 <= n < 120,000. The
 * algorithm to find abc-hits is as follows
 *
 *   (i)   a can be at most 60,000 (since a < b and a + b < 120,000) so we
 *         iterate over all 1 <= a <= 60,000.
 *   (ii)  For each a, we precompute all b relatively prime with a using a
 *         sieve method and taking advantage of our precomputed prime factors
 *         of a.
 *   (iii) For each b relatively prime with a such that a + b < 120,000, we
 *         check if rad(a)rad(b)rad(a + b) < a + b.
 *   (iv)  If so, we add a + b to a running sum.
 *   (v)   After iterating over all a, return that sum.
 */

#include <iostream>
#include <vector>
#include <set>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;



const int BOUND = 120000;

vector<long> rad(BOUND, 1);
vector<int>  prime_factors[BOUND];
vector<int>  primes;



// Precompute the prime factors of n and rad(n), filling the rad[] and
// prime_factors[][] arrays.
void rad_sieve()
{
  int p;

  genPrimes(&primes, BOUND);

  for (int i = 0; i < primes.size(); i++)
  {
    p = primes[i];
    for (int k = p; k < BOUND; k += p)
    {
      rad[k] *= p;
      prime_factors[k].push_back(p);
    }
  }
}



// The hard work is done here.
long solve()
{
  long c, sum = 0;

  for (int a = 1; a < BOUND/2; a++)
  {
    // Sieve method to precompute all b relatively prime with a
    vector<bool> rel_prime(BOUND+1, true);
    for (int p : prime_factors[a])
      for (int k = a + p; a + k < BOUND; k += p)
        rel_prime[k] = false;
    
    // For each b > a such that b + a < 120,000
    for (int b = a + 1; a + b < BOUND; b++)
    {
      c = a + b;
      // If gcd(a,b) = 1 and rad(abc) < c
      if ( (rel_prime[b]) && (rad[a] * rad[b] * rad[c] < c) )
        sum += c;
    }
  }

  return sum;
}



int main(int argc, char * argv[])
{
  rad_sieve();

  cout << solve() << endl;

  return 0;
}
