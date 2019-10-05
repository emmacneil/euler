/*
 * Project Euler - Problem 86
 * Cuboid Routes
 *
 * ...
 */

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

const int  SOLUTIONS  = 1000000;
const int  SQ_LIMIT   = 500000000;

map<int,bool> is_sq;

void compute_squares()
{
  int s = 0;
  while (s*s <= SQ_LIMIT)
  {
    is_sq[s*s]=true;
    s++;
  }
}

int solve(int l)
{
  int n = 0;

  for (int h = 1; h <= 2 * l; h++)
  {
    if (is_sq.count( l*l + h*h ))
    {
      if (h <= l)
        n += h / 2;
      else
        n += l - (h + 1)/2 + 1;
    }
  }
  return n;
}

int main()
{
  int n = 0, m = 0;

  compute_squares();

  while (n <= SOLUTIONS)
  {
    m++;
    n += solve(m);
  }

  cout << m << endl;

  return 0;
}
