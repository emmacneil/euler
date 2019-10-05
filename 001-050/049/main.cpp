#include <iostream>

#include "../../include/primes.h"

using namespace std;

bool hasDigit(int n, const int d)
{
  while (n > 0)
  {
    if (n % 10 == d) return true;
    n /= 10;
  }
  return false;
}

bool arePermutations(const int A, const int B, const int C)
{
  int a = A, b = B, c = C;
  while (a > 0)
  {
    int d = a % 10;
    if (!hasDigit(b, d) || !hasDigit(c, d))
      return false;
    a /= 10;
  }

  a = A, b = B, c = C;
  while (b > 0)
  {
    int d = b % 10;
    if (!hasDigit(a, d) || !hasDigit(c, d))
      return false;
    b /= 10;
  }

  a = A, b = B, c = C;
  while (c > 0)
  {
    int d = c % 10;
    if (!hasDigit(b, d) || !hasDigit(a, d))
      return false;
    c /= 10;
  }

  return true;
}

int main (int argc, char* argv[])
{
  vector<int> primes;
  genPrimes(&primes, 10000);

  int start;
  for (start = 0; primes[start] < 1000; start++)
    continue;
  
  for (int i = start; i < primes.size(); i++)
  {
    for (int j = i + 1; j < primes.size(); j++)
    {
      int d = primes[j] - primes[i];
      int p = primes[j] + d;
      if (p < 10000)
        if (isPrime(p))
          if (arePermutations(primes[i], primes[j], p))
            cout << primes[i] << primes[j] << p << endl;
    }
  }
  
  return 0;
}
