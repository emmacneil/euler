#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
//#include "/home/evan/code/euler/include/mod.h"

using namespace std;
using namespace boost::multiprecision;

int128_t *fastmodpow(const int128_t a,
                     const int128_t n,
		     const int128_t m)
{
  int128_t e = n, y = a;
  int128_t *x;
  x = new int128_t;
  *x = 1;
  while (e != 0)
  {
    if (e % 2)
      *x *= y;
    e /= 2;
    y *= y; // e = 4
    
    *x %= m; // y = 27
    y  %= m; // x = 1
  }

  return x;
}



int main()
{
  int128_t a = 2;
  int128_t b = 28433;
  int128_t c = 1;
  int128_t n = 7830457;
  int128_t m = 10000000000L;
  
  int128_t *k = fastmodpow(a, n, m);
  *k = (b * *k + 1) % m;
  
  cout << *k << endl;

  return 0;
}

