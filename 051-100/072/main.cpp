/*
 * Project Euler - Problem 72
 * Counting Fractions
 *
 * Just compute the Euler phi function for each integer from 2 to 1,000,000.
 */

#include <iostream>
#include <cmath>

using namespace std;

int phi[1000001] = {0};

int eulerphi(int n)
{
  if (n == 1)
    return 1;
  if (phi[n])
    return phi[n];

  const int SQRT_N = sqrt(n);
  int a = n, e = 0, m = 1;
  for (int i = 2; i <= SQRT_N; i++)
  {
    if (n % i == 0)
    {
      while (n % i == 0)
      {
        n /= i;
	e++;
      }
      for (int k = 1; k < e; k++)
        m *= i;
      m *= (i - 1);
      phi[a] = m * eulerphi(n);
      return phi[a];
    }
  }

  phi[n] = n - 1;
  return n - 1;
}

int main()
{
  long n = 0;
  for (int i = 2; i <= 1000000; i++)
    n += eulerphi(i);

  cout << n << endl;

  return 0;
}
