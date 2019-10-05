#include <iostream>
#include <algorithm> // next_permutation
#include <cstring>   // memcpy
#include "../../include/primes.h"

#define N_DIGITS 6
#define GOAL 8

using namespace std;

void replace(char *d, char from, char to)
{
  for (int i = 0; i < N_DIGITS; i++)
    if (d[i] == from)
      d[i] = to;
}

int combine(char *d)
{
  int m = 0;

  for (int i = 0; i < N_DIGITS; i++)
  {
    m *= 10;
    m += d[i] - '0';
  }

  return m;
}

// Returns the smallest prime representable by d if d s valid
// Returns 0 if d is not valid
int isValid(char *d)
{
  if (d[0] == '0') // Must have strictly N_DIGITS digits
    return 0;
  char tmp[N_DIGITS];
  
  int n, m = 0, c = 0;
  for (int i = d[0] == '*' ? 1 : 0;
       i < 10; i++)
  {
    memcpy(tmp, d, N_DIGITS * sizeof(char));

    replace(tmp, '*', i+'0');
    
    n = combine(tmp);
    if (isPrime(n))
    {
      c++;
      if (c == 1)
        m = n;
    }
  }

  return c >= GOAL ? m : 0;
}

int main (int argc, char* argv[])
{
  char digits[N_DIGITS] = {'*', '*', '*', 'c', 'b', 'a'};
  //char digits[N_DIGITS] = {'b', 'c', '*', '*', 'a'};
  //char digits[N_DIGITS] = {'*', 'a'};
  char tmp[N_DIGITS];
  int m, min_p = 0x7fffffff;

  sort(digits, digits + N_DIGITS-1);
  
  do
  {
    for (int b = 0; b < 10; b++)
    {
      for (int c = b; c < 10; c++)
      {
        memcpy(tmp, digits, N_DIGITS * sizeof(char));
        replace(tmp, 'b', b+'0');
        replace(tmp, 'c', c+'0');
        tmp[N_DIGITS-1] = '1';
        if ( (m = isValid(tmp)) != 0)
          min_p = m < min_p ? m : min_p;

        tmp[N_DIGITS-1] = '3';
        if ( (m = isValid(tmp)) != 0)
          min_p = m < min_p ? m : min_p;
      
        tmp[N_DIGITS-1] = '7';
        if ( (m = isValid(tmp)) != 0)
          min_p = m < min_p ? m : min_p;
      
        tmp[N_DIGITS-1] = '9';
        if ( (m = isValid(tmp)) != 0)
          min_p = m < min_p ? m : min_p;
      
      }
    }
  } while ( next_permutation(digits, digits + N_DIGITS - 1) );

  cout << min_p << endl;

  return 0;
}
