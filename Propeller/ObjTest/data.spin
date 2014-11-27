CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ
  reporter : "Parallax Serial Terminal.spin"
    
VAR
  long pwm[4]
  long dirCos[3]
  long cogIndex
  long stack[128]
PUB receiveMe(pwm0, pwm1, pwm2, pwm3, dirCos0, dirCos1, dirCos2)
' calling this method should be filled by controller main
' ex) same type objname = x 
' x.receiveMe(@my.getPwm(0), @my.getPwm(1), @my.getPwm(2), @my.getPwm(3), @my.getdirCos(0),@my.getdirCos(1),@my.getdirCos(2)
  
  pwm[0] := pwm0
  pwm[1] := pwm1
  pwm[2] := pwm2
  pwm[3] := pwm3
  dirCos[0] := dirCos0
  dirCos[1] := dirCos1
  dirCos[2] := dirCos2

PUB setPwm(number, newPwm)
  if (number>=0 AND number <=3)
    pwm[number] := newPwm
    reporter.str(String("recieved"))

PUB getPwm(number)
  if (number>=0 AND number <=3)
    return pwm[number]  

PUB setDirCos(axisNum, value)
 if (axisNum>=0 AND axisNum <=2)   
   dirCos[axisNum] := value
   
PUB getDirCos(axisNum)
 if (axisNum>=0 AND axisNum <=2)
   return dirCos[axisNum]

PUB reporterStart | i
  'rx=31
  'tx=30
  reporter.Start(115200)
  
  repeat
    i:=0
    repeat 4
      reporter.str(String("pwm"))
      reporter.dec(i)
      reporter.str(String("= "))
      reporter.Dec(pwm[i])
      reporter.newLine
      i++

    i:=0
    repeat 3
      reporter.str(String("dirCos= "))
      reporter.Dec(dirCos[i])
      reporter.newLine
      i++

    if reporter.RxCount > 0
      pwm[0] := 111
      
   ' waitcnt(cnt + clkfreq*2)

PUB start
  stop
  cogIndex := cognew(reporterStart, @Stack) + 1  'start running motor

PUB stop {{kind of destructor}}
  if cogIndex
    cogstop(cogIndex ~ - 1)

