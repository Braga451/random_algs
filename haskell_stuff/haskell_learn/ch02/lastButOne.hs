lastButOne l = if length l == 0 then error "Empty list"
                    else if length l == 1 then last l
                      else head ( drop ( (length l) - 2 ) l )
