#include <ctime>
#include <iostream>
#include <map>

#include "../../include/primes.h"

using namespace std;

map<int, int> M;
int g_sum = 0;

void truncl(const int n, const int deg)
{
  if (!isPrime(n)) return;

  M[n] = 1;

  for (int i = 1; i < 10; i++)
  {
    truncl(n + (deg*10*i), deg*10);
  }
}

void truncr(const int n)
{
  if (!isPrime(n)) return;

  if (M[n] == 1)
    if (n > 10)
      g_sum += n;

  for (int i = 1; i < 10; i++)
  {
    truncr(n*10 + i);
  }
}

int truncl(const int n) { truncl(n, 1); }

int main (int argc, char* argv[])
{
  // Calculate...
  truncl(3); truncl(5); truncl(7);
  //cout << "Map size " << M.size() << endl;
  truncr(2); truncr(3); truncr(5); truncr(7);

  cout << g_sum << endl;
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
