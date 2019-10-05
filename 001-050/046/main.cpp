#include <ctime>
#include <iostream>
#include <cmath>
#include "../primes.h"

using namespace std;

bool f(const int N)
{
  int n, m;
  for (int p = 2; p < N; p++)
  {
    if (!isPrime(p)) continue;
    n = N - p;
    if (n % 2 == 1) continue; // n is not divisible by 2
    n /= 2;
    m = sqrt(n);
    if (m * m == n) return true;
  }
  return false;
}

int main (int argc, char* argv[])
{
  // Calculate...
  int n = 9; // smallest odd composite
  while (true)
  {
    if (!isPrime(n))
      if (!f(n)) break;

    n += 2;
  }
  
  if (!isPrime(9)) cout << "9 is not prime" << endl;
  cout << n << endl;

  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
