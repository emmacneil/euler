-- Project Euler - Problem 001
-- Multiples of 3 and 5

import System.Environment

t :: Integer -> Integer
t n = div (n*(n + 1)) 2

f :: Integer -> Integer -> Integer
f n k = k*t(div (pred n) k)

main = do
    args <- getArgs
    let n = if length args == 1 then read (head args) :: Integer else 1000
    let s = f n 3 + f n 5 - f n 15
    print s
