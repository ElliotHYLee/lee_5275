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
  
PUB main | i, motorNumber

  pst.Start(115200)
  setPins

  motors.newMotor(pin[0], pin[1], pin[2], pin[3]) 'set pin numbers for the four motors
  repeat
    if pst.RxCount > 0  
      value := pst.DecIn
      if value<43000 AND value>11200
        motorNumber := value/10000
        value := value//10000
        case motorNumber
          1: motors.motor1_setPWM(value)
          2: motors.motor2_setPWM(value)
          3: motors.motor3_setPWM(value)
          4: motors.motor4_setPWM(value)
       
    else
      value := motors.motor1_getPWM
      pst.Dec(value)
      pst.str(string(", "))
      value := motors.motor2_getPWM
      pst.Dec(value)
      pst.str(string(", "))
      value := motors.motor3_getPWM
      pst.Dec(value)
      pst.str(string(", "))
      value := motors.motor4_getPWM
      pst.Dec(value)
      pst.newline

PUB setPins
  pin[0] := 0
  pin[1] := 1
  pin[2] := 2
  pin[3] := 3


  