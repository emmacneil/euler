#include <iostream>
#include "../../include/primes.h"

using namespace std;



const int BOUND = 1000000;



int main (int argc, char* argv[])
{
  // Calculate...
  vector<int> primes;
  genPrimes(&primes, BOUND);
  vector<int> arr(primes);

  int nTerms = 2;
  int p = 0;
  while (arr[0] < BOUND)
  {
    bool found = false;
    for (int i = 0; i + nTerms - 1 < arr.size(); i++)
    {
      arr[i] += primes[i + nTerms - 1];
      if (!found && arr[i] < BOUND && isPrime(arr[i]))
      {
        p = arr[i];
        found = true;
      }
    }
    nTerms++;
  }

  cout << p << endl;

  return 0;
}
