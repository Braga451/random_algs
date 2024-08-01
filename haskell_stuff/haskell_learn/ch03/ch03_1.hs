data List a = Cons a (List a)
            | Nil
              deriving (Show)

fromList Nil = []
fromList (Cons a b) = [a] ++ fromList b
