/*
 * Project Euler - Problem 87
 * Prime Power Triples
 */

#include <iostream>
#include <map>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

const int  BOUND = 50000000;
const int  MAX_P = 7071;
const int  MAX_Q = 368;
const int  MAX_R = 84;

map<int,bool> nmap;

int main()
{
  int m, p, q, r, len;
  vector<int> primes;
  
  genPrimes(&primes, 2*MAX_P);
  len = primes.size();
  
  for (int i = 0; primes[i] < MAX_P; i++)
  {
    p = primes[i];
    
    for (int j = 0; primes[j] < MAX_Q; j++)
    {
      q = primes[j];
      
      for (int k = 0; primes[k] < MAX_R; k++)
      {
        r = primes[k];
	m = p*p + q*q*q + r*r*r*r;
	if (m < BOUND)
	  nmap[m] = true;
      }
    }
  }

  cout << nmap.size() << endl;

  return 0;
}
