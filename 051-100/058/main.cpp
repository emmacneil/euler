#include <iostream>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;

int main()
{
  int a = 3;      // number on upper-right diagonal
  int b = 5;      // number on upper-left diagonal
  int c = 7;      // lower-left
  int d = 9;      // lower-right
  int k = 3;      // side length
  int n = 1;      // total number of numbers on diagonals
  int p = 0;      // total number of primes on diagonal
  int x = 10;     // increment to numbers on diagonals
  double r = 1.0; // ratio of numbers to primes

  while (r >= 0.1)
  {
    if (isPrime(a)) p++; a += x; x += 2;
    if (isPrime(b)) p++; b += x; x += 2;
    if (isPrime(c)) p++; c += x; x += 2;
    if (isPrime(d)) p++; d += x; x += 2;
    n += 4;
    k += 2;
    r = (double)p / (double)n;
  }

  cout << k-2 << endl;

  return 0;
}
