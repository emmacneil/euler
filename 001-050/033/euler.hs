
cancel :: (Integer, Integer) -> Bool
cancel (num, dem) = cancel'(num, dem) == a / b
    where a = fromIntegral num
          b = fromIntegral dem

cancel' :: (Integer, Integer) -> Double
cancel' (num, dem) = if b == d then a / c else
                    if b == c then a / d else
                    if a == c then b / d else
                    if a == d then b / c else 0.0
    where a = fromIntegral (div num 10)
          b = fromIntegral (mod num 10)
          c = fromIntegral (div dem 10)
          d = fromIntegral (mod dem 10)

solution = [ (a, b) | a <- [10..99], b <- [10..99], a < b, mod a 10 /= 0, mod b 10 /= 0, cancel(a, b) == True ]
