/* Project Euler - Problem 150
 * Searching a Triangular Array for a Sub-triangle Having Minimum-sum
 *
 * Another dynamic programming solution. Let T(i, j, k) be the sum of the sub-triangle at row i,
 * column k, with height k. This sum can be computed recursively by
 *
 *        T(i, j, k) = T(i + 1, j, k - 1) + T(i + 1, j + 1, k - 1) - T(i + 1, j + 1, k - 2)
 *
 * In words, to compute this sum, we add the sum of the two sub-triangles of height k - 1 to the
 * lower-left and lower-right. By the Inclusion-Exclusion Principle, we also have to subtract off
 * the elements we've doubly added -- the sum of the triangle of height k - 2 two rows down.
 *   There are 167,167,000 elements in the 3d array. This algorithm iterates over each element 3
 * times: once to initialize its value; once to compute its value according to the equation above;
 * and once when searching for the least value. Many improvements may be made. We don't need to
 * initialize all 167 million elements -- only the 500 thousand non-zero elements. We can also keep
 * track of the least sum as we are computing the sums. This would cut down on millions of memory
 * accesses and save several seconds. Regardless, this implementation runs in about 9 seconds, and
 * runs in less than 1 second when compiled with optimization level -O3.
 */



#include <iostream>
#include <vector>

using namespace std;



const int N_ROWS = 1000;

// tri[i][j][k] stores the sum of the triangle beginning at row i, column j, with height k + 1.
vector<vector<vector<int>>> tri;



// Linear congruential generator
int lcg()
{
  static int t = 0;

  t *= 615949;
  t += 797807;
  t &= 0xfffff;

  return t - (1 << 19);
}



// Construct the 3d vector that will contain the triangle's data. Initialize its values. All sub-
// triangles of height 1 are determined by the LCG above. The sums of all sub-triangles of height
// 2 or greater are initialized to 0, to be computed later.
void init_vector()
{
  tri.resize(N_ROWS);
  for (int i = 0; i < N_ROWS; i++)
  {
    tri[i].resize(i + 1);
    for (int j = 0; j <= i; j++)
    {
      tri[i][j].resize(N_ROWS - i);
      tri[i][j][0] = lcg();
      for (int k = 1; k < N_ROWS - i; k++)
      {
        tri[i][j][k] = 0;
      }
    }
  }
}



// Compute the sum of all sub-triangles of height 2 or greater.
void compute_subtriangles()
{
  // For each row, starting at bottom
  for (int i = N_ROWS - 1; i >= 0; i--)
  {
    // For each column, moving left to right
    for (int j = 0; j <= i; j++)
    {
      if (i < N_ROWS - 1)
        tri[i][j][1] = tri[i][j][0] + tri[i+1][j][0] + tri[i+1][j+1][0];
      // For each size of subtriangle, beginning at size 3
      for (int k = 2; k < N_ROWS - i; k++)
        tri[i][j][k] = tri[i][j][0] + tri[i+1][j][k-1] + tri[i+1][j+1][k-1] - tri[i+2][j+1][k-2];
    } 
  }
}



// Return the least sum.
int find_smallest()
{
  int ret = 0; // Answer will be negative, so start with 0 as an upper estimate.
  
  for (auto u : tri)
    for (auto v : u)
      for (auto x : v)
        ret = x < ret ? x : ret;
  
  return ret;
}



int main(int argc, char * argv[])
{
  init_vector();
  compute_subtriangles();
  cout << find_smallest() << endl;

  return 0;
}
