/**
 * Project Euler - Problem 119
 * Digit Power Sum
 *
 * I assumed that the 30'th element in the sequence {a_n} would be lesser than
 * 2^64. In that case, a_30's digit sum would be less than 172, since a_30 has
 * at most 19 digits in base 10 (19 * 9 = 171).
 *   Iterate over all 1 < n < 172 and get all powers of n less than 2^64. If
 * the digit sum of some n^k is equal to n, then add it to a list. Sort the
 * list to get the sequence {a_n}.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

unsigned int digit_sum(const unsigned long n)
{
  unsigned long m = n, s = 0;
  while (m > 0)
  {
    s += m % 10;
    m /= 10;
  }
  return s;
}

int main(int argc, char * argv[])
{
  unsigned long m, n;
  vector<unsigned long> a;
  
  for (n = 2; n <= 171; n++)
  {
    // Iterate over all powers of n.
    // If their digit sum is n, add them to a[].

    m = 1;
    while (m * n > m) // while (m*n) does not cause an overflow
    {
      m *= n;
      if (digit_sum(m) == n && m > 9)
        a.push_back(m);
    }
  }
  
  sort(a.begin(), a.end());

  // Output the 30'th element of the sequence.
  cout << a[29] << endl;

  return 0;
}
