/**
 * Project Euler - Problem 130
 * Composites with Prime Repunit Property
 *
 * Just a simple modification of the code from problem 129. The 25'th n such
 * that n is composite and (p-1)|A(n) turns out to be small enough that a brute
 * force approach is still sufficient.
 */

#include <iostream>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

const int TARGET = 25;



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
  int hits = 0, an, n = 2, sum = 0;;

  // Repeat until we find the 25'th composite with the "prime property"
  while (hits < TARGET)
  {
    // If gcd(10, n) = 1
    if ( (n % 2) && (n % 5) )
    {
      // Get A(n)
      an = A(n);

      // If (n - 1) divides A(n)
      if ((n - 1) % an == 0)
      {
        // And if n is composite
        if (!isPrime(n))
	{
	  hits++;   // count it as a "hit"
	  sum += n; // and add n to out sum
	}
      }
    }
    n++; // Increase n
  }
  
  // Output result.
  cout << sum << endl;
  
  return 0;
}
