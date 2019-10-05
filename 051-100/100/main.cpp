/*
 * Project Euler - Problem 100
 * Arranged Probabilities
 *
 * Let a be the number of blue discs in the box, and let x be the total number
 * of discs. Some computation has shown that the first few values of a and x
 * such that the probability of drawing two blues discs is 1/2 are:
 *
 *                          a = 3         x = 4
 *                          a = 15        x = 21
 *                          a = 85        x = 120
 *                          a = 493       x = 697
 *                          a = 2871      x = 4060
 *                          a = 16731     x = 23661
 *
 * The distances between these terms are growing by a factor of between 5 and 6.
 * If we compute enough values, we see that this factor converges to a value of
 * approximately 5.82843.
 *   So to find the next pair in the sequence quickly, we can just find the pair
 * before it, multiply them by a factor slightly lesser than 5.82843, and then
 * do a linear search for the next pair.
 *   Note that the difference between the first few terms is actually lesser
 * than 5.82843, so while this method works for larger values of a and x, it
 * will skip a couple of the earlier terms.
 */

#include </usr/include/boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace std;
using boost::multiprecision::int128_t;

const bool OUTPUT = true;

int main()
{
  int128_t a, aa, x, xx;
  a = 1;
  x = 1;

  while (1)
  {
    aa = 2 * a * (a - 1);
    xx = x * (x - 1);
    if (aa < xx)
      a++;
    else if (aa > xx)
      x++;
    else
    {
      if (OUTPUT)
        cout << "(" << a << "," << x << ")" << endl;
      if (x > 1000000000000L)
        break;
      a *= 582842;
      a /= 100000;
      x *= 582842;
      x /= 100000;
    }
  }

  if (OUTPUT)
    cout << a << " blue balls, of " << x << " balls total." << endl;
  else
    cout << a << endl;

  return 0;
}
