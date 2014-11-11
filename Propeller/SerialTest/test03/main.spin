CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  pst : "Parallax Serial Terminal"
  str: "data"
  motors :"MotorControl"

VAR
  long pin[4]
  long pwm1, pwm2, pwm3, pwm4
  long value  
  byte changed
  
PUB main |  stringVar , motorNumber
  pst.Start(115200)
  motors.newMotor(pin[0], pin[1], pin[2], pin[3]) 'set pin numbers for the four motors
  changed :=1
  repeat
    if pst.RxCount > 0  
      value := pst.strIn(stringVar)
      value := str.decimalToInteger(value)
      pst.str(String("asdfasdfasdfasfasdfasdfasdfasdf"))
 

  
  