fact :: Integer -> Integer
fact n = product [1..n]

--Calculates the binomial coeffecient nCr
c :: Integer -> Integer -> Integer
c n r = (fact n) `div` ((fact r) * fact(n-r))

--Creates a list of all binomial coefficients from 1C1 up to nCr
buildList :: Integer -> Integer -> [Integer]
buildList 0 0 = [1]
buildList n 0 = 1 : buildList (n-1) (n-1)
buildList n r = (n `c` r) : (buildList n (r-1))

main = do
         let l = buildList 100 100
         let l' = filter (>1000000) l
         print $ length l'
