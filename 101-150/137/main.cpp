/**
 * Project Euler - Problem 137
 * Fibonacci Golden Nuggets
 *
 * We have a polynomial
 *
 *        p(x) = F_1 x + F_2 x^2 + F_3 x^3 + ...
 *             = sum from k = 1 to infty of F_k x^k
 *             = (1 / sqrt 5) sum from k = 1 to infty of (a^k - b^k)x^k
 *
 * where a = (1 + sqrt 5)/2 and b = (1 - sqrt 5)/2. This comes from the closed
 * form expression of the Fibonacci numbers. We can split the infinite sum into
 * two sums, and as long as x < a, both sums converge.
 *
 *        p(x) =   (1 / sqrt 5) sum from k = 1 to infty of (ax)^k
 *               - (1 / sqrt 5) sum from k = 1 to infty of (bx)^k
 *             =   (1 / sqrt 5)(1 / (1 - ax)) - (1 / sqrt 5)(1 / (1 - bx))
 *             =   (1 / sqrt 5)[ 1 / (1 - ax) - 1 / (1 - bx) ]
 *             =   (1 / sqrt 5) x(a - b)/((1 - ax)(1 - bx))
 *             =   (1 / sqrt 5) (x sqrt 5) / (1 - x - x^2)
 *             =   x / (1 - x - x^2)
 *
 *   Since we are looking for rational values of x, let x = r/s and define
 *
 *                   p(r, s) = (r/s) / (1 - (r/s) - (r/s)^2)
 *                           = rs / (s^2 - rs - r^2)
 *
 * It was found by inspection that p(r, s) produces integral values when r < s
 * are consecutive terms in the Fibonnaci sequence, that it is a positive
 * integer when r is an even-indexed term (F_2, F_4, ...), and that if m < n,
 * then
 *
 *                   p(F_2m, F_(2m+1)) < p(F_2n, F_(2n+1))
 *
 */

#include <iostream>

using namespace std;

const int TARGET = 15;
const int N_FIBS = 2 * TARGET + 2;
long fib[N_FIBS];

long p(long r, long s)
{
  return (r*s) / (s*s - r*s - r*r);
}

int main(int argc, char * argv[])
{
  fib[0] = 0; fib[1] = 1;
  for (int i = 2; i < N_FIBS; i++)
    fib[i] = fib[i-1] + fib[i-2];

  long r = fib[N_FIBS-2], s = fib[N_FIBS-1];
  cout << p(r, s) << endl;

  return 0;
}
