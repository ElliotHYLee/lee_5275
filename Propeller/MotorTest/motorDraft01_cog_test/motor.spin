CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR
  ' motor [0] = pin 0
  ' motor [1] = pin 1
  ' motor [2] = pin 2
  ' motor [3] = pin 3
  byte motor[4]
  long cogIndex       'this motor's cog index (1-8) 
  long StackA[128]
  long pulse
  byte pin
  long Stack[128]     'stack for this motor 
OBJ
  pst : "Parallax Serial Terminal"
    
PUB main
  pin:=0
  pst.Start(115200)
  setMotors(0)
  pulse :=45
  repeat while pulse < 120
    pst.Str(String(" asdf", pst#NL)) 
    pulse++
    outa[motor[0]]:=1
    waitcnt(cnt + (clkfreq / 1000 ) )
    outa[motor[0]]:=0
    waitcnt(cnt + clkfreq / 1000*20)    
    pst.Dec(pulse)
    pst.Str(String(" ", pst#NL))
  waitcnt(cnt + clkfreq)

  start
PUB start
  stopMotor
  cogIndex := cognew(runMotor, @Stack) + 1  'start running motor  
  
PUB stopMotor {{kind of destructor}}
  if cogIndex
    cogstop(cogIndex ~ - 1)  
  
PUB runMotor
  
  dira[motor[0]] := 1 
  pulse := 1200
  repeat  
    outa[motor[0]]:=1
    waitcnt(cnt + clkfreq / 1000000 * pulse )
    outa[motor[0]]:=0
    waitcnt(cnt + clkfreq / 1000*20)
    'pulse ++
    pst.Dec(pulse)
    pst.Str(String(" ", pst#NL))    
    'if pulse == 1200
    ' pulse:=1185 

PUB setMotors(void)
  motor[0] := 0
  motor[1] := 1
  motor[2] := 2
  motor[3] := 3
  dira[motor[0]] := 1
  dira[motor[1]] := 1
  dira[motor[2]] := 1
  dira[motor[3]] := 1     

PUB motorSpeed(pinNumber, outPut)
  dira[pin] := 1
  setMotor(pin)
  
  'Time := cnt    'asdf
  pulse := 1150
  repeat  while pulse < 1250
    
    outa[pin]:=1
    'waitcnt(cnt + microSec)
    outa[pin] :=0
    waitcnt(cnt + clkfreq / 1000*20)
    pulse += 1
    pst.Str(String("Im here 222222"))  
      

PUB setMotor(pinNumber)
  pst.Str(String("I'm here"))
  'Time := cnt
  pulse := 0
  repeat while pulse <=75
   ' microSec := clkfreq / 1000000 * pulse
    dira[pin] := 1
    outa[pin]:=1
   ' waitcnt(cnt + microSec)
    outa[pin] :=0
    waitcnt(cnt +  clkfreq / 1000*20)
    pulse += 1

  