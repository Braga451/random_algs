data Maybe a = Just a
             | Nothing
               deriving (Show)

data Tree a = Node a (Main.Maybe(Tree a)) (Main.Maybe(Tree a))
              deriving (Show)

simpleTree = Node "parent" (Main.Just(Node "left child" Main.Nothing Main.Nothing)) (Main.Just(Node "right child" Main.Nothing Main.Nothing))
