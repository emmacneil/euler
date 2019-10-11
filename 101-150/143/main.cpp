/* Project Euler - Problem 143
 * Investigating the Torricelli Point of a Triangle
 *
 * This problem is simplified somewhat by the fact that the angles CTB, BTA, and ATC are each 120
 * degrees. Thus, the side length a is determined uniquely by (q, r). Likewise, b and c are
 * functions of (p, q) and (p, r), respectively.
 *   The solution is to iterate over all triples (p, q, r) satisfying
 *
 *   0 < p <= q <= r
 *   p + q + r <= 120,000
 *
 * and compute the side lengths (a, b, c). Compute b immediately after choosing p and q, and if
 * b is not an integer, continue on to the next choice of q. This saves time iterating over all
 * the possible values of r. After computing (a, b, c) we check if a and c are also integral,
 * then make sure the triangle (a, b, c) has all interior angles less than 120 degrees. If all
 * checks are passed, add p + q + r to a set, then compute the sum of the set after all Torricelli
 * triangles have been generated.
 *   When compiled with -O3, this runs in approximately 30 seconds on an Intel Core i5-7200U
 * at 2.5GHz.
 */

#include <cmath>
#include <cstdint>
#include <iostream>
#include <set>

using namespace std;



uint32_t isqrt(uint64_t n)
{
  return (uint32_t)sqrt((double)n);
}

// Computes the side length of the triangle side defined by the interior lengths i1 and i2.
// E.g. if i1 and i2 are p and q, then this returns the length of b.
// Returns 0 if the result is not integral.
// Otherwise returns a positive integer.
uint32_t side_length(uint64_t i1, uint64_t i2)
{
  uint64_t ss = i1*i1 + (i2 + i1)*i2;
  uint64_t s = isqrt(ss);
  return s*s == ss ? (uint32_t)s : 0;
}

// Returns true if the triangle with side lengths is valid.
// A triangle is valid if it has no internal angle >= 120'
bool valid(double a, double b, double c)
{
  double A = acos((b*b + c*c - a*a)/(2.0*b*c));
  double B = acos((a*a + c*c - b*b)/(2.0*a*c));
  double C = acos((a*a + b*b - c*c)/(2.0*a*b));
  return ((A < 120.0) && (B < 120.0) && (C < 120.0));
}


int main(int argc, char * argv[])
{
  uint32_t BOUND = 120000, count = 0, sum = 0, a, b, c;
  set<uint32_t> S;
  
  if (argc == 2)
    BOUND = atoi(argv[1]);
  
  for (uint32_t p = 1; p <= BOUND; p++)
  {
    for (uint32_t q = p; p + q <= BOUND; q++)
    {
      if (!(b = side_length(p, q)))
        continue;

      for (uint32_t r = q; p + q + r <= BOUND; r++)
      {
        if (!(c = side_length(p, r)))
          continue;
        if (!(a = side_length(q, r)))
          continue;
        
        // Ensure triangle abc has no angle >= 120'
        if (!valid(a, b, c))
          continue;
        
        count++;
        S.insert(p + q + r);
      }
    }
  }
  
  for (uint32_t n : S)
    sum += n;
  
  cout << "Found " << count << " Toricelli triangles" << endl;
  cout << "and " << S.size() << " distinct values of p + q + r." << endl;
  cout << "Solution: " << sum << endl;
  
  return 0;
}

