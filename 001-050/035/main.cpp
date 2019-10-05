#include <ctime>
#include <iostream>
#include <cmath>

#include "../primes.h"

using namespace std;



bool isCircPrime(const int N)
{
  if (!isPrime(N))
    return false;

  // Get magnitude of N;
  int n = N, mag = 1;
  while (n > 9)
  {
    n /= 10;
    mag *= 10;
  }
  n = mag*(N % 10) + (N / 10);

  while (n != N)
  {
    if (!isPrime(n))
      return false;
    n = mag*(n % 10) + (n / 10);
  }

  return true;
}



int main (int argc, char* argv[])
{
  //vector<int> primes;
  const int BOUND = 1000000;

  //genPrimes(&primes, sqrt(BOUND));

  cout << endl;
  // Calculate...
  int n = 0;
  for (int i = 1; i < BOUND; i++)
  {
    if (isCircPrime(i))
    {
      cout << i << ", ";
      cout.flush();
      n++;
    }
  }

  cout << endl << n << endl;

  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
