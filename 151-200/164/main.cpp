/* Project Euler - Problem 164
 * Numbers for which No Three Consecutive Digits Have a Sum Greater than a Given Value
 *
 * Solution using dynamic programming and memoization. We need to compute the number of 20-digit
 * numbers n (without any leading zeroes) such that no three consecutive digits of n have a sum
 * greater than 9. Let f(n, a, b) be the number of n-digit numbers (possibly with leading zeroes)
 * beginning with the digits a and b such that no 3 consecutive digits have a sum greater than 9.
 * Our solution will be to compute f(20, a, b) for all 1 <= a <= 9 and 0 <= b <= 9 and add all
 * these together.
 *   To compute f, we first note that we must define f(n, a, b) = 0 if a < 0, b < 0, or a + b > 9.
 * Otherwise:
 *
 *                    f(n, a, b) = \sum_{c = 0}^{C} f(n - 1, b, c),
 *
 * where C = 10 - a - b. We also need a base case for the recursion:
 *
 *                                  f(3, a, b) = 10 - a - b,
 *
 * except, again, when a, b < 0 or a + b > 9. To speed up the computation, we memoize values of f
 * so that we do not recompute it for duplicate inputs.
 *   Runs in less than 10ms.
 */

#include <iostream>

using namespace std;

const int N_DIGITS = 20;

long memo[N_DIGITS][10][10] = {0};



// Returns the number of n-digit numbers whose first two digits are a and b for which no consecutive digits exceed 9.
// This allows for leading zeros, i.e. a may equal 0.
long f(int n, int a, int b)
{
  if (a + b > 9) return 0;
  if (a < 0) return 0;
  if (b < 0) return 0;
  if (n == 3) return 10 - a - b;
  
  // If result has already been memoized, return that result.
  if (memo[n][a][b] > 0)
    return memo[n][a][b];

  long ret = 0;
  int C = 10 - a - b;
  for (int c = 0; c < C; c++)
    ret += f(n - 1, b, c);
  memo[n][a][b] = ret;
  return ret;
}



// Returns the number of N-digit numbers (with no leading zeroes) for which no consecutive digits exceed 9.
long solve(int n)
{
  long ret = 0;

  for (int a = 1; a < 10; a++)
    for (int b = 0; b < 10 - a; b++)
      ret += f(n, a, b);

  return ret;
}



int main(int argc, char * argv[])
{
  long count = 0;

  cout << solve(N_DIGITS) << endl;

  return 0;
}

