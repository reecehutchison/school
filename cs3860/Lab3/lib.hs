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


-- task 3 : pascal
-- pascal is given a row of the triangle, and will return the next row
-- we use tail to match every value we need to add...
-- 1 3 3 1
--  3 3 1  --> result of tail
-- zip [1,3,3,1] [3,3,1] => [(1,3),(3,3),(3,1)]
--                       1     4     6     4     1       
pascal :: [Int] -> [Int]
pascal [] = [1]
pascal [1] = [1, 1]
pascal arr = 1 : [a+b | (a, b) <- zip arr (tail arr)] ++ [1]

-- triangle will produce the n'th row directly of pascal's triangle
triangle :: Int -> [Int]
triangle 0 = [1]
triangle 1 = [1,1]
triangle n = pascal (triangle (n-1))

-- pascalTriangle will produce the full triangle to the n'th row
pascalTriangle :: Int -> [[Int]]
pascalTriangle n
  | n < 0 = []
  | otherwise = pascalTriangle (n-1) ++ [triangle n]


-- task 4 : caesar cipher and decipher
alphabet = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ"

-- lets just only do lowercase letters.... lol
letterToNumber :: Char -> Int
letterToNumber ch = head [i | (c, i) <- zip alphabet [0..], c == ch]

numberToLetter :: Int -> Char
numberToLetter n = alphabet !! (n `mod` 53)

shiftLetter :: Char -> Int -> Char
shiftLetter ch n = numberToLetter (letterToNumber ch+n)

cipher :: [Char] -> Int -> [Char]
cipher text n = map (`shiftLetter` n) text

-- just go cipher but in the opposite way
decipher :: String -> Int -> String
decipher text n = cipher text (-n)