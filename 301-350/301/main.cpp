/*
 * Project Euler - Problem 301
 * Nim
 *
 * The function X described in the problem statement is
 *
 *                 X(a,b,c) = 0  if  a XOR b XOR c = 0
 *                            1  if  a XOR b XOR c > 0
 *
 * So X(1,2,3) = 0 because
 *
 *                                  00000001
 *                              XOR 00000010
 *                              XOR 00000011
 *                                  --------
 *                                  00000000
 *
 * But X(3,6,9) = 1 because
 *
 *                                  00000011
 *                              XOR 00000110
 *                              XOR 00001001
 *                                  --------
 *                                  00001100
 *
 * In general, X(n,2n,3n) = 0 if n's binary representation does not contain
 * adjacent 1's. This problem appears to have a dynamic programming solution.
 * Consider the number of solutions in which the greatest bit that is 'on' is
 * 2^5. That is, the number of solutions in the form 001XXXXX in binary. The
 * first X must be a zero, and the number of remaining solutions is just the
 * number of solutions in which the greatest 'on' bit is 2^3, plus of course
 * the solution in which all the X's are zeroes.
 *   So we get the following recurrence relation: let f(m) be the number of
 * positive integers 2^m <= n < 2^{m+1} such that X(n,2n,3n) = 0. Then,
 *
 *                        f(0) = 1
 *                        f(1) = 1
 *                        f(m) = 1 + sum_0^{m-2} f(i)
 *
 * But this function f(m) is in fact the m'th Fibonnaci number. The solution to
 * this problem, then, is just the sum of the first 30 Fibonacci numbers, plus 1
 * to account for the solution n = 2^30.
 */

#include <iostream>
#include <cstdlib>

using namespace std;

const bool OUTPUT = true;

int main(int argc, char *argv[])
{
  int a = 1, b = 1, n = 2;
  for (int i = 2; i < 30; i++)
  {
    b = a + b;
    a = b - a;
    n += b;
  }

  // Output an extra 1, because the above doesn't capture the solution n = 2^30
  cout << n + 1 << endl;
  
  return 0;
}
