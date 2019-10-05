/*
 * Project Euler - Problem 73
 * Counting Fractions in a Range
 *
 * For a fixed d:
 * Let a/d be the smallest fraction greater than 1/3
 * Let b/d be the greatest fraction lesser than 1/2
 * Count the number of integers from a to b inclusive that are relatively prime
 * to d, and do this for every d from 5 to 12000
 */

#include <iostream>

using namespace std;

int gcd(int a, int b)
{
  if (a < b)
    return gcd(b, a);
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int main()
{
  double MIN = 1.0/3.0;
  double MAX = 1.0/2.0;
  int a = 2, b = 2, n = 0;
  for (int d = 5; d <= 12000; d++)
  {
    if ( (double)a / (double)d < MIN)
      a++;
    b++;
    if ( (double)b / (double)d > MAX)
      b--;
    for (int k = a; k <= b; k++)
      if (gcd(k, d) == 1)
        n++;
  }

  cout << n << endl;
  
  return 0;
}
