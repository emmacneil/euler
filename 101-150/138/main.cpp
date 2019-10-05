/**
 * Project Euler - Problem 138
 * Special Isoceles Triangles
 *
 * We use an algorithm to generate all Pythagorean triples with particular
 * properties. If m > n are positive integers, exactly one being even, then
 * (x, y, z) with
 *
 *                               x = m^2 - n^2
 *                               y = 2mn
 *                               z = m^2 + n^2
 *
 * is a primitive Pythagorean triple. We construct an isoceles triangle with
 * base b = 2y, height h = x, and "legs" l = z. Note that if the base was
 * formed by x instead, both b and h would be even so we can't get the
 * condition h = b +/- 1. Neither could we get this condition if (x, y, z)
 * weren't primitive.
 *   It is too time-consuming to exhaustively try all m, n. We need to satisfy
 *
 *                          b = h +/- 1
 *                         2y = x +/- 1
 *                        4mn = m^2 - n^2 +/- 1,
 *
 * so we approximate this to n^2 - 4mn - m^2 = 0, use the quadratic equation to
 * solve for n = (sqrt 5 - 2) and for a fixed m, we try all values
 *
 *         floor (sqrt 5 - 2) - 1  <=  n  <=  ceil (sqrt 5 - 2) + 1,
 *
 * a very tight range.
 */

#include <cmath>
#include <iostream>

using namespace std;

const int TARGET = 12;



int main(int argc, char * argv[])
{
  const double X = sqrt(5.0) - 2.0;

  long sum = 0; // Sum of the 12 triangle "legs"
  long c   = 0; // Number of special triangles discovered. Stop at 12.
  long b, h, l; // Triangle dimensions.
  long d;       // Difference between b and h.

  // Try all values of m, n as described in the header.
  for (long m = 2; c < TARGET; m++)
  {
    long start = (long)(m*X - 1.0);
    long end   = start + 2;
    for (long n = start; n <= end; n++)
    {
      // Exactly one of m, n must be even.
      if ((n % 2) == (m % 2)) 
        continue;

      // Get isoceles triangle dimensions
      h = m*m - n*n;
      b = 4*m*n;
      l = m*m+n*n;

      // If b = h +/- 1
      d = b - h;
      if ( (d == 1) || (d == -1) )
      {
        sum += l; // At triangle leg length to the total sum.
	c++;      // Increment the number of triangles found.
      }
    }
  }

  // Output result.
  cout << sum << endl;

  return 0;
}
