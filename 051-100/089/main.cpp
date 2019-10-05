/*
 * Project Euler - Problem 89
 * Roman Numerals
 *
 * Given a Roman numeral, we iterate through each position in the string and
 * look at the characters that follow. If they can be combined into a higher-
 * order numeral (e.g.: IIIII combined into V), we combine them and look at the
 * previous position again -- collapsing numerals into a higher order numeral
 * may allow the numerals that preceded it to also be collapsed. Example:
 *
 *  xviiiii
 *  ^
 *  xviiiii
 *   ^
 *  xviiiii
 *    ^
 *  xvv
 *   ^
 *  xx
 *  ^
 */

#include <iostream>
#include <string>

using namespace std;

string collapse(string str)
{
  int len = str.length();

  int i = 0;
  bool inc;
  while (i < len)
  {
    if (i < 0) i++;

    inc = false;
    if      (str.substr(i, 5) == "CCCCC") str.replace(i, 5, "D");
    else if (str.substr(i, 5) == "XXXXX") str.replace(i, 5, "L");
    else if (str.substr(i, 5) == "IIIII") str.replace(i, 5, "V");
    else if (str.substr(i, 4) == "CCCC") str.replace(i, 4, "CD");
    else if (str.substr(i, 4) == "XXXX") str.replace(i, 4, "XL");
    else if (str.substr(i, 4) == "IIII") str.replace(i, 4, "IV");
    else if (str.substr(i, 3) == "DCD") str.replace(i, 3, "CM");
    else if (str.substr(i, 3) == "LXL") str.replace(i, 3, "XC");
    else if (str.substr(i, 3) == "VIV") str.replace(i, 3, "IX");
    else if (str.substr(i, 2) == "DD") str.replace(i, 2, "M");
    else if (str.substr(i, 2) == "LL") str.replace(i, 2, "C");
    else if (str.substr(i, 2) == "VV") str.replace(i, 2, "X");
    else
      inc = true;

    if (inc) i++;
    else     i--;

    len = str.length();
  }
  return str;
}

int main()
{
  string str;

  int m, n, saved = 0;
  while (cin >> str)
  {
    int n = str.length();
    int m = collapse(str).length();
    saved += n - m;
  }
  
  cout << saved << endl;

  return 0;
}
