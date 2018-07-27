/* Project Euler - Problem 165
 * Intersections
 *
 * Straight-forward brute force algorithm. For every distinct pair of line segments A and B:
 *
 *  - Check if A and B intersect (i.e. are not parallel)
 *  - Check that the endpoints of A are not on B and vice versa (i.e. check that A's endpoints do
 *    not satisfy B's line equation).
 *  - Find the point of intersection of the lines defined by A and B.
 *  - Check that this point of intersection is actually on the segments A and B.
 *
 * If all of these checks pass, add the point of intersection to a set (rather than an array so as
 * not to count duplicate points). This requires also defining a point struct to add points to the
 * set. Moreover, this struct must represent *rational* points since the points of intersection are
 * not necessarily integral. This further necessitates defining a comparison function (<) on
 * rational points.
 */

#include <algorithm> // min, max
#include <iostream>
#include <set>
#include <vector>

using namespace std;

const int N_SEGMENTS = 5000;
bool output = false;



// Line segment data structure.
// The segment is defined by two endpoints (x1, y1) and (x2, y2)
// The segment can be extended to an infinite line with the equation
//   L : ax + by + c = 0
// The function L(x, y), substitutes x and y into the equation defining the line above.
// A point (x, y) is on the line if and only if L(x, y) = 0.
// A point is on the segment if and only if all three of the following hold:
//  * L(x, y) = 0
//  * x is between x1 and x2, and
//  * y is between y1 and y2.
struct segment
{
  segment(long x1, long y1, long x2, long y2)
   : x1(x1), y1(y1), x2(x2), y2(y2),
     a(y1 - y2), b(x2 - x1), c((x1 - x2)*y1 + x1*(y2-y1)) {}

  long x1, y1, x2, y2;
  long a, b, c;
  
  long L(const long x, const long y) const{ return a*x + b*y + c; }
  
  // Returns true if the rational point (xn/xd, yn/yd) lies on the line segment.
  // (Actually returns true if the rational point is contained in the smallest rectangle containing
  // the segment. This function does not check that the point actually lies on the line. That
  // should be verified by some other means (which this solution does...))
  bool contains(const long xn, const long xd, const long yn, const long yd) const
  {
    return ( (xn >= xd*min(x1, x2)) &&
             (xn <= xd*max(x1, x2)) &&
             (yn >= yd*min(y1, y2)) &&
             (yn <= yd*max(y1, y2)) );
  }
};



// Represents a rational point in QQ^2.
struct rational_point
{
  rational_point(long xn, long xd, long yn, long yd)
   : xn(xn), xd(xd), yn(yn), yd(yd) {}
   
  long xn, xd, yn, yd; // x numerator and denominator, y numerator and denominator.
  
  struct compare
  {
    // Comparison function. Returns true if lhs < rhs according to the lexicographical ordering on
    // points in QQ^2.
    bool operator() (const rational_point & lhs, const rational_point & rhs)
    {
      if (lhs.xn * rhs.xd < rhs.xn * lhs.xd) return true;
      if (lhs.xn * rhs.xd > rhs.xn * lhs.xd) return false;
      return (lhs.yn * rhs.yd < rhs.yn * lhs.yd);
    }
  };
};



// Array of line segments.
vector<segment> segs;
// Set of distinct true intersection points. Inserting into a set ensures we count no duplicates.
set<rational_point, rational_point::compare> true_intersections;



// For test purposes, outputs the segment in a readble format.
void print_segment(segment s)
{
  cout << "(" << s.x1 << "," << s.y1 << ") to (" << s.x2 << "," << s.y2 << ")" << endl;
}



// "Blum Blum Shub" pseudo-random number generator
long bbs()
{
  static long a = 290797L;
  a = (a * a) % 50515093L;
  return a % 500L;
}



// Fills the array of line segments.
void generate_segments()
{
  for (int i = 0; i < N_SEGMENTS; i++)
  {
    long x1 = bbs();
    long y1 = bbs();
    long x2 = bbs();
    long y2 = bbs();
    segs.push_back(segment(x1, y1, x2, y2));
    //print_segment(segs[i]);
  }
}



// Returns true if A and B are parallel line segments.
bool parallel(const segment & A, const segment & B)
{
  if ( (A.b == 0) && (B.b == 0) ) return true;
  if ( (A.b == 0) && (B.b != 0) ) return false;
  if ( (A.b != 0) && (B.b == 0) ) return false;
  if ( (A.a * B.b) == (A.b * B.a) ) return true;
  return false;
}



// Returns true if A and B have a true intersection. That intersection is added to a set.
bool intersect(const segment & A, const segment & B)
{
  // If segments are parallel, they have no true intersection.
  if (parallel(A, B))
    return false;
  
  // If end point of one segment lies on the other, they have no true intersection.
  if ( (A.L(B.x1, B.y1) == 0) ||
       (A.L(B.x2, B.y2) == 0) ||
       (B.L(A.x1, A.y1) == 0) ||
       (B.L(A.x2, A.y2) == 0) )
    return false;

  // Now compute the point of intersection of the two lines defined by segments A and B.  
  long a = A.a, b = A.b, c = A.c,
       r = B.a, s = B.b, t = B.c;
  
  // The equations of the two lines are
  //   ax + by + c = 0
  //   rx + sy + t = 0
  // The point of intersection of the two extended lines is
  //   x = (cs - bt)/(br - as)
  //   y = (at - cr)/(br - as)
  // These equations are valid (i.e. br - as is not 0) whenever the two lines are not parallel,
  // but we already ruled out that case above. We must represent x and y by rational numbers to
  // avoid precision errors, e.g. x = x_numer / x_denom.
  long x_numer = c*s - b*t,
       x_denom = b*r - a*s,
       y_numer = a*t - c*r,
       y_denom = x_denom;
  
  // The math that follows involves multiplying inequalities possibly by negative values.
  // To make sure signs do not get flipped, ensure denominators have positive values.
  if (x_denom < 0)
  {
    x_numer *= -1L;
    x_denom *= -1L;
    y_numer *= -1L;
    y_denom *= -1L;
  }

  if ( A.contains(x_numer, x_denom, y_numer, y_denom) &&
       B.contains(x_numer, x_denom, y_numer, y_denom) )
  {
    true_intersections.insert(rational_point(x_numer, x_denom, y_numer, y_denom));
    return true;
  }

  return false;
}



int main(int argc, char * argv[])
{
  generate_segments();

  // Find intersections
  for (int i = 0; i < N_SEGMENTS; i++)
    for (int j = i + 1; j < N_SEGMENTS; j++)
      intersect(segs[i], segs[j]);

  cout << true_intersections.size() << endl;
  
  return 0;
}

