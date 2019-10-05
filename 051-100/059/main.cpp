#include <algorithm>
#include <iostream>

#define LEN 1202

using namespace std;

// Assuming dest is an array of 256 ints
void countOccurrences(int *dest, char *src)
{
  for (int i = 0; i < LEN-1; i++)
    dest[ src[i] ]++;
}

char *decrypt(char *cipher, char key[3])
{
  char *plain = new char[LEN];
  int k = 0;
  
  for (int i = 0; i < LEN-1; i++)
  {
    plain[i] = cipher[i] ^ key[k++];
    k %= 3;
  }

  return plain;
}

int sumChars(char* text)
{
  int n = 0;
  for (int i = 0; i < LEN-1; i++)
    n += text[i];
  return n;
}

int main()
{
  int n;
  int occ[256] = {0};
  char cipher[LEN];
  int i = 0;
  while (cin >> n)
  {
    cipher[i++] = (char)n;
    cin.ignore(1);
  }
  cipher[LEN-1] = 0;
  
  /*countOccurrences(occ, cipher);
  for (int i = 0; i < 256; i++)
    cout << i << ": " << occ[i] << endl;*/
  
  // Characters 79, 71, 68 were the most common occurence.
  // Assuming spaces (32) are the most frequent character in the text
  // Then the key is some permutation on 111, 103, 100 (ogd)

  char key[4] = {'d','g','o', 0};
  sort(key, key+3);
  do
  {
    cout << "KEY = " << key << endl;
    char *plain = decrypt(cipher, key);
    cout << plain << endl;
    cout << "SUM = " << sumChars(plain) << endl << endl;
    delete[] plain;
  } while ( next_permutation(key, key+3) );
  
  return 0;
}
