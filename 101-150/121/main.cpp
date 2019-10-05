/**
 * Project Euler - Problem 121
 * Disc Game Prize Fund
 *
 * A dynamic programming problem. Let f(n, k) be the number of ways in which
 * the player can have drawn exactly k blue discs after n rounds. This is
 * the number of ways he could have drawn k-1 blue discs after n-1 rounds plus
 * n times the number of ways he could have drawn b blue discs after n-q
 * rounds, or:
 *
 *                     f(n, k) = f(n-1, k-1) + n*f(n-1, k)
 *
 * This is because for each way he could have gotten f(n-1, k-1) he could now
 * draw the one blue disc in the bag, and for each way he could have gotten
 * f(n-1, k-1) he could now draw one of the n red discs in the bag.
 *   For a game played over N rounds, the number of events is N!. The number
 * of ways the player wins is the sum from k = (N/2 + 1) to k = N of f(N, k).
 * The probability of the player winning is then that sum divided by N!.
 * Conversely, the payout is N! divided by the sum, rounded down.
 */

#include <iostream>

using namespace std;

const int TURNS = 15;

unsigned long f[TURNS+1][TURNS+1] = {0};

int main(int argc, char * argv[])
{
  // Compute f[][]
  f[0][0] = 1;
  for (int i = 1; i <= TURNS; i++)
  {
    f[i][0] = i * f[i-1][0];
    for (int j = 1; j <= TURNS; j++)
    {
      f[i][j] = f[i-1][j-1] + i * f[i-1][j];
    }
  }

  // Get probability of player winning, m/n
  unsigned long m = 0L;
  for (int j = TURNS/2+1; j <= TURNS; j++)
    m += f[TURNS][j];
  
  unsigned long n = 1L;
  for (int i = 1; i <= TURNS+1; i++)
    n *= i;

  // Payout is n/m
  cout << n/m << endl;

  return 0;
}
