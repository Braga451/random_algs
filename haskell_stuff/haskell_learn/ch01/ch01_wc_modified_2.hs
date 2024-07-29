main = interact wordCount
    where wordCount input = "With \\n: " ++ show (length (input)) ++ "\n" ++ "Without: " ++ show (length (input) - length (lines (input))) ++ "\n"
