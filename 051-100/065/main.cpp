// Problem 65: Convergents of e

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

const bool OUTPUT = false;

int digitsum(int256_t n)
{
  int256_t m = 0;
  while (n > 0)
  {
    m += (n % 10);
    n /= 10;
  }
  return m.template convert_to<int>();
}

int main()
{
  int256_t a = 2, b = 3, c, k = 1;
  for (int i = 2; i < 100; i++)
  {
    if (i % 3 == 2)
      c = 2*b*(k++) + a;
    else
      c = b + a;
    a = b;
    b = c;
  }
  if (OUTPUT)
    cout << b << endl;
  cout << digitsum(b) << endl;

  return 0;
}
