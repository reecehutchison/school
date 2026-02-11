-- task 1 : transpose matrix
-- use ' let arr = [[1..6],[21..26],[31..36]] ' for testing
getCol :: [[a]] -> Int -> [a]
getCol arr n = [row !! n | row <- arr]

transp :: [[a]] -> [[a]]
transp [] = [] -- if matrix is empty
transp arr = [getCol arr i | i <- [0..(length (head arr) - 1)]] -- extract all cols as rows


-- task 2 : matmult
-- isConformable is used for checking if mat1's rows match mat2's columns
isConformable :: [[a]] -> [[a]] -> Bool
isConformable mat1 mat2 
  | null mat1 || null mat2 = False
  | length (head mat1) == length mat2 = True
  | otherwise = False

-- dotProd will give you the dot product of two vectors
dotProd :: [Int] -> [Int] -> Int
dotProd [] [] = 0
dotProd (a:vec1) (b:vec2) = (a*b) + dotProd vec1 vec2 

-- procRow will process a row of the matrix
procRow :: [Int] -> [[Int]] -> [Int]
procRow row = map (dotProd row)

-- multiplies 2 matrices
-- matmult returns an empty list if matrices are not conformable
matMult :: [[Int]] -> [[Int]] -> [[Int]]
matMult mat1 mat2  
  | not (isConformable mat1 mat2) = []
  | otherwise = map (`procRow` mat2T) mat1 
      where mat2T = transp mat2