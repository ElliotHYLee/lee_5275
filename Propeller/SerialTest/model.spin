CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000


VAR

  long value
OBJ
  pst : "Parallax Serial Terminal"
    
PUB newModel
  value :=0
  pst.Start(115200)
  repeat
    pst.Dec(value)
    pst.NewLine

PUB getValue
  return value
  
  