CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  pst : "Parallax Serial Terminal"
  str: "data"
  num : "Numbers"   

VAR
  long total
  byte type
  
' Char   :  ASCII
' 0      :  48
' 1      :  49
' 9      :  57
' M      :  77

' type      :  number
' Motor     :  1
' ascend    :  2
' descend   :  3
' advance   :  4
' ....... 
  
PUB main 
  num.Init
  pst.Start(115200)
  total := 0 
  repeat
   readCharArray
   
    

PUB char2ASCII(charVar) | index
  result := byte[charVar]

PUB ASCII2Dec(ASCII)
  result := ASCII - 48    
  
PUB readCharArray   |  varChar , ascii, garbage
    if pst.RxCount > 0
      'waitcnt(cnt + clkfreq*2)
      varChar := pst.CharIn
      pst.char(varChar)
      'ascii := char2ASCII(@varChar)
      if (varChar==77)
        type :=1
        repeat 5
          'pst.str(String("Im here"))
          varChar :=pst.CharIn
          pst.char(varChar)
          ascii := char2ASCII(@varChar)
          total := total*10 + ASCII2Dec(ascii)
        repeat while pst.RxCount > 0
          garbage := pst.DecIn
        pst.str(String("fulshing"))
        pst.newline
        report
        pst.str(String("reset total: "))
        total:= 0  
        pst.Dec(total) 
        pst.newline
        type := 0
      else
        'pst.str(String("asdfasfd"))
PUB report
  pst.str(String("Motor"))
  pst.newline
  pst.str(String("total is: "))
  pst.Dec(total)
  pst.newline  

