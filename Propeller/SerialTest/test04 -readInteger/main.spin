CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  pst : "Parallax Serial Terminal"
  num : "Numbers"

VAR
  long value, stringVar   
  byte changed
  
PUB main |   a
  num.Init
  pst.Start(115200)
  value := 0
  repeat
    if pst.RxCount > 0
      pst.str(String("PRLR sayz: received"))
      pst.strIn(@stringVar)
      pst.newline
      pst.str(String("value is: "))
      pst.str(@stringVar)
      pst.newline      
      pst.newline
    else
      'pst.newline
  
  