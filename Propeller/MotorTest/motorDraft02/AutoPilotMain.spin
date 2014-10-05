OBJ
  ' motor[1] = pin 0, cw
  ' motor[2] = pin 1, ccw
  ' motor[3] = pin 2, cw
  ' motor[4] = pin 3, ccw
  motor[4] : "Motor"
  pst : "Parallax Serial Terminal"

VAR
  byte pin0
  byte pin1
  byte pin2
  byte pin3  
  
PUB main
  motor[1].newMotor(0, 1) 'set pin numbre 0 for the fist motor

PUB setPins
  pin0 := 0
  pin1 := 1
  pin2 := 2
  pin3 := 3