/**
 * Project Euler - Problem 140
 * Modified Fibonacci Golden Nuggets
 *
 * Much like problem 137. The infinite series from problem 137 was reduced to
 * 
 *                            p(x) = x/(1 - x - x^2).
 *
 * This time, the series can be reduced to
 *
 *                       p(x) = x(1 + 3x)/(1 - x - x^2)
 *
 * or in terms of rational x = r/s,
 *
 *                    p(r, s) = r(s + 3r)/(s^2 - rs - r^2)
 *
 *   A brute force search was run to find the first few rational solutions, and
 * a pattern was found. Let F(n) be the Fibonacci sequence, and let H(n) be the
 * sequence
 *
 *                             H(1) = 2
 *                             H(2) = 5
 *                           H(n+2) = H(n+1) + H(n)
 *
 * Then the "golden nuggets" are
 *
 *                     p( H(1), H(2) )  =  p(2,  5)  =  2
 *                     p( F(2), F(3) )  =  p(1,  2)  =  5
 *                     p( H(3), H(4) )  =  p(7, 12)  = 21
 *                     p( F(4), F(5) )  =  p(3,  5)  = 42
 *
 * and so on, alternating between F and H, and incrementing the index as we go.
 */

#include <iostream>

using namespace std;



const bool OUTPUT = true;
const long TARGET = 30;

long F[TARGET+1];
long H[TARGET+1];



// Computes the infinite series given in the problem description for a
// rational number r/s. The result is an integer. It is assumed that r/s will
// in fact produce an integer.
long p(long r, long s)
{
  long numer = r*(s + 3*r);
  long denom = (s*s - r*s - r*r);

  return numer/denom;
}



int main(int argc, char * argv[])
{
  long r, s, t, sum, * SEQ;

  // Initialize sequences.
  F[0] = 1; F[1] = 1;
  H[0] = 2; H[1] = 5;
  for (int i = 2; i <= TARGET; i++)
  {
    F[i] = F[i - 1] + F[i - 2];
    H[i] = H[i - 1] + H[i - 2];
  }

  // Compute nuggets
  sum = 0;
  SEQ = H;
  for (int i = 0; i < TARGET; i++)
  {
    r = SEQ[i];
    s = SEQ[i+1];
    t = p(r, s);
    sum += t;
    SEQ = SEQ == F ? H : F;

    if (OUTPUT)
      cout << "Nugget " << i + 1 << ": p(" << r << "," << s << ") = " << t << endl;
  }
  
  cout << sum << endl;

  return 0;
}
