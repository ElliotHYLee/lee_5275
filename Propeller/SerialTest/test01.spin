CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  pst : "Parallax Serial Terminal"
    
PUB main
  pst.Start(115200)
  pst.Dec(123456789)
  pst.Str(String(" abc", pst#NL))  
