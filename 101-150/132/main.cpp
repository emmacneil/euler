/**
 * Project Euler - Problem 132
 * Large Repunit Factors
 *
 * Another modification to the solution for problem 129. We have
 *
 * A(n) = min { k : n|R(k) }
 *
 * Observe also that if n divides R(k), then n divides R(2k), R(3k), etc.
 * n divides R(ck) for all positive natural numbers c.
 *   Let p be prime. Let A(p) = k. Then p divides R(k). Suppose k dvides 10^9.
 * Then 10^9 = ck for some integer c > 0. Since p divides R(k), p divides
 * R(ck) = R(10^9) and we a have a basis for a solution to this problem.
 *   For every prime p > 5 (so that gcd(10, p) = 1, and since 3 does not divide
 * R(10^9)), check if A(p) divides 10^9. If so, add it to our sum and stop
 * after we've found 40 such primes.
 */

#include <iostream>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

const int N_FACTORS = 40;
const int MAX_PRIME = 1000000;
const int TARGET = 1000000000;



// Assumes gcd(10, n) = 1.
// If gcd(10, n) != 1, then this may enter an infinite loop.
int A(int n)
{
  // Start with one term in our sum,
  // sum = m^k = 10^0 = 1
  int k = 0;
  int m = 1;
  int sum = 1;

  // Keep adding powers of 10 modulo n to sum, until sum is a multiple of n.
  while (sum != 0)
  {
    k++;
    m = (10 * m) % n;
    sum = (sum + m) % n;
  }
  
  return k + 1;
}



int main(int argc, char * argv[])
{
  int a, sum = 0, n_factors = 0;
  vector<int> primes;
  
  genPrimes(&primes, MAX_PRIME);

  // For each prime p
  for (int p : primes)
  {
    // If gcd(p, 10) = 1
    if (p > 5)
    {
      // Get A(p)
      a = A(p);

      // If A(p) divides 10^9 ...
      if (TARGET % a == 0)
      {
        // ... then p divides R(10^9)
        n_factors++;
        sum += p;
        if (n_factors == N_FACTORS)
          break;
      }
    }
  }

  cout << sum << endl;

  return 0;
}
