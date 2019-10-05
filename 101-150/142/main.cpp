/**
 * Project Euler - Problem 142
 * Perfect Square Collection
 *
 * (x + y), (x - y), and (x + z) must be perfect squares, say m^2, n^2, and
 * l^2, respectively. Some algebraic manipulations show:
 *
 *                         n^2 + (y + z) = l^2, and
 *                         l^2 + (y - z) = m^2.
 *
 * That is, n and l are parts of a Pythagorean triple, as are l and m. l is the
 * hypotenuse of one Pythagorean triangle, and m is the hypotenuse of some
 * other Pythagorean triangle with base l.
 *   We can also solve for x, y, z in terms of l, m, n:
 *
 *                            x = (m^2 + n^2)/2
 *                            y = (m^2 - n^2)/2
 *                            z = l^2 - x
 *
 *   Our solution is to simply generate all Pythagorean triples up to some size
 * limit, find pairs of triples (a, b, c), (d, e, f) such that
 *
 *   i)   c = e, 
 *   ii)  b^2 = y + z
 *   iii) d^2 = y - z
 *   iv)  x - z is square.
 *
 * and output the smallest.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct triple {int first, second, third;};

vector<triple> triples1; // Pythagorean triples, sorted by 1st, 2nd, then 3rd values
vector<triple> triples2; // Pythagorean triples, sorted by 2nd value.



// Greatest common divisor
int gcd(int a, int b)
{
  if (b == 0) return b;
  if (a < b) return gcd(b, a);
  return gcd(b, a % b);
}



// Generates all Pythgorean triples up to some size limit. No triple will have
// a value exceeding 2*BOUND^2. Triples are stored (unsorted) in triples1 and
// triples2.
void fill_triples(const int BOUND)
{
  int a, b, c;
  for (int r = 1; r < BOUND; r++)
  {
    for (int s = r + 1; s < BOUND; s++)
    {
      if (gcd(r, s) > 1) continue;
      if ( (s-r) % 2 == 0) continue;
      for (int k = 1; k*(s*s + r*r) < 2*BOUND*BOUND; k++)
      {
        a = k*(s*s - r*r);
	b = 2*k*s*r;
	c = k*(s*s + r*r);
	if (a > b)
	{
	  a ^= b;
	  b ^= a;
	  a ^= b;
	}
	triples1.push_back({a,b,c});
      }
    }
  }
  triples2 = vector<triple>(triples1);
}



// Prints a vector of triples.
void print_triples(vector<triple> & vec)
{
  for (auto el : vec)
    printf("(%d,%d,%d)\n", el.first, el.second, el.third);
}



// Prints a single triple.
void print_triple(triple t)
{
  printf("(%d,%d,%d)\n", t.first, t.second, t.third);
}



// compares first, then second, then third values.
// Given two triples (a,b,c), (x,y,z), returns true if a < x.
// Otherwise, returns true if b < y.
// Otherwise, returns true iff c < z.
bool cmp_triples1(triple a, triple b)
{
  if (a.first < b.first) return true;
  else if (a.first > b.first) return false;
  else
    if (a.second < b.second) return true;
    else if (a.second > b.second) return false;
    else
      return a.third < b.third;
}



// Compares seconds values in each triple. Given triples (a,b,c), (x,y,z),
// returns true iff b < y.
bool cmp_triples2(triple a, triple b)
{
  return a.second < b.second;
}



// Sorts triples1 and triples2 using cmp_triples1 and cmp_triples2, respectively.
void sort_triples()
{
  sort(triples1.begin(), triples1.end(), cmp_triples1);
  sort(triples2.begin(), triples2.end(), cmp_triples2);
}



// Checks if both triples satisfy the conditions outlined in the beginning of
// the document.
bool check(triple a, triple b)
{
  int x, y, z, sqrt_xz;
  bool found;

  // Check that the parity of b.third and a.first are the same. I forget why.
  if ( (b.third + a.first) % 2 == 1 )
    return false;

  // Solve for x, y, z in terms of l, m, n.
  // l, m, n are a.third, b.third, a.first.
  x = (b.third * b.third + a.first * a.first) / 2;
  y = (b.third * b.third - a.first * a.first) / 2;
  z = a.third * a.third - x;

  // Check conditions ii, iii, iv. Condition i is assumed to hold before
  // calling this function.
  found = (a.second * a.second == y + z) &&
          (b.first * b.first == y - z);

  sqrt_xz = (int)sqrt(x - z);
  
  found = found && (sqrt_xz * sqrt_xz == x - z);

  // Output
  if (found)
  {
    printf("Triple 1: "); print_triple(a);
    printf("Triple 2: "); print_triple(b);
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);
    printf("%d\n", (x + y + z));
  }

  return found;
}



// Find a solution
void solve()
{
  vector<triple>::iterator it;

  // For each triple...
  for (auto a : triples1)
  {
    triple tmp = {a.third, a.third, a.third};
    
    // Find the first triple whose second value is equal to the third value of a.
    it = lower_bound(triples2.begin(), triples2.end(), tmp, cmp_triples2);

    // Iterate over all subsequent triples sharing the same property.
    // For each such triple...
    while ((*it).second == a.third)
    {
      // Check if the pair of triples satisfy conditions ii, iii, iv.
      if (check(a, *it))
        return;
      
      // Swap the first two values of a and check again.
      if (check({a.second, a.first, a.third}, *it))
        return;

      it++;
    }
  }

  printf("No solution found.\n");
}



int main(int argc, char * argv[])
{
  // Get all Pythagorean triples (up to some limit) and put it in a list.
  // Previous computations have shown 30 is a sufficient bound here.
  fill_triples(30);

  // Sort the list by first, then second, then third value.
  sort_triples();
  //print_triples(triples1);
  
  solve();

  return 0;
}
