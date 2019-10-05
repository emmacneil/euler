/**
 * Project Euler - Problem 129
 * Repunit Divisibility
 *
 * A simple brute force solution. We have
 *
 *                     R(n) = 10^0 + 10^1 + ... + 10^(n-1)
 *
 * and
 *
 *                          A(n) = min { k : k|R(n) }
 *
 * So for A(n), we want the smallest k such that
 *
 *                   10^0 + 10^1 + ... + 10^{k-1} = 0 (mod n)
 *
 * So we add powers of 10 modulo n to a running sum (also modulo n) and return
 * the largest exponent needed, plus 1.
 *   The brute force search can be made quicker by recognizing that A(n) <= n.
 * So if A(n) > 1,000,000, then n > 1,000,000 and we can start our search at
 * n = 1,000,001. The search is too slow otherwise.
 */

#include <iostream>

using namespace std;

const int TARGET = 1000000;



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
  int n = TARGET;
  
  while (n++)                 // For each n,
    if ( (n % 2) && (n % 5) ) // if gcd(10, n) = 1
      if (A(n) > TARGET)      // and A(n) > 1,000,000,
        break;                // stop
  
  cout << n << endl;          // and report solution
  
  return 0;
}
