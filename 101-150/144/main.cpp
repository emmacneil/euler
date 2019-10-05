/* Project Euler - Problem 144
 * Investigating Multiple Reflections of a Laser Beam
 *
 * Nothing special is done here. Given a vector form equation of a line describing the direction
 * in which the light is traveling, find the lights next point of contact with the cell and the
 * direction of the light's reflection. This gives us a vector equation for a new line. Iterate
 * this process until it is determined that the light escapes (when the next point of contact with
 * the cell is at (x, y) for some -0.01 <= x <= 0.01, 0 < y).
 */



#include <iostream>
#include <cmath>

using namespace std;

const bool OUTPUT = false;



/* Vector class.
 * This is where much of the heavy lifting is done.
 * Makes printed output easy to manage.
 * Operators are overloaded to make vector addition, subtraction, and scalar multiplication easy.
 * Dot products, projections and rejections are defined.
 * Rejections are used in calculating the direction of a line after reflection. */
struct vec2d
{
  vec2d(double x, double y) : x(x), y(y) {}
  double x, y;
  double dot(const vec2d& v) const { return x*v.x + y*v.y; };
  // Projection of this onto v
  vec2d proj(const vec2d& v) const;
  vec2d rej(const vec2d& v) const { return (*this) - proj(v); }
  vec2d operator+(const vec2d& v) const { return vec2d(x+v.x, y+v.y); }
  vec2d operator-(const vec2d& v) const { return vec2d(x-v.x, y-v.y); }
  friend ostream& operator<<(ostream& os, const vec2d& v);
};

ostream& operator<<(ostream& os, const vec2d& v)
{
  os << "(" << v.x << ", " << v.y << ")";
  return os;
}

const vec2d operator*(const double k, const vec2d& v)
{
  return vec2d(k*v.x, k*v.y);
}

vec2d vec2d::proj(const vec2d& v) const
{
  return (dot(v) / v.dot(v)) * v;
}



/* Line class.
 * Not strictly necessary.
 * Allows us to use lines as parameters and return values, rather than pairs of vectors.
 * Makes printed output easy to manage. */
struct line2d
{
  line2d(vec2d p, vec2d d) : p(p), d(d) {}
  vec2d p, d;
  friend ostream& operator<<(ostream& os, const line2d& l);
};

ostream& operator<<(ostream& os, const line2d& l)
{
  os << l.p << " + " << l.d << "t";
  return os;
}



/* The core function in the algorithm.
 *   Given a (vector equation for a) line passing through the ellipse, returns the reflection of
 * the line tangent to the ellipse. We first find the point of intersection. Our line is
 * parameterized as
 *
 *    x = p_x + d_x t        (1)
 *    y = p_y + d_y t        (2)
 * 
 * And the ellipse is given as
 * 
 *    4x^2 + y^2 - 100 = 0   (3)
 * 
 * Substituting (1) and (2) in (3), we get a quadratic equation in t, and we use the quadratic
 * formula to solve for t. We are interested in the larger of the two solutions. The smaller
 * solution ought to be t = 0, which corresponds to a point we already know, the position vector
 * of the input line.
 *   The solution t > 0 gives us a point coinciding with the input line, the reflected line, and
 * the ellipse. We calculate the direction vector of the reflected line using vector rejections.
 * If d_in is the direction of the input line, d_tan is the direction of the line tangent to the
 * ellipse at the point of intersection, and d_out is the direction of the output line, then
 *
 *    d_out = d_in - 2 * rej_{d_tan}(d_in)
 * 
 * where rej_b(a) is the rejection of a from b.
 *   We then return the line defined by the point of intersection and direction vector that we
 * found. */
line2d reflect(line2d in)
{
  double t;       // Solution to quadratic equation
  double a, b, c; // Coefficients of quadratic equation
  double disc;    // Discriminant of quadratic equation
  
  // Find next point of intersection...
  
  a = 4.0 * in.d.x * in.d.x + in.d.y * in.d.y;
  b = 8.0 * in.p.x * in.d.x + 2.0 * in.p.y * in.d.y;
  c = 4.0 * in.p.x * in.p.x + in.p.y * in.p.y - 100.0;
  
  disc = b*b - 4.0*a*c;
  
  // If d < 0 here, something has gone wrong.
  if (disc < 0)
  {
    cout << "Discriminant is negative!" << endl;
    exit(0);
  }
  
  t = (-b + sqrt(disc))/(2.0*a);

  vec2d P( in.p + t*in.d ); // Position vector P of the reflected line.

  // Find direction of reflection...

  vec2d tang( P.y, -4.0 * P.x );          // Direction vector of tangent line to ellipse at P
  vec2d D( in.d - 2.0 * in.d.rej(tang) ); // Direction of reflection

  // Construct and return next line.
  return line2d(P, D);
}



int main(int argc, char * argv[])
{
  double x, y;
  int i = 0;
  
  // Initial line given in problem statement.
  vec2d P0(0.0, 10.1), D0(1.4,-19.7);
  line2d L(P0, D0);

  // Print initial line.
  if (OUTPUT)
    cout << i << ": " << L << endl;

  // Repeat contents of loop until the laser escapes the ellipse.
  do
  {
    L = reflect(L); // Reflect line
    i++;            // Increase number of contacts (reflections)
    
    if (OUTPUT)
      cout << i << ": " << L << endl;
    
    x = L.p.x;
    y = L.p.y;
  } while ( (x < -0.01) || (0.01 < x) || (y < 0) ); // Stop if next intersection is ellipse's exit
  
  // Print result. Subtract one, since the last "intersection" passed through the hole in the
  // ellipse, not through the ellipse itself.
  cout << (i - 1) << endl;

  return 0;
}
