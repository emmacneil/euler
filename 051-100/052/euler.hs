import Data.List

--Takes an integer n
--Returns another integer composed of the n's digits, sorted.
sortInt :: Integer -> Integer
sortInt n = read $ sort $ show n

--Takes an integer n
--Returns true if n, 2n, 3n, 4n, 5n and 6n have the same digits.
check :: Integer -> Bool
check n = allEq $ map sortInt $ map (n*) [1..6]

--Returns true if all elements of a list are equal
allEq :: Eq a => [a] -> Bool
allEq [x] = True
allEq (x:xs) = x == head xs && allEq xs

main = do
  let n = find check [1..]
  print n
