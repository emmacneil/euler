/**
 * Project Euler - Problem 141
 * Investigating Progressive Numbers, n, which are also Square
 *
 * We are dividing n into n = qd + r and 0 <= r < d. Without loss of
 * generality, we may assume d < q, so that 0 <= r < d < q. r, d, q are
 * consecutive terms in a geometric series, so d = r(a/b), q = r(a/b)^2, for
 * some rational number a/b. For this series to be increasing as necessary, we
 * require a > b. We may also assume a/b is in lowest terms, so that
 * gcd(a, b) = 1. For q = r(a/b)^2 to be an integer, we need b^2 to divide q
 * and we can rewrite r = kb^2, d = kab, q = ka^2, for some integer k. We then
 * get
 *
 *                            n = kb(ka^3 + b).
 *
 * The solution is then merely a matter of iterating over all values of k, a,
 * and b satisfying these conditions:
 *
 *    i)   a > b
 *    ii)  gcd(a, b) = 1
 *    iii) kb(ka^3 + b) < 10^12
 *    iv)  kb(ka^3 + b) is a perfect square.
 *
 * The final condition can be easily tested by precomputing squares in an array
 * and doing a binary search. 
 *
 * Compiled with -O3 optimization, this runs in under 2 seconds.
 */



#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;

const unsigned long BOUND = 1000000000000UL;
const unsigned long RT_BOUND = 1000000UL;



// Vector of precomputed squares.
// Testing if a number is square is just a binary search on this vector.
vector<unsigned long> squares(RT_BOUND+1);



// Greated common divisor.
unsigned long gcd(unsigned long a, unsigned long b)
{
  if (b == 0) return a;
  if (a < b) return gcd(b, a);
  return gcd(b, a % b);
}



// Computes and returns the solution based on the predefined BOUND constant
unsigned long solve()
{
  unsigned long m = 0;

  // Try every combination of k, a, b satisfying
  //  * a > b
  //  * gcd(a, b) = 1
  //  * kb(ka^3 + b) < BOUND
  for (unsigned long b = 1; ; b++)
  {
    // Given that n = kb(ka^3 + b), we stop when setting a = b + 1, k = 1 will
    // result in a number larger than BOUND
    if ( b*(b*b*b + 3*b*b + 4*b + 1) >= BOUND)
      break;
    
    for (unsigned long a = b + 1; ; a++)
    {
      if (b*(a*a*a+b) >= BOUND)
        break;
      
      if (gcd(a, b) > 1)
        continue;
      
      for (unsigned long k = 1; ; k++)
      {
        unsigned long n = k*b*(k*a*a*a+b);

        // Make sure n is within bounds
        if (n >= BOUND)
	  break;
	
	// Make sure n is square
	if (binary_search(squares.begin(), squares.end(), n))
  	{
	  //cout << n << endl;
	  m += n;
	}
      } // for k
    } // for a
  } // for b

  return m;
}



int main(int argc, char * argv[])
{
  // Precompute all square numbers less than BOUND
  for (unsigned long i = 0; i <= RT_BOUND; i++)
    squares[i] = i * i;
  
  // Print solution
  cout << solve() << endl;
  
  return 0;
}
