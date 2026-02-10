-- task 1 : transpose matrix
-- use ' let arr = [[1..6],[21..26],[31..36]] ' for testing
getCol :: [[a]] -> Int -> [a]
getCol arr n = [row !! n | row <- arr]

transp :: [[a]] -> [[a]]
transp [] = [] -- if matrix is empty
transp arr = [getCol arr i | i <- [0..(length (head arr) - 1)]] -- extract all cols as rows


-- task 2 : matmul 
