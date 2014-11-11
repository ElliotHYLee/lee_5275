CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR

  long value
OBJ
  pst           : "Parallax Serial Terminal"
  f             : "Float32"
  fstring        : "FloatString"
PUB main| a,b

  pst.Start(115200)
  f.start
  a := f.ffloat(3)
  b := f.ffloat(2)
  a :=f.fdiv(a,b)
  pst.str(fstring.FloatToString(a))
  

 
  