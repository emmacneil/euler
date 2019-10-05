/*
 * Project Euler - Problem 90
 * Cube Digit Pairs
 *
 * It turns out that there are only 26,460 arrangements of the two dice that
 * are possible, given the constraint that the same digit must not occur twice
 * on the same die. Most of these arrangements we will be rejecting since we 
 * want the numbers on the second die, when arranged in ascending order, to be
 * larger than or equal to those on the first die in order not to double-count
 / non-distinct arrangements. So we can just brute force this solution.
 */

#define range(x,a,b) for(x=a;x<b;x++)

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

const bool OUTPUT = false;

bool found[8];
bool digits[10];

inline void find(int n)
{
  switch (n)
  {
    case 1:
      found[0] = true;
      break;
    case 4:
      found[1] = true;
      break;
    case 6:
      found[2] = true;
      break;
    case 16:
      found[3] = true;
      break;
    case 25:
      found[4] = true;
      break;
    case 36:
      found[5] = true;
      break;
    case 46:
      found[6] = true;
      break;
    case 81:
      found[7] = true;
      break;
    default:
      return;
  }
}

bool check(int die1[6], int die2[6])
{
  int i, j, a, b, c, d;
  bool good = true;

  // Check if we have at least one of each digits between the two die.
  range(i,0,10)
    digits[i] = false;
  range(i,0,6)
  {
    digits[die1[i]] = true;
    digits[die2[i]] = true;
  }
  digits[6] |= digits[9];
  digits[9] |= digits[6];
  range(i,0,7)
    good &= digits[i];
  range(i,8,10)
    good &= digits[i];
  if (!good)
    return false;
  
  // Initialize found array to false
  range(i,0,8) found[i] = false;

  // Check if we have all the squares
  good = true;
  range(i,0,6) range(j,0,6)
  {
    a = die1[i]; if (a == 9) a = 6;
    b = die2[j]; if (b == 9) b = 6;
    c = 10 * a + b;
    d = 10 * b + a;
    find(c);
    find(d);
  }
  range(i,0,8)
    good &= found[i];

  if (good && OUTPUT)
  {
    printf("{%d,%d,%d,%d,%d,%d} ",
           die1[0], die1[1], die1[2], die1[3], die1[4], die1[5]);
    printf("{%d,%d,%d,%d,%d,%d}\n",
           die2[0], die2[1], die2[2], die2[3], die2[4], die2[5]);
  }
  
  return good;
}

int diecmp(int die1[6], int die2[6])
{
  int i;
  range(i,0,6)
  {
    if (die1[i] < die2[i]) return -1;
    if (die1[i] > die2[i]) return 1;
  }
  return 0;
}

int main()
{
  int die1[6];
  int die2[6];
  int n = 0;
  range(die1[0],0,1)
  range(die1[1],die1[0]+1,10)
  range(die1[2],die1[1]+1,10)
  range(die1[3],die1[2]+1,10)
  range(die1[4],die1[3]+1,10)
  range(die1[5],die1[4]+1,10)

  range(die2[0],0,10)
  range(die2[1],die2[0]+1,10)
  range(die2[2],die2[1]+1,10)
  range(die2[3],die2[2]+1,10)
  range(die2[4],die2[3]+1,10)
  range(die2[5],die2[4]+1,10)
  if ( diecmp(die1, die2) < 1 )
  if (check(die1, die2)) n++;
  
  cout << n << endl;

  return 0;
}
