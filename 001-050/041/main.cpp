#include <iostream>
#include <vector>

#include "../../include/pandigital.h"
#include "../../include/primes.h"

using namespace std;

int main (int argc, char* argv[])
{
  // Calculations
  vector<int> primes;
  genPrimes(&primes, 10000000);
  int sz = primes.size();
  int i;

  for (i = sz - 1; i >= 0; i--)
  {
    if (isPandigital(primes[i], 7))
    {
      cout << primes[i] << endl;
      break;
    }
  }
  
  // Output
  

  return 0;
}
