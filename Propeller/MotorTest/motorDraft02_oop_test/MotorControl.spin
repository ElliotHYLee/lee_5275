CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR     'object variables                            

  long cogIndex       'this motor's cog index (1-8)
  long Stack[128]     'stack for this motor
  long pulse          'the pulse of this motor
  byte motorPin       'the pin number for this motor
  byte isCW           '1(true) if this motor is counter clock wise, or 0(false)
OBJ     ' import below objects

  pst : "Parallax Serial Terminal"

PUB newMotor(pin, direction) {{ constructor }}
  pst.Start(115200)
  motorPin := pin  'set pin number for this motor
  isCW := direction 'whether the rotation is cw(true, 1) or ccw(flase, 0)      
  initMotor  'physical initialization for this motor
  waitcnt(cnt + clkfreq)
  startMotor
  
PUB startMotor
  stopMotor
  cogIndex := cognew(runMotor, @Stack) + 1  'start running motor

PUB getDirection {{ return direction of this motor}}
  return isCW
         
PUB updatePWM(newPulse) {{update the pulse of this so "runMotor" method can use the new value}}
  pulse := newPulse

PUB stopMotor {{kind of destructor}}
  if cogIndex
    cogstop(cogIndex ~ - 1)
  
PUB runMotor {{generating pwm for the motor connected to this pin}}              
  dira[motorPin] := 1
  pulse := 1190
  repeat  
    outa[motorPin]:= 1
    waitcnt(cnt + clkfreq / 1000000 * pulse )
    outa[motorPin]:= 0
    waitcnt(cnt + clkfreq / 1000*20)
    pst.Dec(cogIndex)
    pst.Str(String(", "))
    pst.Dec(motorPin)
    pst.Str(String(", ")) 
    pst.Dec(pulse)
    pst.Str(String(" ", pst#NL))    

PUB initMotor {{initializing the motor connected to this pin}}    
  dira[motorPin] := 1   'set pin direction for this motor   
  pulse :=45
  repeat while pulse < 150
    pulse++
    outa[motorPin]:=1
    waitcnt(cnt + (clkfreq / 1000 ) )
    outa[motorPin]:=0
    waitcnt(cnt + clkfreq / 1000*20)    
    pst.Dec(pulse)
    pst.Str(String(" ", pst#NL))


  
  