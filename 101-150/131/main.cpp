/**
 * Project Euler - Problem 131
 * Prime Cube Partnership
 *
 * We have the equation n^3 + n^2 p = m^3, which can be rewritten as
 * 
 *   n*n*(n + p) = m^3
 *
 * The key insight is that both n and (n + p) must be perfect cubes. What's
 * more, they must be consecutive cubes. Suppose (n + p) = b^3 and
 * n = a^3. Then p = b^3 - a^3.
 *
 *                      n + p = b^3
 *                          p = b^3 - n
 *                            = b^3 - a^3
 *                            = (b - a)(b^2 + ba + a^2)
 *
 * So p is divisible by (b - a) and can only be prime if b - a = 1
 */

#include <cstdio>
#include <iostream>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

const bool OUTPUT  = false;
const long BOUND   = 1000000;

int main(int argc, char * argv[])
{
  long a = 1;
  long b = 2;
  long aaa = a * a * a;
  long bbb = b * b * b;
  long n = 0;
  long p = bbb - aaa;

  while (p < BOUND)
  {
    if (isPrime(p))
    {
      if (OUTPUT)
        cout << "p = " << p << ",   n = " << aaa << endl;
      n++;
    }
    a++;
    b++;
    aaa = a * a * a;
    bbb = b * b * b;
    p = bbb - aaa;
  }

  cout << n << endl;

  return 0;
}
