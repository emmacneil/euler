/*
 * Project Euler - Problem 94
 * Almost Equilateral Triangles
 *
 * An "almost equilateral" triangle is also an isosceles triangle. The formula
 * for the area of an isosceles triangle is
 *
 *                         A = (b/4) sqrt(4a^2 - b^2)
 *
 * where b is the length of the base of the triangle, and a is the length of
 * the other two sides. In order for this to be an integer, 4a^2 - b^2 must
 * firstly be perfect square, otherwise our area is not even a rational number.
 * Then we multiply the its square root by b and check that the result is
 * divisible by 4.
 *   The numbers of the form 4a^2 - b^2 that are perfect squares can be found
 * by the following means:
 *   If b = a + 1, then 4a^2 - b^2 = 4a^2 - (a+1)^2 follows the sequence
 *
 *                     0, 7, 20, 39, 64, 95, ...
 *
 * for a = 1, 2, 3.... Notice that the difference between terms is 7, 13, 19,
 * 23..., which grows linearly. This sequence can be easily computed, and each
 * term can be compared to a sequence of square numbers.
 *   If b = a - 1, then 4a^2 - b^2 = 4a^2 - (a-1)^2 follows the sequence
 *
 *                   15, 32, 55, 84, 119, 160, ...
 *
 * for a = 2, 3, 4... (a = 1, b = 0 is not a triangle)
 */


#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

const bool OUTPUT = false;
const int BOUND = 1000000000;
const float EPS = 1.0e-7f;

int main()
{
  long a, d, n = 0, sq, x;
  
  // Find the pairs (a, a+1) such that 4a^2 - (a+1)^2 is a square
  a = 1;
  d = 7;
  x = 0;
  sq = 1;
  while (3 * a + 1 < BOUND)
  {
    while (sq * sq < x)
      sq++;
    if (sq * sq == x)
      if ( (sq*(a+1)) % 4 == 0)
      {
        n += a + a + a + 1;
	if (OUTPUT)
	  printf("(%ld,%ld,%ld)\n",a,a,a+1);
      }
    
    x += d;
    d += 6;
    a++;

    //printf("\n");
  }

  // Find the pairs (a+1, a) such that 4(a+1)^2 - a^2 is a square
  a = 2;
  d = 17;
  x = 15;
  sq = 1;
  while (3 * a - 1 < BOUND)
  {
    while (sq * sq < x)
      sq++;
    if (sq * sq == x)
      if ( (sq*(a-1)) % 4 == 0)
      {
        n += a + a + a - 1;
	if (OUTPUT)
	  printf("(%ld,%ld,%ld)\n",a,a,a-1);
      }
    x += d;
    d += 6;
    a++;
  }

  cout << n << endl;

  return 0;
}
