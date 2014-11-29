CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  usb : "Parallax Serial Terminal.spin"
  fNum : "FloatMath.spin"
  fString : "FloatString.spin"
VAR
 long pwm[4]
 long dirCos[3]

PUB main     | a,b,c
  usb.start(115200)
  


  a := fNum.Ffloat(0)
  b := fNum.Fmul(a,a)
  c := fNum.Fsqr(b)
  usb.dec(c)
  usb.newline
  usb.str(fString.FloatToString(c))

  
  
  