"""
Project Euler - Problem 188
The Hyperexponentiation of a Number

This is easily solved using fast modular exponentiation and repeated application of Euler's
Theorem, which says that if a and m are coprime, then

    a^phi(m) = 1 (mod m)

Where phi is Euler's totient function. In our case, this tells us that

    1777^^1855 % 10^8
        = 1777^(1777^^1854 % phi(10^8)) % 10^8
        = 1777^(1777^( 1777^^1853 % phi(phi(phi(10^8))) ) % phi(10^8)) % 10^8
        = ...

We note that a) applying phi 24 times to 10^8 results in 1, so this sequence terminates quickly;
and b) 1777 is coprime with 10^8 and all of its repeated totients (1777 is prime and totients
of 10^8 have only 2 and 5 as prime factors).
"""

def f(a, b, m) : 
    if (m == 1) :
        return 0
    if (b == 1) :
        return a;
    return (a^f(a, b-1, euler_phi(m))) % m

f(1777, 1855, 100000000)