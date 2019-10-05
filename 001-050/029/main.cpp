/*
 * Project Euler - Problem 29
 * Distinct Powers
 *
 * For each value of a that is itself the power of some smaller integer m, we
 * rewrite a^b so that it is to the base m. So if a = m^n, then a^n = m^nb.
 *   Our bases and exponents are all small enough to fit in 16 bits, so we take
 * m and nb, store them in the first and last 16 bits of a 32-bit integer,
 * respectively, and add this value to a map. After going through all 100
 * values of a and b, we count the keys in our map.
 */

#include <ctime>
#include <iostream>
#include <map>

using namespace std;

map<int, int> gMap;


// Returns the smallest n such that n to some power equals N.
int factor(const int N)
{
  int n;

  for (int i = 2; i < N; i++)
  {
    n = N;
    if (n % i == 0)
    {
      while (n % i == 0) n /= i;
      if (n == 1)        return i;
    }
  }
  return N;
}



// Returns the number x, such that m^x = n
// Assumes such a number exists
int exp(const int M, const int N)
{
  int m = M, e = 1;
  while (m != N)
  {
    m *= M;
    e++;
  }
  return e;
}



void add(const int base, const int exponent)
{
  int n = (base << 16) + exponent;
  gMap[n] = 1;
}



int main (int argc, char* argv[])
{
  // Calculate...
  for (int a = 2; a <= 100; a++)
  {
    int f = factor(a);
    int e = exp(f, a);
    for (int b = 2; b <= 100; b++)
    {
      add(f, e*b);
    }
  }
  
  int n = gMap.size();
  cout << n << endl;
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
