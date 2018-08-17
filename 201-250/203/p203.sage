"""
  Project Euler - Problem 203
  Squarefree Binomial Coefficients

  Testing whether integers are squarefree, to my knowledge, requires factoring the integer (though
  one can stop factoring early upon encountering a squared prime). Factoring is computationally
  expensive in general, but a brute-force factoring of all the integers in Pascal's triangle works
  very nicely for this problem.
    In the first 51 rows of Pascal's Triangle, there are only 1326 integers, so we don't need to
  factor many numbers. Considering the triangle is symmetric, we can disregard almost half of those
  values and reduce the problem to factoring 676 numbers. We could reduce the number of
  factorizations even more by ignoring all the 1's, but 1 is rather easy to factor anyway. The
  largest binomial is C(50, 25) = 126,410,606,437,752. Numbers this large sound like they might
  take a long time to factor, but no number in the first 51 rows is divisible by a prime larger
  than 50. These numbers are all incredibly easy to factor.
    Sage already has predefined functions for computing binomials and testing whether integers are
  squarefree, as well as support for arbitrarily large integers. This solution runs in well under a
  second.
"""

def main() :
  N = 50
  L = []
  for i in [0..N] :
    for j in [0..floor(i/2)] :
      L = L + [binomial(i,j)]
  S = filter(is_squarefree, set(L))
  print(sum(S))

if __name__ == "__main__" :
  main()
