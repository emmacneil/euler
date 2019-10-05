/*
 * Project Euler - Problem 93
 * Arithmetic Expressions
 *
 * Assuming that 0 is not going to be one of our digits, we have 9 choose 4
 * choices for a < b < c < d. There are 4! ways of arranging {a,b,c,d}. We have
 * 4^3 choices for our operators {+,-,*,/}, and 5 ways of pairing our
 * parentheses. In all, there are 967,680 different calculations to make here --
 * within brute-force range.
 */

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const float EPS = 1.0e-7;
const int MAX_VAL = 6561;

char operators[4] = {'+', '-', '*', '/'};
bool found[MAX_VAL + 1];
int best = 0;
int result = 0;



// Stores f as a 'found' value if it is an integer
void store(float f)
{
  if (f < 0)
    return;

  int n = rintf(f);
  float fn = (float)n;
  float d = f > fn ? f - fn : fn - f;
  if (d < EPS)
  {
    found[n] = true;
  }
}



// Applies the operator op to a and b. Note that although this doesn't check for
// divide by 0, it didn't prevent me from getting a correct solution :/
float sub(float a, float b, char op)
{
  switch (op)
  {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  default:
    return 0;
  }
}



// Calculates all five ways of arranging the parentheses
void calc(float nums[4], char ops[3])
{
  float a, b, c, d, x, y, z;
  a = nums[0];
  b = nums[1];
  c = nums[2];
  d = nums[3];

  // (((a*b)*c)*d)
  x = sub(a, b, ops[0]);
  y = sub(x, c, ops[1]);
  z = sub(y, d, ops[2]);
  store(z);

  // ((a*b)*(c*d))
  x = sub(a, b, ops[0]);
  y = sub(c, d, ops[2]);
  z = sub(x, y, ops[1]);
  store(z);
  
  // ((a*(b*c))*d)
  x = sub(b, c, ops[1]);
  y = sub(a, x, ops[0]);
  z = sub(y, d, ops[2]);
  store(z);
  
  // (a*((b*c)*d))
  x = sub(b, c, ops[0]);
  y = sub(x, d, ops[1]);
  z = sub(a, y, ops[2]);
  store(z);
  
  // (a*(b*(c*d)))
  x = sub(c, d, ops[2]);
  y = sub(b, c, ops[1]);
  z = sub(a, y, ops[0]);
  store(z);
}



// Tries all combinations of operators {+,-,*,/}
void choose_operators(float nums[4])
{
  char ops[3];
  for (int i = 0; i < 4; i++)
  {
    ops[0] = operators[i];
    for (int j = 0; j < 4; j++)
    {
      ops[1] = operators[j];
      for (int k = 0; k < 4; k++)
      {
        ops[2] = operators[k];
	calc(nums, ops);
      }
    }
  }
}



// Tries all permutations of {a,b,c,d}
void permute_abcd(float nums[4])
{
  do
  {
    choose_operators(nums);
  } while(next_permutation(nums, nums+4));
}



// Reset the array of 'found' values. Calculates all the values that can be
// obtained by choosing operators and arranging the values a,b,c,d in nums[].
// Counts the number of consecutive 'found' values, recording the best results
// so far.
void solve(float nums[4])
{
  for (int i = 0; i <= MAX_VAL; i++)
    found[i] = false;

  permute_abcd(nums);

  int i = 1;
  while (found[i++])
    continue;

  if (i > best)
  {
    best = i;
    result = nums[0]*1000 + nums[1]*100 + nums[2]*10 + nums[3];
  }
}



int main()
{
  float nums[4];

  // Try each choice of a, b, c, d.
  for (int a = 1; a <= 6; a++)
  {
    nums[0] = (float)a;
    for (int b = a + 1; b <= 7; b++)
    {
      nums[1] = (float)b;
      for (int c = b + 1; c <= 8; c++)
      {
        nums[2] = (float)c;
        for (int d = c + 1; d <= 9; d++)
	{
	  nums[3] = (float)d;
	  solve(nums);
	}
      }
    }
  }

  cout << result << endl;

  return 0;
}
