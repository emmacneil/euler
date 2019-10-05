/**
 * Project Euler - Problem 120
 * Square Remainders
 *
 * IF we take powers of (a-1)^n modulo a^2, eventually we will get 1. The next
 * power results in (a-1) again. Likewise for powers of (a+1)^n. For each a, we
 * repeatedly raise (a-1) and (a+1) to the next power until they both reach 1.
 * Then we know that we have gotten all distinct sums of powers. Raising again
 * to the next power repeats the sequence.
 */

#include <iostream>

using namespace std;



int solve(int a)
{
  int aa = a * a; // a^2
  int b  = a - 1; // (a-1)^n
  int c  = a + 1; // (a+1)^n
  int r = 0;      // remainder
  int rmax = 0;   // maximum remainder
  
  while ( (b != 1) || (c != 1) )
  {
    r = (b + c) % aa;           // Get remainder of [(a-1)^n + (a+1)^n] / a^2
    rmax = r > rmax ? r : rmax; // Compare it to the largest remainder so far
    b *= a - 1; b %= aa;        // Get the next power of (a-1)^n modulo a^2
    c *= a + 1; c %= aa;        // Get the next power of (a+1)^n modulo a^2
  }

  return rmax;
}



int main(int argc, char * argv[])
{
  int n = 0;
  for (int a = 3; a <= 1000; a++)
    n += solve(a);
  cout << n << endl;

  return 0;
}
