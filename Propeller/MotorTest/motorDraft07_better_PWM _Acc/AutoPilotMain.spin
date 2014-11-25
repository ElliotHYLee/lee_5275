CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000
  
OBJ
  ' motor[0] = pin 0, cw
  ' motor[1] = pin 1, ccw
  ' motor[2] = pin 2, cw
  ' motor[3] = pin 3, ccw
  motors : "MotorControl"
  pst    : "Parallax Serial Terminal"
  nums   : "Numbers"

VAR
  long pin[4]
  long pwm1, pwm2, pwm3, pwm4
  long value
  long newValue
  byte type

' Char   :  ASCII
' 0      :  48
' 1      :  49
' 9      :  57
' M      :  77
' C      :  67

' type      :  number
' Motor     :  1
' ascend    :  2
' descend   :  3
' advance   :  4
' ....... 
PUB main 
  nums.Init
  pst.Start(115200)
  setPins
  motors.newMotor(pin[0], pin[1], pin[2], pin[3]) 'set pin numbers for the four motors
  repeat
    if pst.RxCount > 0  
      readCharArray
    else
      pst.str(String("M1"))
      value := motors.motor1_getPWM
      pst.Dec(value)
      pst.str(string("M2"))
      value := motors.motor2_getPWM
      pst.Dec(value)
      pst.str(string("M3"))
      value := motors.motor3_getPWM
      pst.Dec(value)
      pst.str(string("M4"))
      value := motors.motor4_getPWM
      pst.Dec(value)



PUB setPins
  pin[0] := 0
  pin[1] := 1
  pin[2] := 2
  pin[3] := 3

PUB char2ASCII(charVar)  ' currently not used
  result := byte[charVar]
  ' Don't know how, but this returns ascii code of char

PUB ASCII2Dec(ASCII)
  result := ASCII - 48    
  
PUB readCharArray   |  varChar , ascii, newPWM, motorNumber
   varChar := pst.CharIn
   if (varChar =>48 AND varChar=<57) 'btw 0-9
     newValue := newValue*10 + ASCII2Dec(varChar)
   elseif(varChar ==77) ' M -> motor
     type := 1  'next 5 digits are (motornumber & pwm)
   elseif(varChar == 67)
     type := 2  'number is not yet determined

   if (type==1)
     if newValue<43000 AND newValue>11200
       motorNumber := newValue/10000
       newPWM := newValue//10000
       case motorNumber
        1: motors.motor1_setPWM(newPWM)
        2: motors.motor2_setPWM(newPWM) 
        3: motors.motor3_setPWM(newPWM) 
        4: motors.motor4_setPWM(newPWM)
       type := 0
       newValue := 0
       'waitcnt(cnt + clkfreq*3)

        
PUB clear
  
  