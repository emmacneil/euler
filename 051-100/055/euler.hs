isPalindrome :: Integer -> Bool
isPalindrome n = a == b
  where a = show n
        b = reverse $ show n

reverseInt :: Integer -> Integer
reverseInt = read . reverse . show

isLychrel :: Integer -> Bool
isLychrel n = isLychrel' 49 (n + reverseInt n)

isLychrel' :: Integer -> Integer-> Bool
isLychrel' 0 _ = True
isLychrel' i n = if isPalindrome n then False else isLychrel' (i-1) (n + reverseInt n)

main = do
  let arr = [ x | x <- [1..9999], isLychrel x ]
  let x = length arr
  print x
