/*
 * Project Euler - Problem 407
 * Idempotents
 *
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

const long BOUND = 10000000;
const bool OUTPUT = true;

int M[BOUND+1] = {0};
int largestFactor[BOUND+1] = {0};
vector<int> primes;



int getLargestFactor(const int N)
{
  int rootn = sqrt(N);
  int n = N, p = 0, pk;
  for (int i = 0; p <= rootn; i++)
  {
    p = primes[i];
    if (N % p == 0)
    {
      pk = 1;
      while (n % p == 0)
      {
        pk *= p;
	n /= p;
      }
      largestFactor[N] = max(largestFactor[N/pk], pk);
      return largestFactor[N];
    }
  }
  largestFactor[N] = N;
  return largestFactor[N];
}



int solve(int n)
{
  int pk = getLargestFactor(n);
  if (pk == n) return 1;

  long a;
  int  m = n - pk;
  while (m > 0)
  {
    a = m + 1;
    if ( (a*a) % n == a ) return a;
    
    a = m;
    if ( (a*a) % n == a ) return a;

    m -= pk;
  }

  return 0;
}



int main()
{
  int p;
  long n;

  if (OUTPUT) cout << "BOUND = " << BOUND << endl;

  if (OUTPUT) cout << "Generating primes" << endl;
  genPrimes(&primes, BOUND);

  if (OUTPUT) cout << "Factorizing" << endl;
  for (int i = 2; i <= BOUND; i++)
    getLargestFactor(i);

  if (OUTPUT) cout << "Solving" << endl;
  n = 0;
  for (int i = 2; i <= BOUND; i++)
    n += (M[i] = solve(i));

  cout << n << endl;

  return 0;
}
