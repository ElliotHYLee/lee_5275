CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000
  
OBJ
  ' motor[0] = pin 0, cw
  ' motor[1] = pin 1, ccw
  ' motor[2] = pin 2, cw
  ' motor[3] = pin 3, ccw
  motor[4] : "MotorControl"
  pst : "Parallax Serial Terminal"

VAR
  byte pin0
  byte pin1
  byte pin2
  byte pin3  
  
PUB main
  setPins
  motor[0].newMotor(pin0, 1) 'set pin numbre 0 for the fist motor
  

PUB setPins
  pin0 := 0
  pin1 := 1
  pin2 := 2
  pin3 := 3