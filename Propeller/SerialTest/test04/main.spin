CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  pst : "Parallax Serial Terminal"
  str: "data"
  num : "Numbers"

VAR
  long value  
  byte changed
  
PUB main |  stringVar , a
  num.Init
  pst.Start(115200)
  value := 0
  repeat
    if pst.RxCount > 0  
      pst.strIn(stringVar)
      pst.str(String("string is: "))
      pst.str(stringVar)
      pst.newline      
      a := num.FromStr(@stringVar, %000_000_000_0_0_000000_01010)
      pst.str(String("number is: "))
      pst.Dec(a)
      pst.newline

  
  