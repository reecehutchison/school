-- Part 1
chunk :: [a] -> Int -> [[a]]
chunk [] _ = []
chunk xs n = take n xs : chunk (drop n xs) n

loc :: Eq a => a -> [a] -> Int
loc x xs = foldr (\(i, v) acc -> if v == x then i else acc) (-1) (zip [0..] xs)

-- Part 2 

-- we took mult from last assignment --> num stuff bit different, just 
-- changed the range..
getCol :: [[a]] -> Int -> [a]
getCol arr n = [row !! n | row <- arr]

transp :: [[a]] -> [[a]]
transp [] = []
transp arr = [getCol arr i | i <- [0..(length (head arr) - 1)]]

isConformable :: [[a]] -> [[a]] -> Bool
isConformable mat1 mat2
  | null mat1 || null mat2 = False
  | length (head mat1) == length mat2 = True
  | otherwise = False

dotProd :: [Int] -> [Int] -> Int
dotProd [] [] = 0
dotProd (a:vec1) (b:vec2) = (a*b) + dotProd vec1 vec2

procRow :: [Int] -> [[Int]] -> [Int]
procRow row = map (dotProd row)

matMult :: [[Int]] -> [[Int]] -> [[Int]]
matMult mat1 mat2
  | not (isConformable mat1 mat2) = []
  | otherwise = map (`procRow` mat2T) mat1
      where mat2T = transp mat2

alphabet :: String
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

letterToNum :: Char -> Int
letterToNum ch = head [i | (c, i) <- zip alphabet [0..], c == ch]

numToLetter :: Int -> Char
numToLetter n = alphabet !! (n `mod` 26)

-- end of last assignment

-- using chunk from part 1 to separate msg into groups of 3
msgToMatrix :: String -> [[Int]]
msgToMatrix msg = transp (chunk (map letterToNum msg) 3)

key :: [[Int]]
key = [[6,24,1],[13,16,10],[20,17,15]]

inverse :: [[Int]]
inverse = [[8,5,10],[21,8,21],[21,12,8]]

-- convert msg to matrix, multiply by given matrix, mod 26 each entry, convert back to string
hillCipher :: [[Int]] -> String -> String -- note we pass a map to another map to do 2d arr!
hillCipher mat msg = map numToLetter (concat (transp (map (map (`mod` 26)) (matMult mat (msgToMatrix msg)))))

cipher :: String -> String
cipher msg = hillCipher key msg

decipher :: String -> String
decipher msg = hillCipher inverse msg