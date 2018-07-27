/* Project Euler - Problem 170
 * Find the Largest 0 to 9 Pandigital that Can Be Formed by Concatenating Products
 *
 * There are 10! pandigital 10-digit numbers. This is less than 4 million. We are looking for the
 * largest pandigital with a particular property, so we will simply begin with 9,876,543,210 and
 * iterate over all pandigitals in decreasing order until we find it. This is easily accomplished
 * with std::next_permutation.
 *   Now suppose k is a 10-digit pandigital integer. Now we want to check if 
 *
 *  * k = ab||ac for some integers a, b, and c (where || denotes concatenation) and
 *  * a||b||c is pandigital.
 *
 * We simply try every way of partitioning k into m||n. There are 9 ways to do this for each
 * pandigital k. For each partitioning k = m||n, we can write m and n as m = ab and n = ac for some
 * integers a, b, and c. There are possibly multiple ways to do this, one for every common divisor
 * of m and n. Finally, for each such triple (a, b, c), we check if a||b||c is pandigital.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;



// Concatenates the digits in the vector v.
// E.g. vec_to_int({1,2,7,4}) = 1274.
// Assumes the elements of v are integers in the range [0,9].
// An overflow error will occur if v is sufficiently large.
int vec_to_int(vector<int> & v)
{
  int ret = 0;
  for (int i = 0; i < v.size(); i++)
  {
    ret *= 10;
    ret += v[i];
  }
  return ret;
}

// Compute the greatest common divisor of a and b.
int gcd(int a, int b)
{
  if (b == 0) return a;
  if (b > a) return gcd(b, a);
  return gcd(b, a % b);
}

// Returns a vector of all positive integer divisors of a.
// This algorithm uses trial division. For the purpose of this solution, it is expected that the
// inputs will be small enough that this won't matter.
vector<int> divisors(int a)
{
  vector<int> ret;
  for (int d = 1; d*d <= a; d++)
  {
    if (a % d == 0)
    {
      ret.push_back(d);
      ret.push_back(a/d);
    }
  }
  return ret;
}

// Returns true if, between the integers a, b, and c, each digit 0 through 9 is countered exactly once.
// In other words, returns true if the concatenation a||b||c is 10-digit pandigital.
bool is_pandigital(int a, int b, int c)
{
  int dcount[10] = {0};
  bool ret = true;
  while (a > 0)
  {
    dcount[a % 10]++;
    a /= 10;
  }
  while (b > 0)
  {
    dcount[b % 10]++;
    b /= 10;
  }
  while (c > 0)
  {
    dcount[c % 10]++;
    c /= 10;
  }
  for (int d : dcount)
    ret &= (d == 1);
  return ret;
}

// Returns true if (m, n) is a "pandigital product" of some integers a and (b, c)
bool check(int m, int n)
{
  int g = gcd(m, n);
  vector<int> div = divisors(g);

  // Ignore the case where m or n is 0
  if ( (m == 0) || (n == 0) )
    return false;
    
  // For each divisor a of g
  for (int a : div)
  {
    int b = m/a;
    int c = n/a;
    if (is_pandigital(a, b, c))
    {
      cout << "The pandigital product of " << a << " and (" << b << ", " << c << ") is " << m << n << endl;
      return true;
    }
  }
  return false;
}

int main(int argc, char * argv[])
{
  vector<int> digits;
  for (int i = 9; i >= 0; i--)
    digits.push_back(i);

  bool found = false;  
  // For each permutation of the digits 0 through 9 (in reverse lexicographical order) ...
  do
  {
    // For each way of splitting the array digits[]
    for (int i = 1; !found && i < 10; i++)
    {
      vector<int> vm(digits.begin(), digits.begin() + i);
      vector<int> vn(digits.begin() + i, digits.end());
      int m = vec_to_int(vm);
      int n = vec_to_int(vn);
      found = check(m, n);
    }
  } while (!found && next_permutation(digits.begin(), digits.end(), greater<int>()));
  
  return 0;
}
