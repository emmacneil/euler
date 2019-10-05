fact 0 = 1
fact n = n * fact (n - 1)

fib 0 = 1
fib 1 = 1
fib n = fib' 1 1 n

fib' _ b 1   = b
fib' a b acc = fib' b (b + a) (acc - 1)
