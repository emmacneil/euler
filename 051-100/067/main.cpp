#include <iostream>

#define N_ROWS 100

using namespace std;

int main()
{
  int **arr = new int*[N_ROWS + 2];
  for (int i = 0; i < N_ROWS + 2; i++)
  {
    arr[i] = new int[N_ROWS + 2];
    for (int j = 0; j <= i; j++)
    {
      if (j == 0 || j == i)
        arr[i][j] = 0;
      else
        cin >> arr[i][j];
    }
  }
  
  for (int i = 2; i < N_ROWS+2; i++)
    for (int j = 1; j <= i; j++)
      arr[i][j] += max(arr[i-1][j], arr[i-1][j-1]);

  int m = 0;
  for (int i = 1; i < N_ROWS+2; i++)
    m = arr[N_ROWS+1][i] > m ? arr[N_ROWS+1][i] : m;
  
  cout << m << endl;
  
  for (int i = 0; i < N_ROWS + 2; i++)
    delete[] arr[i];
  delete[] arr;
}
