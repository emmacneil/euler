longDivide' :: Int -> Int -> [Char]
longDivide' num dem = x:xs
    where x    = show (div num dem) !! 0
          xs   = longDivide' num' dem
          num' = (num - dem * (div num dem)) * 10

longDiv :: Int -> Int -> Int
longDiv num dem = longDiv' num dem []

longDiv' :: Int -> Int -> [Int] -> Int
longDiv' num dem arr = if elem num arr
                       then pos
                       else longDiv' num' dem arr'
    where pos  = (length arr) - (length (takeWhile ( /= num) arr))
          num' = (num - dem * (div num dem)) * 10
          arr' = arr ++ [num]

solution = length (takeWhile ( /= max) arr) + 1
    where arr = map (longDiv 1) [1..1000]
          max = maximum arr

main = print solution
