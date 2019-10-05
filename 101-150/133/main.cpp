/**
 * Project Euler - Problem 133
 * Repunit non-factors
 *
 * If a prime number p divides R(10^n), then A(p) divides 10^n, as seen in
 * problem 132. Conversely, if A(p) does not divide 10^n, then p does not
 * divide R(10^n). So for every prime p < 100,000, we check if its prime
 * factorization is (2^a)(5^b). If so, it may divide R(10^n). IF not, it does
 * not divide R(10^n).
 */

#include <iostream>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

const int MAX_PRIME = 100000;



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



// Returns true if n divides 10^n for some n, or equivalently, if n is of the
// form n = 2^a 5^b, for some a >= 0, b >= 0
bool divides10n(int n)
{
  while (n % 2 == 0)
    n /= 2;
  while (n % 5 == 0)
    n /= 5;
  return n == 1;
}



int main(int argc, char * argv[])
{
  int sum = 0;
  vector<int> primes;
  
  genPrimes(&primes, MAX_PRIME);
  
  for (int p : primes)
    if ( (p <= 5) || (!divides10n(A(p))) )
      sum += p;
  
  cout << sum << endl;
  
  return 0;
}
