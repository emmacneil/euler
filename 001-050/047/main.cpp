#include <iostream>

#include "../../include/factor.h"

using namespace std;

int main (int argc, char* argv[])
{
  // Calculate...
  int i;
  for (i = 2; ; i++)
    if (countPrimeFactors(i) == 4)
      if (countPrimeFactors(i+1) == 4)
        if (countPrimeFactors(i+2) == 4)
          if (countPrimeFactors(i+3) == 4)
            break;
  cout << i << endl;
  
  return 0;
}
