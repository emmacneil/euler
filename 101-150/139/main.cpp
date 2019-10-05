/**
 * Project Euler - Problem 139
 * Pythagorean Tiles
 *
 * Generate all primitive Pythagorean triples, (a, b, c). The area of the
 * square is simply c^2. The combined area of the four triangles is 2ab. The
 * area of the inner area is c^2 - 2ab. Check if the square root of the inner
 * area divides the length of the larger square, c. If so, then count this
 * triple and all multiples of this triple as long as
 * k(a + b + c) < 100,000,000. There are 1,000,000/(a + b + c) such multiples.
 */

#include <cmath>
#include <iostream>

using namespace std;



const bool OUTPUT        = false;
const int  MAX_PERIMETER = 100000000;



int gcd(int a, int b)
{
  if (a < b)  return gcd(b, a);
  if (b == 0) return a;
  return gcd(b, a % b);
}



// The commented-out portion reflects the algorithm described in the header
// and produces the solution. Running it showed that all triangles that
// work had the additional property that |a-b| = 1. This appears to be a
// sufficient condition, as checking for it instead produces the same results.
bool solve(long a, long b, long c)
{
  if (a > b) return solve(b, a, c);
  else       return (b - a) == 1;
/*
  long A, sqrt_A;

  A = c * c - (2 * a * b);
  sqrt_A = (long)sqrt(A);

  return ( (c * c) % sqrt_A ) == 0;
*/
}



int main(int argc, char * argv[])
{
  int a, b, c, count = 0;
  
  // Generate Pythagorean triples. If m > 50,000,000, then no triangle produced
  // by it will have a perimeter lesser than 100,000,000.
  for (int m = 2; 2 * m < MAX_PERIMETER; m++)
  {
    // If n is exceeds this value, then the perimeter of the produced
    // triangle will exceed 100,000,000.
    int n_end = MAX_PERIMETER / (2 * m) - m;
    n_end = n_end > m ? m : n_end;
    
    for (int n = 1; n < n_end; n++)
    {
      //cout << "(m = " << m << ", n = " << n << ")" << endl;
      // m and n must be relatively prime and not both odd.
      if ( ((m % 2) == (n % 2)) || (gcd(m, n) > 1) )
        continue;

      a = m*m - n*n;
      b = 2*m*n;
      c = m*m + n*n;

      //cout << "(" << a << "," << b << "," << c << ")" << endl;
      if (solve(a, b, c))
      {
        if (OUTPUT)
	  cout << "(" << a << "," << b << "," << c << ")" << endl;
        count += MAX_PERIMETER / (a + b + c);
      }
    }
  }
  
  cout << count << endl;

  return 0;
}
