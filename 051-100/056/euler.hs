import Data.List

--Take a pair (a,b) and return a^b
f :: (Integer, Integer) -> Integer
f (a, b) = a^b

--Return the digit some of n
g :: Integer -> Integer
g 0 = 0
g n = n' + n''
  where n'  = mod n 10
        n'' = g $ div n 10

main = do
         let pairs = [ (a,b) | a <- [1..99], b <- [1..99] ]
         let pows = map f pairs
         let sums = map g pows
         print $ maximum sums
