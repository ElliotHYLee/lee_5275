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
  
PUB main |  charVar , a
  num.Init
  pst.Start(115200)
  value := 0
  repeat
    if pst.RxCount > 0
      pst.str(String("PRPLR sayz: received"))
      charVar := pst.CharIn
      pst.str(String("string is: "))
      pst.char(charVar)
      pst.newline
      changed := charVar
      'pst.StrInMax(@charVar, -1)      
      'a := str.decimalToInteger(charVar)
      pst.str(String("number is: "))
      pst.Dec(changed)
      pst.newline

  
  