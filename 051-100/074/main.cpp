/*
 * Project Euler - Problem 74
 * Digit Factorial Chains
 *
 * Just brute-force the solution, but memo-ize results so we don't recompute
 * the same values over and over again.
 */

#include <iostream>

using namespace std;

const int MAXVAL = 2177280;
int fact[10];
int *memo;



// Compute the digit-factorial of n
// i.e., the sum of the factorials of n's digits
int dfact(int n)
{
  if (n == 0)
    return 1;

  int m = 0;
  while (n > 0)
  {
    m += fact[n % 10];
    n /= 10;
  }
  return m;
}



// Computes the length of the digit factorial chain of n
// i.e., the number of unique terms that appear when repeatedly taking the
//       digit factorial of n
int chain(int n, int depth)
{
  //cout << "chain(" << n << ")" << endl; cout.flush();
  if (memo[n])
    return memo[n];
  if (depth > 60) // Make sure we don't recurse too deeply
    return depth;

  int d = dfact(n);
  memo[n] = 1 + chain(d, depth+1);
  return memo[n];
}



int main()
{
  // Compute the factorials of single-digit numbers
  fact[0] = 1;
  for (int i = 1; i < 10; i++)
    fact[i] = i * fact[i-1];

  // Initialize memoization array
  memo = new int[MAXVAL + 1];
  for (int i = 0; i <= MAXVAL; i++)
    memo[i] = 0;

  // Initialize a few values given in the problem description
  memo[169] = memo[363601] = memo[1454] = 3;
  memo[871] = memo[45361] = 2;
  memo[872] = memo[45362] = 2;
  memo[145] = 1;
  memo[0] = 2;
  memo[1] = 1;
  memo[2] = 1;
  memo[40585] = 1; // 4! + 0! + 5! + 8! + 5! = 40585

  // Solve
  int n = 0;
  for (int i = 1; i < 1000000; i++)
  {
    if (chain(i, 0) == 60)
      n++;
  }
  
  // Output
  cout << n << endl;

  // Clean up
  delete[] memo;
}
