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
' /      :  47/_______//////////

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
  
PUB readCharArray   |  varChar , ascii
    if pst.RxCount > 0
      'waitcnt(cnt + clkfreq*2)
      varChar := pst.CharIn
      ascii := char2ASCII(@varChar)

      
<<<<<<< HEAD
                
      pst.newline
=======
>>>>>>> origin/master
      if (ascii =>48 AND ascii=<57) 'btw 0-9
        total := total*10 + ASCII2Dec(ascii)
      elseif(ascii ==77)
        type := 1
<<<<<<< HEAD
                               
      elseif(ascii == 47)  'empty char
=======
       
      elseif(ascii ==95)   'empty char  
>>>>>>> origin/master
        if type==1
          pst.str(String("Motor"))
          pst.newline
        pst.str(String("total : "))
        'pst.dec(total)
        pst.newline  
        pst.str(String("reset total: "))
        total:= 0  
        pst.Dec(total)
        pst.newline
        type := 0
        pst.RxFlush
 