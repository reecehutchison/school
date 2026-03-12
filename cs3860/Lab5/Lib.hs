module Lib where

import Data.List (sort)

data TTTree a = Leaf | Node a (TTTree a) (TTTree a) (TTTree a)
  deriving (Show, Eq, Ord)

inorder :: TTTree a -> [a]
inorder Leaf = []
inorder (Node val left mid right) = inorder left ++ [val] ++ inorder mid ++ inorder right

height :: TTTree a -> Int
height Leaf = 0
height (Node _ left mid right) = 1 + max (max (height left) (height mid)) (height right)

balance :: TTTree a -> Bool
balance Leaf = True
balance (Node _ left mid right) = height left == height mid && height mid == height right

ordered :: (Ord a) => TTTree a -> Bool
ordered Leaf = True
ordered tree = inorder tree == sort (inorder tree)

tree1 :: TTTree Int
tree1 = Node 5
  (Node 2 Leaf Leaf Leaf)
  (Node 5 Leaf Leaf Leaf)
  (Node 8 Leaf Leaf Leaf)

tree2 :: TTTree Int
tree2 = Node 9
  (Node 12 (Node 1 Leaf Leaf Leaf) Leaf Leaf)
  Leaf
  (Node 3 Leaf Leaf Leaf)

instance Functor TTTree where
  fmap :: (a -> b) -> TTTree a -> TTTree b
  fmap _ Leaf = Leaf
  fmap f (Node val left mid right) = Node (f val) (fmap f left) (fmap f mid) (fmap f right)