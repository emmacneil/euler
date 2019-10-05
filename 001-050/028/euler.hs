layer :: Int -> Int
layer 1 = 1
layer n = n*n*4 - 6*(n-1) + layer (n-2)

solution = layer 1001
