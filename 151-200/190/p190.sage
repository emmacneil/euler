"""
  Project Euler - Problem 190
  Maximising a Weighted Product
  
  Let m be a positive integer. We want to maximize the function

                               p_m(x_1, ..., x_m) =  x_1*x_2^2*...*x_m^m

  given the constraint

                                       x_1 + x_2 + ... + x_m = m

  The function p_m is maximimized where its partial derivatives are all 0. For 2 <= k <= m, we
  substitute 

                                       x_1 = m - x_2 - ... - x_m                      (1)

  into p_m, compute its partial derivative with respect to x_k, and factor out the largest powers
  of each x_i (since each x_i must be positive). This yields the equation

                                    k(m - x_2 - ... - x_m) - x_k = 0

  which we rewrite as

                                       sum_{i=2}^m a_i x_i = km,                      (2)
    
  where a_i = k + 1 if i = k, otherwise a_i = k. The equation (1) and the equations (2) gives us a
  system of linear equations, which are sufficient to determine x_1 through x_m.
"""



# The goal is to construct a system of equations to solve for x_1, ..., x_m and to encode this
# system in a matrix. This function returns the kth row of the matrix corresponding to the
# subproblem consisting of m variables.
def row(k, m) :
  if k == 1 :
    return [QQ(1)] * m + [m];
  elif k > 1 and k <= m :
    return [QQ(0)] + [QQ(k)] * (k-2) + [QQ(k + 1)] + [QQ(k)] * (m-k) + [QQ(k*m)]
  else :
    return [QQ(0)] * (m+1)



# Construct a matrix using the row() function defined above.
def mat(m) :
  return Matrix(QQ, map(lambda k : row(k,m), [1..m]))



# Given the list lst = [a, b, c, ...], returns a * b^2 * c^3 * ...
# This computes the weighted product we are after.
def p(lst) :
  ret = QQ(1)
  for i, x in enumerate(lst) :
    ret = ret * x^(ZZ(i+1))
  return ret



# Solve the subproblem of maximizing p_m. Returns the weighted product, rounded down.
def sub_solve(m) :
  M = mat(m)               # Encode a system of equations in a matrix
  R = M.rref()             # Row reduce the matrix
  C = R.column(m)          # Extract the last column (which holds solutions for the x_i's)
  return floor(p(list(C))) # Compute the weighted product, rounded down.



# Solve the problem by solving the subproblems m = 2, ..., 15.
def solve() :
  M = 15
  ret = 0
  for m in [2 .. M] :
    ret = ret + sub_solve(m)
  return ret



def main() :
  print solve()



if __name__ == "main" :
  main()
