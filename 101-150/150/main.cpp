/* Project Euler - Problem 150
 * Searching a Triangular Array for a Sub-triangle having Minimum Sum
 *
 * For each element in the triangular matrix, compute the minimum subtriangle whose top-most point
 * is that element. Print the minimum of these.
 */



#include <iostream>
using namespace std;

const int NROWS = 1000;

int T[NROWS][NROWS];

// Returns the minimum sub-triangle whose top corner is T[r][c].
int minimize(int r, int c)
{
  int ret = 0, sum = 0;
  for (int ri = 0; r + ri < NROWS; ri++) {
    for (int ci = 0; ci <= ri; ci++)
      sum += T[r+ri][c+ci];
    ret = sum < ret ? sum : ret;
  }
  return ret;
}

void fill()
{
  int t = 0;
  int two19 = 1 << 19;
  int two20 = 1 << 20;
  for (int r = 0; r < NROWS; r++) {
    for (int c = 0; c <= r; c++) {
      t = (t * 615949 + 797807) % two20;
      T[r][c] = t - two19;
    }
  }
}

int main(int argc, char * argv[])
{
  fill();
  int m = 0;
  int ans = 0;
  for (int r = 0; r < NROWS; r++) {
    for (int c = 0; c <= r; c++) {
      m = minimize(r, c);
      ans = m < ans ? m : ans;
    }
  }
  
  cout << ans << endl;
  
  return 0;
}

