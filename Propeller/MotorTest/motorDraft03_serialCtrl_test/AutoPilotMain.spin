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
  long pin[4]
  long value
  
PUB main
  pst.Start(115200)
  pst.Str(String("setting pins..."))
  pst.NewLine
  setPins
  pst.Str(String("setting motor 1..."))
  pst.NewLine
  motor[0].newMotor(pin[0], 1) 'set pin numbre 0 for the fist motor
  repeat
   if pst.RxCount > 0  
    value := pst.DecIn
    motor[0].setPWM(value)
   else
    value:=motor[0].getPWM
    pst.Dec(value)
    pst.NewLine


PUB setPins
  pin[0] := 0
  pin[1] := 1
  pin[2] := 2
  pin[3] := 3