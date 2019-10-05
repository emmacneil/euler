/*
 * Project Euler - Problem 84
 * Monopoly Odds
 *
 * Runs a simple simulation. Player position begins at 0. We roll the dice a
 * million times following the rules of Monopoly described in the problem
 * description, recording the player position after each move. Then we find the
 * three most visited spaces.
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int  TRIALS = 1000000;
const int  D      = 4;
const bool OUTPUT = false;



// Determines the player's new position after drawing a Chance card, based on
// their current position.
int chance(int pos)
{
  static int i = 0;

  switch (i++ % 16)
  {
  case 0: // GO
    return 0;
  case 1: // JAIL
    return 10;
  case 2: // C1
    return 11;
  case 3: // E3
    return 24;
  case 4: // H2
    return 39;
  case 5: // R1
    return 5;
  case 6: // Next R
  case 7:
    if (pos == 7)  return 15;
    if (pos == 22) return 25;
    else           return 5;
  case 8: // Next U
    if (pos == 7)  return 12;
    if (pos == 22) return 28;
    else           return 12;
  case 9: // Back 3
    return pos - 3;
  default:
    return pos;
  }
}



// Determines the player's new position after drawing a Community Chest card,
// based on their current position.
int chest(int pos)
{
  static int i = 0;
  
  switch (i++ % 16)
  {
  case 0: // GO
    return 0;
  case 1: // JAIL
    return 10;
  default:
    return pos;
  }
}



// Rolls two dice and returns the result. flag is set to true if the roll was a
// double.
int roll(bool &flag)
{
  int a = rand() % D + 1;
  int b = rand() % D + 1;
  flag = (a == b);
  return a + b;
}



// Simulates player movement over n turns. The position of the player after
// each move is stored in arr.
void run(int *arr, int n)
{
  int pos = 0;  // Start on GO
  int dubs = 0; // Haven't rolled any doubles
  int r;
  bool flag;
  for (int i = 0; i < n; i++)
  {
    r = roll(flag); // Roll 2 dice
    if (flag)       // If they were doubles
      dubs++;
    else
      dubs = 0;
    if (dubs == 3)  // If they were the third doubles in a row
    {
      dubs = 0;
      pos = 10;
      arr[pos]++;
      continue;
    }

    pos += r;  // Move a number of spaces according to the roll
    pos %= 40; // Wrap around board
  
    if (pos == 30) // Go to JAIL
      pos = 10;
    if (pos == 7 || pos == 22 || pos == 36) // Chance
      pos = chance(pos);
    if (pos == 2 || pos == 17 || pos == 33) // Community Chest
      pos = chest(pos);

    arr[pos]++;
  }
}



int main()
{
  int arr[40] = {0};
  run(arr, TRIALS);

  if (OUTPUT)
  {
    string str[] = {"GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2",
                    "B3", "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2",
                    "D2", "D3", "FP", "E1", "CH2", "E2", "E3", "R3", "F1",
                    "F2", "U2", "F3", "G2J", "G1", "G2", "CC3", "G3", "R4",
                    "CH3", "H1", "T2", "H2"};
    for (int i = 0; i < 40; i++)
      printf("%02d %-4s - %4.2lf%%\n", i, str[i].c_str(),
             100.0 * (double)arr[i] / (double)TRIALS);
  }

  // Find greatest 3 elements in arr, arr[a] > arr[b] > arr[c]
  int a = 0, b = 0, c = 0, m;
  for (int i = 0, m = 0; i < 40; i++) if (arr[i] > m) { m = arr[i]; a = i; }
  for (int i = 0, m = 0; i < 40; i++) if (arr[i] > m) if (i != a) { m = arr[i]; b = i; }
  for (int i = 0, m = 0; i < 40; i++) if (arr[i] > m) if (i != a) if (i != b) { m = arr[i]; c = i; }
  printf("%02d%02d%02d\n", a, b, c);

  return 0;
}
