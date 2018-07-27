/* Project Euler - Problem 162
 * Hexadecimal Numbers
 *
 * A somewhat straightforward counting problem. We break the problem down to the level of counting
 * the number of n-digits hex numbers with exactly some number of 0's, 1's, and A's. Suppose x
 * digits are 0, y digits are 1, and z digits are A. There are n-1 places we can put the x 0's (it
 * cannot go in the leading position). Once x of them are placed, there remain n-x places to put
 * the 1's. Once they are placed too, there are n-x-y places to put the A's. Once they are placed,
 * there remain n-x-y-z digits that can take on any of the other 13 hex digits other than 0, 1,
 * and A. In all this gives us
 *
 *                   binom(n-1, x) * binom(n-x, y) * binom(n-x-y, z) * 13^(n-x-y-z)
 *
 * ways to arrange these numbers, where binom(n, k) is the binomial coefficient "n choose k".
 *   We use this formula to count the number of n-digit numbers with at least one of each of 0, 1,
 * and A. Afterwards, we can do the count for numbers with *at most* n digits.
 *   Runs almost instantaneously.
 */

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;



const int MAX_DIGITS = 16;
unsigned long binom_memo[MAX_DIGITS+1][MAX_DIGITS+1];
unsigned long pow13[MAX_DIGITS+1];



// Returns the binomial coefficient "n choose k"
// Overflow errors occur when n > 20 (assuming 64-bit longs).
// We are only using n <= 16.
unsigned long binom(int n, int k)
{
  if (k < 0) return 0;
  if (k > n) return 0;
  if ( (n == 0) && (k == 0) ) return 1;
  if (binom_memo[n][k] > 0) return binom_memo[n][k];
  unsigned long ret = 0UL;
  ret = binom(n - 1, k - 1) + binom(n - 1, k);
  binom_memo[n][k] = ret;
  return ret;
}



// Brute force algorithm to count the number of n-digit hex numbers with 0 1 A each occurring at
// least once. Runs in under a second for n <= 6 and in about 2 to 3 minutes for n = 8.
// This was used to get a list of expected values to verify the actual solution on small inputs.
unsigned long bf(int n)
{
  unsigned long start = 1UL << (4*(n - 1));
  unsigned long end = (1UL << (4*n)) - 1UL;
  unsigned long ret = 0UL;

  cout << hex << "Iterating from " << start << " to " << end << "." << dec << endl;
  
  for (unsigned long i = start; i <= end; i++)
  {
    bool found0 = false;
    bool found1 = false;
    bool foundA = false;
    unsigned long x = i;
    while (x > 0)
    {
      unsigned long d = x & 0xf;
      found0 |= (d == 0x0);
      found1 |= (d == 0x1);
      foundA |= (d == 0xA);
      x >>= 4;
    }
    if (found0 && found1 && foundA)
    {
      // cout << hex << i << dec << endl;
      ret++;
    }
  }
  return ret;
}



// Returns the number of n-digit hexadecimal numbers (no leading zeroes) with exactly
// x 0's, y 1's, and z A's. 
unsigned long f(int n, int x, int y, int z)
{
  if (n < 3) return 0UL;
  return binom(n-1, x) *
         binom(n-x, y) *
         binom(n-x-y, z) *
         pow13[n-x-y-z];
}



// Returns the number of n-digit hexadecimal numbers (no leading zeroes) with at least one of each
// of 0, 1, and A. 
unsigned long f(int n)
{
  unsigned long ret = 0UL;
  
  for (int x = 1; x <= n - 2; x++)
  {
    for (int y = 1; y <= n - 1 - x; y++)
    {
      for (int z = 1; z <= n - x - y; z++)
      {
        ret += f(n, x, y, z);
      }
    }
  } 
  
  return ret;
}



// Returns the number of hexadecimal numbers with at most n digits and with at least one of each
// of 0, 1, and A. 
unsigned long solve(int n)
{
  unsigned long ret = 0UL;
  
  for (int i = 0; i <= n; i++)
    ret += f(i);
  
  return ret;
}



int main(int argc, char * argv[])
{
  int N = 16;
  if (argc == 2)
    N = atoi(argv[1]);
  if (N > MAX_DIGITS)
  {
    cout << "Resizing input to " << MAX_DIGITS << "." << endl;
    N = MAX_DIGITS;
  }

  // Precompute powers of 13.
  pow13[0] = 1UL;
  for (int i = 1; i <= MAX_DIGITS; i++)
    pow13[i] = pow13[i-1] * 13UL;

  // Solve the problem.
  unsigned long solution = solve(N);
  
  // Output in decimal and hexadeximal.  
  cout << "dec: " << solution << endl;
  cout << hex << "hex: " << solution << dec << endl;
  
  return 0;
}

