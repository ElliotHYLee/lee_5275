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
  motorPin := pin  'set pin number for this motor
  isCW := direction 'whether the rotation is cw(true, 1) or ccw(flase, 0)      
  dira[motorPin] := 1   'set pin direction for this motor   
  initMotor  'physical initialization for this motor   
  cogIndex := cognew(runMotor, @Stack) + 1  'start running motor

PUB getDirection {{ return direction of this motor}}
  return isCW
         
PUB updatePWM(newPulse) {{update the pulse of this so "runMotor" method can use the new value}}
  pulse := newPulse

PUB stopMotor {{kind of destructor}}
  if cogIndex
    cogstop(cogIndex ~ - 1)
  
PRI runMotor {{generating pwm for the motor connected to this pin}}              
  repeat  
    outa[motorPin]:=1
    waitcnt(cnt + clkfreq / 1000000 * pulse )
    outa[motorPin]:=0
    waitcnt(cnt + clkfreq / 1000*20)
    pulse ++
    pulse --
    pst.Dec(pulse)
    pst.Str(String(" ", pst#NL))    

PRI initMotor {{initializing the motor connected to this pin}}    
  pulse :=0
  repeat while pulse < 75
    outa[motorPin]:=1
    waitcnt(cnt + clkfreq / 1000000 * pulse )
    outa[motorPin]:=0
    waitcnt(cnt + clkfreq / 1000*20)
  pulse := 1200  'set default pulse 
  