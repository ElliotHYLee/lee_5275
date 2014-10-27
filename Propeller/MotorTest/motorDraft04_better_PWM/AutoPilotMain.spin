CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000
  
OBJ
  ' motor[0] = pin 0, cw
  ' motor[1] = pin 1, ccw
  ' motor[2] = pin 2, cw
  ' motor[3] = pin 3, ccw
  motors : "MotorControl"
  pst : "Parallax Serial Terminal"

VAR
  long pin[4]
  long pwm1, pwm2, pwm3, pwm4
  long value
  
PUB main | i

  pst.Start(115200)
  pst.Str(String("setting pins..."))
  pst.NewLine
  setPins
  pst.Str(String("setting motor 1..."))
  pst.NewLine
  motors.newMotor(pin[0], pin[1], pin[2], pin[3]) 'set pin numbre 0 for the fist motor
  pst.str(pin)
  repeat
   if pst.RxCount > 0  
    value := pst.DecIn
    motors.motor1_setPWM(value)
   else
    pwm1 := motors.motor1_getPWM
    pwm2 := motors.motor2_getPWM
    pwm3 := motors.motor3_getPWM
    pwm4 := motors.motor4_getPWM
    pst.Dec(pwm1)
    pst.Str(String(", "))
    pst.Dec(pwm2)
    pst.Str(String(", "))
    pst.Dec(pwm3)
    pst.Str(String(", "))
    pst.Dec(pwm4)
    pst.NewLine 

  


PUB setPins
  pin[0] := 0
  pin[1] := 1
  pin[2] := 2
  pin[3] := 3


  