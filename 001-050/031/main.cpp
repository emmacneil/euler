#include <ctime>
#include <iostream>

using namespace std;



int c[] = {1, 2, 5, 10, 20, 50, 100, 200};

int f(const int n, const int m)
{
  if (n <  0) return 0;
  if (m <  0) return 0;
  if (n == 0) return 1;
  
  return f(n, m-1) + f(n - c[m], m);
}



int main (int argc, char* argv[])
{
  // Calculate...
  int n = f(200, 7);

  cout << n << endl;  
  double t = clock() / (double)CLOCKS_PER_SEC;
  cout << "Time taken: " << t << " seconds." << endl;

  return 0;
}
