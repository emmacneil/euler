"""
Project Euler - Problem 182
RSA Encryption

Suppose m^e = m (mod n). Then m^(e-1) = 1 (mod n). This means that m must be a unit in the ring
Z/nZ, so m is an element of the group U(n) (the group of units modulo n). The order of this group
is phi(n) (where phi is Euler's totient function). The order of m must divide the order of the
group. Since m^(e-1) = 1, the order of m must also divide e - 1. Hence, the order of m divides
gcd(e - 1, phi(n)). Moreover, for every divisor d of gcd(e - 1, phi(n)), there is one or more
messages of order d that are unconcealable. This suggests that, if we want to find values of e that
minimize the number of unconcealable messages, we should be looking for values of e that minimize
gcd(e - 1, phi(n)).

Since phi(n) is even and gcd(e, phi(n)) is required to be 1, we must have that e is odd. Hence
e - 1 is even, and to minimize gcd(e - 1, phi(n)) means to impose gcd(e - 1, phi(n)) = 2. Our
algorithm is to find all e in the range 1 < e < phi(n) such that gcd(e, phi(n)) = 1 and
gcd(e-1, phi(n)) = 2. We then print the sum of all these e's.

As luck would have it, this algorithm produces the correct solution (the above 'proof' has some
holes) and runs in a couple of seconds.
"""



# These first two functions were used to confirm the hypothesis that gcd(e - 1, phi(n)) = 2
# minimizes the number of unconcealed messages.

# Return true if mod (m^e) n = m
# I.e., return true if the encryption of the message m under the RSA public key (e, n) is equal to m.
def unconcealed(e, n, m) :
  return mod(m^e, n) == m

# Given an RSA public key pair (e, n), return a list of all plaintexts m that are identical to their ciphertexts.
def unconcealed_list(e, n) :
  p = lambda m : unconcealed(e, n, m)
  return filter(p, [0 .. n - 1])



def main() :
  (p, q) = (1009, 3643)
  phi = (p-1)*(q-1)

  s = 0
  for e in [2 .. phi - 1] :
    if (gcd(e, phi) == 1) and (gcd(e - 1, phi) == 2) :
      s = s + e
  print s

if __name__ == "__main__":
  main()
