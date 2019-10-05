/**
 * Project Euler - Problem 128
 * Hexagonal Tile Differences
 *
 * In each layer of the hexagonal grid, only the first tile (at "12 o'clock")
 * and the last tile (after filling in counter-clockwise) need to be
 * considered. All other tiles have two neighbours with a difference of 1, and
 * two neighbours with an even difference (and greater than 2). There are
 * exceptions to this rule in the first two layers, but we can account for
 * these: the only tiles n in the first two layers such that PD(n) = 3 are
 * n = 1 and n = 2.
 *   For the first tile in every layer, the neighbour to the south-west has a
 * difference of 1, and the neighbours to the north and south have even
 * differences. We need to check only the neighbours to the north-west, north-
 * east, and south-east.
 *   For the last tile in every layer, the neigbour to the south-east has a
 * difference of one, and the neighbours to the north and south have even
 * differences. We need to check only the neighbours to the north-west, north-
 * east, and south-west.
 */

#include <iostream>
#include "/home/evan/code/euler/include/primes.h"

using namespace std;



const int TARGET = 2000;
const int MAX_LAYER = 70000;
long FIRST[MAX_LAYER] = {0};



// Returns the first tile in the specified layer. The first tile is considered
// to be the one placed in the "12 o'clock" position. The inner layer
// containing only "1" is taken to be layer 0.
long first(int layer)
{
  if (layer == 0)   return 1;
  if (layer == 1)   return 2;
  if (FIRST[layer]) return FIRST[layer];
  
  FIRST[layer] =  6 * (layer - 1) + first(layer - 1);
  
  return FIRST[layer];
}



int main(int argc, char * argv[])
{
  int count = 2, layer = 2, pdn;
  long a, b, c, n;
  while (count < TARGET)
  {
    // Check first tile in current layer
    n = first(layer);         // Get the tile
    a = first(layer + 1) - 1; // Get its neighbours
    b = a + 2;
    c = first(layer + 2) - 1;
    pdn = 0;                  // Compute PD(n)
    if (isPrime(a - n)) pdn++;
    if (isPrime(b - n)) pdn++;
    if (isPrime(c - n)) pdn++;
    if (pdn == 3) count++;

    // If this is the 2000'th hit, break early.
    if (count == TARGET)
      break;

    // Check last tile in current layer
    n = first(layer + 1) - 1;
    a = first(layer - 1);
    b = first(layer);
    c = first(layer + 2) - 2;
    pdn = 0;
    if (isPrime(n - a)) pdn++;
    if (isPrime(n - b)) pdn++;
    if (isPrime(c - n)) pdn++;
    if (pdn == 3) count++;
    layer++;
  }

  // Output result.
  cout << n << endl;

  return 0;
}
