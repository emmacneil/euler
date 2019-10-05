/* Project Euler - Problem 149
 * Searching for a Maximum-Sum Subsequence
 *
 * Finding the maximum sum of a subsequence has a well-known dynamic programming solution. Given an
 * array A, let m(i) be the maximum subsequence ending on the i-th element of A. Then m(i) is equal
 * to either the maximum subsequence ending on the (i-1)-th element of A plus the i-th element of
 * A, or simply the i-th element itself.
 *
 *                                m(i) = max { m(i-1) + A[i], A[i] }
 *
 *   We simply fill a matrix M with the 4,000,000 pseudo-random entries as described in the
 * problem statement. Then we run the maximum subsequence algorithm on each of the rows, columns,
 * and diagonals of M. The most difficult part of this problem is iterating properly over the
 * diagonals of M.
 *   This algorithm terminates in a little under one second.
 */



#include <iostream>
#include <vector>
using namespace std;



const bool OUTPUT = false;
const int WIDTH = 2000;
const int HEIGHT = 2000;
long M[WIDTH * HEIGHT];
//long M[WIDTH * HEIGHT] = {-2, 5, 3, 2, 9, -6, 5, 1, 3, 2, 7, 3, -1, 8, -4, 8};

void fill()
{
  for (long k = 1; k <= 55; k++)
    M[k-1] = (100003ul - 200003ul*k + 300007ul*k*k*k) % 1000000ul - 500000ul;
  for (long k = 56; k <= 4000000ul; k++)
    M[k-1] = (M[k-25] + M[k-56] + 1000000ul) % 1000000ul - 500000ul;
}



// Returns the maximum sum of a contiguous subsequence of m.
int m(vector<int> & v)
{
  vector<int> s(v.size());
  int ret = 0;
  
  s[0] = v[0];
  for (int i = 1; i < s.size(); i++) {
    s[i] = s[i-1] > 0 ? s[i-1] + v[i] : v[i];
    ret = s[i] > ret ? s[i] : ret;
  }
  return ret;
}



void test(int val, int expected)
{
  cout << "Got:\t" << val << "\tExpected:\t" << expected << endl;
}



int solve_horizontals()
{
  vector<int> v(WIDTH);
  int tmp, ret = 0;
  for (int r = 0; r < HEIGHT; r++) {
    v.assign(M + r * WIDTH, M + (r + 1) * WIDTH);
    tmp = m(v);
    ret = tmp > ret ? tmp : ret;
  }
  return ret;
}

  

int solve_verticals()
{
  vector<int> v(HEIGHT);
  int tmp, ret = 0;
  for (int c = 0; c < WIDTH; c++) {
    for (int r = 0; r < HEIGHT; r++)
      v[r] = M[r * WIDTH + c];
    tmp = m(v);
    ret = tmp > ret ? tmp : ret;
  }
  return ret;
}



int solve_diagonals()
{
  const int DIM = HEIGHT > WIDTH ? HEIGHT : WIDTH;
  int tmp, ret = 0;
  for (int c = 0; c < WIDTH; c++) {
    vector<int> v(DIM);
    
    for (int k = 0; (k < HEIGHT) && (c + k < WIDTH); k++)
      v[k] = M[k * WIDTH + c + k];

    tmp = m(v);
    ret = tmp > ret ? tmp : ret;
  }

  for (int r = 1; r < HEIGHT; r++) {
    vector<int> v(DIM);

    for (int k = 0; (k < WIDTH) && (r + k < HEIGHT); k++) 
      v[k] = M[(r + k) * WIDTH + k];
    
    tmp = m(v);
    ret = tmp > ret ? tmp : ret;
  }
  return ret;
}



int solve_antidiagonals()
{
  const int DIM = HEIGHT > WIDTH ? HEIGHT : WIDTH;
  int tmp, ret = 0;
  for (int c = 0; c < WIDTH; c++) {
    vector<int> v(DIM);
    
    for (int k = 0; (k < HEIGHT) && (c - k >= 0); k++)
      v[k] = M[k * WIDTH + c - k];

    tmp = m(v);
    ret = tmp > ret ? tmp : ret;
  }

  for (int r = 1; r < HEIGHT; r++) {
    vector<int> v(DIM);

    for (int k = 0; (k < WIDTH) && (r + k < HEIGHT); k++) 
      v[k] = M[(r + k + 1) * WIDTH - k - 1];
    
    tmp = m(v);
    ret = tmp > ret ? tmp : ret;
  }
  return ret;
}



int main(int argc, char * argv[])
{
  fill();
  /*cout << M[9] << endl;
  cout << M[99] << endl;*/
  int solution;
  int h = solve_horizontals();
  int v = solve_verticals();
  int d = solve_diagonals();
  int a = solve_antidiagonals();

  if (OUTPUT) {
  cout << "Max Horizontal    Subsequence: " << h << endl;
  cout << "Max Vertical      Subsequence: " << v << endl;
  cout << "Max Diagonal      Subsequence: " << d << endl;
  cout << "Max Anti-diagonal Subsequence: " << a << endl;
  }
  solution = h > v ? h : v;
  solution = d > solution ? d : solution;
  solution = a > solution ? a : solution;
  cout << solution << endl;
  return 0;
}
