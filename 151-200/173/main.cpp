/* Project Euler - Problem 173
 * Using up to One Million Tiles, How Many Different "Hollow" Square Laminae Can Be Formed?
 *
 * Let b denote the width of the hollow square in tiles, and let a denote the width of the hole.
 * Let n be the number of available tiles. We have the following necessary and sufficient
 * conditions for a and b:
 *
 *     (i) 1 <= a <= b - 2
 *    (ii) a and b are both odd or both even
 *   (iii) b^2 - a^2 <= n
 *
 * It is now a matter of counting the pairs with these properties. We can place an upper bound on b
 *
 *                                       b <= floor(n/4) + 1
 *
 * If we fix a value of b, it is a simple matter to count the number of values of a satisfying the
 * above properties. The algorithm is to iterate over all values of 3 <= b <= n/4 + 1 and count the
 * number of values for a for each b.
 *   Runs in under one second.
 */
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;



// Counts the number of integers k in the closed interval [l, r] such that k and r have the same
// parity. It is assumed that l < r.
long inrange(long l, long r)
{
  // If l and r have different parity, we can increase l
  if ( (r % 2) != (l % 2) ) return inrange(l + 1, r);

  // Shift the range so that it begins at 0.
  if (l > 0) return inrange(0, r - l);

  // If we made it this far, our interval is of the form [0, r] for even r.
  // The number of even integers in this range is simpy r/2 + 1.
  return r / 2L + 1L;
}

int main(int argc, char * argv[])
{
  long N = 1000000;
  if (argc == 2)
    N = atoi(argv[1]);
  const long MAXB = (N / 4) + 1;
  const long RTN = floor(sqrt(N));

  long sum = 0;

  // If b is sufficiently small relative to n (when b <= sqrt(n)), there is no restriction on a.
  // a can be any value in the range [1, b - 2] with the same parity as b.
  for (long b = 3; b <= RTN; b++)
    sum += inrange(1, b - 2);

  // When b becomes large (when b > sqrt(n)), we don't have enough tiles unless we increase the
  // size of the hole. This imposes a lower bound on a, which is solved for by property (iii).
  for (long b = RTN + 1; b <= MAXB; b++)
    sum += inrange(ceil(sqrt(b*b - N)), b - 2);
  
  cout << sum << endl;
  
  return 0;
}
