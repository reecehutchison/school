import Lib

main :: IO ()
main = do
  let t = tree1
  putStrLn $ show t
  putStrLn $ show (inorder t)
  putStrLn $ show (height t)
  putStrLn $ show (balance t)
  putStrLn $ show (ordered t)
  putStrLn $ show $ fmap (== 5) t
