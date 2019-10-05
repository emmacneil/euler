/* Project Euler - Problem 205
 * Dice Game
 *
 * Let Pr(P = m) be the probability that Peter rolls m and Pr(C = n) be the
 * probability that Colin rolls n. The probability that Peter beats Colin is

 *                     Pr(P > C) = Pr(C = 6) * Pr(P > 6)
 *                               + Pr(C = 7) * Pr(P > 7)
 *                               + ...
 *                               + Pr(C = 35) * Pr(P > 35)
 */

#include <iostream>

#define loop(i, n) for(int i = 1; i <= n; i++)

using namespace std;



int P[37]; // P[k] = 4^9 * Pr(P >= k)
int C[37]; // C[k] = 6^6 * Pr(C = k)

int main(int argc, char * argv[])
{
  double pr = 0.0;

  // Compute the number of ways in which Peter can roll k
  loop(a, 4) loop(b, 4) loop(c, 4)
  loop(d, 4) loop(e, 4) loop(f, 4) 
  loop(g, 4) loop(h, 4) loop(i, 4) 
    P[a + b + c + d + e + f + g + h + i]++;

  // Convert these results into the number of ways Peter can roll *at least* k
  for (int i = 35; i >= 0; i--)
    P[i] += P[i + 1];

  // Compute the number of ways Colin can roll k
  loop(a, 6) loop(b, 6) loop(c, 6)
  loop(d, 6) loop(e, 6) loop(f, 6)
    C[a + b + c + d + e + f]++;

  // Compute the sum of products described at the beginning of the file
  for (int i = 0; i < 36; i++)
    pr += (double)(C[i] * P[i+1]);
  pr /= 262144.0; // 4^9
  pr /= 46656.0;  // 6^6

  // Output results.
  cout.precision(7);
  cout << pr << endl;

  return 0;
}
