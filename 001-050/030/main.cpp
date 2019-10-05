/*
 * Project Euler - Problem 30
 * Digit Fifth Power
 *
 * Simple calculation -- take each digit of n, raise them to their fifth
 * powers, sum them up, and compare their sum to n.
 */

#include <ctime>
#include <iostream>

using namespace std;



// Calculates the digital fifth power sum of N
// That is, takes each digit in N, raises them to their fifth powers,
// and sums them together, returning this value
int dps5(const int N)
{
  int n = N;
  int sum = 0;
  int last;
  while (n > 0)
  {
    // Get the last digit of n.
    last = n % 10;

    // Raise it to the fifth power
    last = last * last * last * last * last;

    // Add that number to the sum
    sum += last;

    // Reduce n
    n /= 10;
  }

  return sum;
}



int main (int argc, char* argv[])
{
  const int UPPER_BOUND = 354294;
  int sum = 0;

  // Calculate...
  for (int i = 10; i <= UPPER_BOUND; i++)
  {
    if (i == dps5(i))
    {
      cout << i << endl;
      sum += i;
    }
  }

  // Output
  cout << "Sum = " << sum << endl;
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
