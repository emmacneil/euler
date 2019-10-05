/*
 * Project Euler - Problem 85
 * Counting Rectangles
 *
 * A rectangle of size w X h contains
 *
 *                             hw(w+1)(h+1) / 4
 *
 * rectangles. This is the product of the h'th and w'th triangular numbers.
 * Start with h = 1, w = 2,000 and compute the number of rectangles, n.
 * If n > 2,000,000, then we decrease w. If n < 2,000,000 then we increase h.
 * We repeat this until h = 2,000 and w = 1, recording the values of h and w
 * that produce n closest to 2,000,000 along the way.
 */

#include <iostream>

using namespace std;

int main()
{
  int h = 1, w = 2000;
  int best_h = 1, best_w = 2000;
  int d, m = 0x7fffff, n;
  
  while (w > 0)
  {
    n = (h*h+h)*(w*w+w)/4;
    d = n - 2000000;
    d = d < 0 ? -d : d;
    if (d < m)
    {
      m = d;
      best_h = h;
      best_w = w;
    }

    if (n > 2000000)
      w--;
    else
      h++;
  }

  cout << best_h * best_w << endl;
}
