' motor1 = ccw
' motor2 = cw
' motor3 = ccw
' motor4 = cw

CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR     'object variables                            

  long cogIndex       'this motor's cog index (1-8)
  long Stack[128]     'stack for this motor
  long pulse[4]          'the pulse of this motor
  long motorPin[4]    'the pin number for this motor
  
OBJ     ' import below objects

  'pst : "Parallax Serial Terminal"

PUB newMotor(pin0, pin1, pin2, pin3)  {{ constructor }}
  motorPin[0] := pin0  'set pin number for this motor
  motorPin[1] := pin1
  motorPin[2] := pin2
  motorPin[3] := pin3
  waitcnt(cnt + clkfreq)

  start
  
PUB start
  stop
  cogIndex := cognew(runMotor, @Stack) + 1  'start running motor

PUB stop {{kind of destructor}}
  if cogIndex
    cogstop(cogIndex ~ - 1)

PUB initMotor | i                                             {{initializing the motor connected to this pin}}
  i:=0                       'set pin directions               
  repeat while i<4
    dira[motorPin[i]] := 1
    pulse[i] :=45
    i++  
  
  repeat while pulse[0] < 150
    i:=0  
    repeat while i<4
      outa[motorPin[i]]:=1
      waitcnt(cnt + (clkfreq / 1000 ) )
      outa[motorPin[i]]:=0
      pulse[i] ++
      i++
    waitcnt(cnt + clkfreq / 1000*20)
       

PUB runMotor | baseTime, i, totalElapse                 {{generating pwm for the motor connected to this pin}}              
  
  initMotor  'physical initialization for this motor 
  i:=0
  repeat while i<4
    dira[motorPin[i]] := 1   'set pin direction for this motor 
    pulse[i] := 1250         'set default pwm
    i++

  repeat  
    
    totalElapse:=0

    baseTime := cnt    
    outa[motorPin[0]]:= 1
    waitcnt(baseTime + clkfreq/1000000*pulse[0])
    outa[motorPin[0]]:= 0

      
    outa[motorPin[1]]:= 1 
    waitcnt(cnt + clkfreq/1000000*pulse[1])
    outa[motorPin[1]]:= 0

     
    outa[motorPin[2]]:= 1
    waitcnt(cnt + clkfreq/1000000*pulse[2])
    outa[motorPin[2]]:= 0

     
    outa[motorPin[3]]:= 1
    waitcnt(cnt + clkfreq/1000000*pulse[3])
    outa[motorPin[3]]:= 0
     
    totalElapse := pulse[0] + pulse[1] + pulse[2] + pulse[3]

    
    waitcnt(baseTime + (clkfreq/1000*20 - clkfreq/1000000*totalElapse))
    
  ' waitcnt(baseTime + (clkfreq/1000*20 - clkfreq/1000000*(pulse[0]+ pulse[1])+pulse[2]+ pulse[3])))




    
    
PUB motor1_setPWM(newPulse)                                    {{update the pulse of this so "runMotor" method can use the new value}}
  pulse[0] := newPulse

PUB motor2_setPWM(newPulse)                                    {{update the pulse of this so "runMotor" method can use the new value}}
  pulse[1] := newPulse

PUB motor3_setPWM(newPulse)                                    {{update the pulse of this so "runMotor" method can use the new value}}
  pulse[2] := newPulse

PUB motor4_setPWM(newPulse)                                    {{update the pulse of this so "runMotor" method can use the new value}}
  pulse[3] := newPulse
  

  
pub motor1_getPinNumber
  return motorPin[0]

pub motor2_getPinNumber
  return motorPin[1]

pub motor3_getPinNumber
  return motorPin[2]

pub motor4_getPinNumber
  return motorPin[3]

        

PUB motor1_getPWM
  return pulse[0]
  
PUB motor2_getPWM
  return pulse[1]
  
PUB motor3_getPWM
  return pulse[2]
  
PUB motor4_getPWM
  return pulse[3]


  
 