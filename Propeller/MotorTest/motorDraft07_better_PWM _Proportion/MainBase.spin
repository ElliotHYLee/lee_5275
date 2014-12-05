CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  myAutoPilot : "AutoPilot.spin"

Var
  long   stack[128]
  byte cogIndex
PUB main
 
  myAutoPilot.startAutoPilot



PUB start
  stopMotor
  cogIndex:=cognew(pwm, @Stack) + 1  'start running motor  
  
PUB stopMotor {{kind of destructor}}
  if cogIndex
    cogstop(cogIndex ~ - 1)   