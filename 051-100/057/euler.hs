-- Returns True is a has more decimal digits than b
most :: Integer -> Integer -> Bool
most a b = (length $ show a) > (length $ show b)

solve :: Integer -> Integer -> Integer -> Integer
solve 0 _ _ = 0
solve k numer denom = solve k' numer' denom' + c
  where k'     = k - 1
        denom' = numer + denom
	numer' = denom + denom'
	c      = if most numer denom then 1 else 0

main = do
  print $ solve 1000 3 2
