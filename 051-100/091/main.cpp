/*
 * Project Euler - Problem 91
 * Right Angles with Integer Coordinates
 *
 * Just brute force every possible combination of points. To ensure that we
 * don't count the same combination twice, we can do the following. Number the
 * corners of the grid:
 *
 *                                  6--7--8
 *                                  |  |  |
 *                                  3--4--5
 *                                  |  |  |
 *                                  0--1--2
 *
 * And calculate the positions of the points P and Q on the grid. We skip over
 * instances where P's position is lesser than or equal to Q's.
 */

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

const int  BOUND  = 50;
const bool EPS    = 1.0e-7;
const bool OUTPUT = false;

struct point
{
  double x, y;
};



// Distance between two points.
float dist(point P, point Q)
{
  float d = (P.x-Q.x)*(P.x-Q.x) + (P.y-Q.y)*(P.y-Q.y);
  return sqrt(d);
}



// Return true if O, P, Q define a right-angle triangle.
int check(point O, point P, point Q)
{
  float op, oq, pq, h, diff;

  // O, P, and Q may not overlap
  if (P.x == O.x && P.y == O.y) return false;
  if (Q.x == O.x && Q.y == O.y) return false;
  if (P.x == Q.x && P.y == Q.y) return false;

  // Calculate P's and Q's positions on the grid.
  // Return false if P is not 'ahead' of Q.
  if (P.y * (BOUND+1) + P.x < Q.y * (BOUND+1) + Q.x) return false;

  // Calculate length of each side of the triangle.
  op = dist(O, P);
  oq = dist(O, Q);
  pq = dist(P, Q);

  // Find the hypotenuse
  h = op > oq ? op : oq;
  h = pq > h  ? pq : h;
  
  // The triangle must satisfy a^2 + b^2 = c^2.
  // c^2 - b^2 - a^2 must therefore be 0 (or very close since we are using
  // floating point numbers)
  if (h == op) diff = h * h - oq * oq - pq * pq;
  if (h == oq) diff = h * h - op * op - pq * pq;
  if (h == pq) diff = h * h - op * op - oq * oq;
  diff = diff < 0 ? -diff : diff;
  
  if (OUTPUT && diff < EPS)
    printf("(%d,%d)(%d,%d)(%d,%d)\n",
          (int)O.x, (int)O.y,
	  (int)P.x, (int)P.y,
	  (int)Q.x, (int)Q.y);
  
  // Return true is we are 'close enough' to being a right angle triangle.
  return diff < EPS;
}



int main()
{
  int n = 0;
  point O = {0.0f, 0.0f}, P, Q;

  for (int py = 0; py <= BOUND; py++)
  {
    P.y = (float)py;
    for (int px = 0; px <= BOUND; px++)
    {
      P.x = (float)px;
      for (int qy = 0; qy <= BOUND; qy++)
      {
        Q.y = (float)qy;
        for (int qx = 0; qx <= BOUND; qx++)
	{
	  Q.x = (float)qx;
	  if (check(O, P, Q)) n++;
	}
      }
    }
  }

  cout << n << endl;
}
