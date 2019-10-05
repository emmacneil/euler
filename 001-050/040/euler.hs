import Data.Char

champernowne = '0' : (concat $ map show [1..])

ctoi :: Char -> Int
ctoi c = (ord c) - (ord '0')

stoints :: [Char] -> [Int]
stoints [] = []
stoints [c] = [ctoi c]
stoints (c:str) = (ctoi c) : stoints str

main = print solution
  where solution = product $ stoints [ champernowne !! (10^n) | n <- [0..6] ]
