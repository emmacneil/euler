#include <cstdio>
#include <iostream>
#include <vector>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;



const int  MAX_P  = 10000; // Do not generate prime numbers beyond this value.
const bool OUTPUT = false;

bool **lookup;



// Concatenate two integers
// e.g.: concat(31, 107) = 31107
int concat(int a, int b)
{
  int n = b;
  while (n > 0)
  {
    a *= 10;
    n /= 10;
  }
  return a + b;
}



// Returns true if concatenating the i'th prime number and the j'th prime
// number would yield another prime number
bool concatable(int i, int j)
{
  return lookup[i][j] && lookup[j][i];
}



int main()
{
  int nPrimes;
  int m = 0x7fffffff;
  int setsum = 0;
  vector<int> primes;
  
  genPrimes(&primes, MAX_P);
  nPrimes = primes.size();

  // Build lookup table
  lookup = new bool*[nPrimes];
  for (int i = 0; i < nPrimes; i++)
  {
    lookup[i] = new bool[nPrimes];
    for (int j = 0; j < nPrimes; j++)
    {
      if (i == j)
        lookup[i][j] = true;
      else
        lookup[i][j] = isPrime(concat(primes[i], primes[j]));
    }
  }

  if (OUTPUT)
    cout << nPrimes << " primes less than " << MAX_P << endl;

  for (int a = 0; a < nPrimes; a++)
  {
    setsum += primes[a];
    
    for (int b = a+1; b < nPrimes && setsum < m; b++)
    {
      if (!concatable(a, b)) continue;
      setsum += primes[b];
      
      for (int c = b+1; c < nPrimes && setsum < m; c++)
      {
        if (!concatable(a, c) ||
	    !concatable(b, c)) continue;
        setsum += primes[c];
        
	for (int d = c+1; d < nPrimes && setsum < m; d++)
        {
          if (!concatable(a, d) ||
	      !concatable(b, d) ||
	      !concatable(c, d)) continue;
          setsum += primes[d];
          
	  for (int e = d+1; e < nPrimes && setsum < m; e++)
          {
            if (!concatable(a, e) ||
	        !concatable(b, e) ||
	        !concatable(c, e) ||
	        !concatable(d, e)) continue;
            setsum += primes[e];
	    
	    if (setsum < m)
	    {
	      if (OUTPUT)
	         printf("Found new smallest set: {%d,%d,%d,%d,%d}\n",
		        primes[a], primes[b], primes[c], primes[d], primes[e]);
	      m = setsum;
	    }
	    
	    setsum -= primes[e];
          }
          setsum -= primes[d];
        }
        setsum -= primes[c];
      }
      setsum -= primes[b];
    }
    setsum -= primes[a];
  }

  cout << m << endl;

  // Destroy lookup table
  for (int i = 0; i < nPrimes; i++)
    delete[] lookup[i];
  delete[] lookup;

  return 0;
}
