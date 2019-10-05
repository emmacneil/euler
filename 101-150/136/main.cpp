/**
 * Project Euler - Problem 136
 * Singleton Differences
 *
 * The same code as from problem 135, except the constants were changed.
 */

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;



const int N = 50000000;
const int TARGET = 1;

int n_solutions[N] = {0};



// Returns x^2 - y^2 - z^2 where z, y, x form an arithmetic progression,
// differing by a -- i.e., y = z + a, x = y + a
long f(long z, long a)
{
  long n = (a + z) * (3 * a - z);
  // if (n == 20)
  //   printf("%ld - %ld - %ld = %ld\n", (z+2*a)*(z+2*a), (z+a)*(z+a), z*z, n);
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
