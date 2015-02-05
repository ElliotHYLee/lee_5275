CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  pst           : "Parallax Serial Terminal"
  fNum          : "FloatMath"
  fStr          : "FloatString"
var
  long prevTime , dt
PUB main
  pst.start(115200)
  prevTime := cnt  
  dt := fNum.FFloat(dt)
  
  repeat
    dt := fNum.FDiv(fNum.FFloat(cnt - prevTime), fNum.FFloat(clkfreq))
    pst.str(fStr.FloatToString(dt))
    pst.newline
    prevTime := cnt   
     