(<"vBlock", vBlock>
   (<"vStmts", vStmts>
      (<"if", kIf>
         (<"&&", kAnd>
            (<"==", kEqual>
               <"i", kID>
               (<"+", +>
                  (<"*", *>
                     <"3", kNum>
                     <"4", kNum>
                  )
                  <"5", kNum>
               )
            )
            (<"<", <>
               (<"+", +>
                  <"j", kID>
                  <"i", kID>
               )
               (<"*", *>
                  (<"+", +>
                     <"7", kNum>
                     <"8", kNum>
                  )
                  <"5", kNum>
               )
            )
         )
         (<"vBlock", vBlock>
            (<"vStmts", vStmts>
               (<"=", =>
                  <"i", kID>
                  <"0", kNum>
               )
            )
         )
         (<"vBlock", vBlock>
            (<"vStmts", vStmts>
               (<"=", =>
                  <"j", kID>
                  <"0", kNum>
               )
            )
         )
      )
   )
)
{
  if ((i == ((3) * (4)) + (5)) && ((j) + (i) < ((7) + (8)) * (5))) {
    i = 0;
  }
  else {
    j = 0;
  }
}