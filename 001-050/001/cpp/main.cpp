/* Project Euler - Problem 001
 * Multiples of 3 and 5
 *
 * Let F(n, k) be the sum of all positive multiples of k less than n. Then
 *
 *                                    F(n, k) = kT((n - 1)/k)
 *
 * where T(n) denotes the n-th triangular number. The solution is to compute
 *
 *                            F(1000, 3) + F(1000, 5) - F(1000, 15).
 */

#include <cstdlib>
#include <iostream>



/* Returns the n-th triangular number, n(n + 1)/2. */
int T(int n)
{
  return (n*(n + 1ul)) >> 1;
}



/* Returns the sum of all positive multiples of k less than n, via the formula
 * F(n, k) = k*T((n-1)/k). */
int F(int n, int k)
{
  return k*T((n - 1ul)/k);
}



int main(int argc, char * argv[])
{
  int sum, n = 1000;
  if (argc == 2)
    n = atoi(argv[1]);
  sum = F(n, 3) + F(n, 5) - F(n, 15);
  std::cout << sum << std::endl;
  return 0;
}
