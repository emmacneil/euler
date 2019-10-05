t :: Integer -> Integer
t n = div (n * (n + 1)) 2

p :: Integer -> Integer
p n = div (n * (3 * n - 1)) 2

h :: Integer -> Integer
h n = n * (2 * n - 1)

next a b c = if t(a) == p(b) && p(b) == h(c)
             then t(a)
             else next a' b' c'
    where a' = if smallest a b c == t(a) then a+1 else a
          b' = if smallest a b c == p(b) then b+1 else b
          c' = if smallest a b c == h(c) then c+1 else c

smallest a b c = minimum [t(a), p(b), h(c)]

solution = next 1 1 144
