/**
 * Project Euler - Problem 135
 * Same Differences
 *
 * If x > y > z are an arithmetic progression, we can let y = z + a and
 * x = y + a and rewrite the equation x^2 - y^2 - x^2 = n in any of the
 * following ways:
 *
 *                      (z + 2a)^2 - (z + a)^2 + z^2 = n
 *                                  3a^2 + 2az - z^2 = n
 *                                   (a + z)(3a - z) = n
 *
 * The idea is to try to plug every z and a into this equation to get every n
 * with the form we are looking for, but we have to know when to stop.
 *   If we fix a, the equation gives us a concave down parabola. For each value
 * of a, then, we find where the parabola intercepts the z-axis and the line
 * n = 1,000,000.
 *
 *   (i)   For all a such that 4a^2 < N, n is never 1,000,000, so we test all z
 *           from 1 to the single positive z-intercept.
 *   (ii)  For all a such that 3a^2 < N < 4a^2, the parabola intercepts the
 *           line n = 1,000,000 at two points, say at z = A and z = B, A < B,
 *           and we try all z from 1 to A and from B to the z-intercept.
 *   (iii) For all a such that N < 3a^2, the first time the parabola intercepts
 *           the line n = 1,000,000 occurs for some negative z, so we try only
 *           the range from B to the z-intercept.
 *
 *   For each a, we test all z on the above ranges. Eventually, the slope of the
 * parabola at z = B will be so steep that it will skip over all values between
 * n = 1 and n = 1,000,000. At this point, we stop.
 */

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;



const int N = 1000000;
const int TARGET = 10;

int n_solutions[N] = {0};



// Returns x^2 - y^2 - z^2 where z, y, x form an arithmetic progression,
// differing by a -- i.e., y = z + a, x = y + a
long f(long z, long a)
{
  long n = (a + z) * (3 * a - z);
  //if (n == 1155)
  //  printf("%ld - %ld - %ld = %ld\n", (z+2*a)*(z+2*a), (z+a)*(z+a), z*z, n);
  return n;
}



// The derivative of f(z, a) with respect to z
long dfdz(long z, long a)
{
  return 2*(a - z);
}



void add_solution(int n)
{
  if ( (n > 0) && (n < N) )
    n_solutions[n]++;
}



int main(int argc, char * argv[])
{
  long a = 1;

  // For 4a^2 < N, f(a, z) never exceeds N, but reaches 0 at z = 3*a
  while (4*a*a < N)
  {
    for (long z = 1; z < 3 * a; z++)
      add_solution(f(z, a));

    a++;
  }

  // For 3a^2 < N < 4a^2, f(z, a) equals N twice. We try all z on two separate intervals
  // while (3 * a * a < N)
  while (true)
  {
    long rt, A, B;

    rt = sqrt(4*a*a - N);
    A = a - rt;
    B = a + rt;
    
    if (dfdz(B, a) < -N)
      break;
    
    for (long z = 1; z < A; z++)
      add_solution(f(z, a));
    for (long z = B; z < 3 * a; z++)
      add_solution(f(z, a));
    
    a++;
  }


  // Count up the amount of n with 10 solutions.
  int k = 0;
  for (int i = 0; i < N; i++)
    if (n_solutions[i] == TARGET)
      k++;

  cout << k << endl;

  return 0;
}
