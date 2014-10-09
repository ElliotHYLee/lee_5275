CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000


VAR
  long value
  long Stack[128]
  long cogIndex
  long serialIn
OBJ
  pst : "Parallax Serial Terminal"
    
PUB newSerialReceiver
  pst.Start(115200) 
  start

PUB start
  stop
  cogIndex := cognew(run, @Stack) + 1  'start running motor

PUB stop {{kind of destructor}}
  if cogIndex
    cogstop(cogIndex ~ - 1)
PUB run
  repeat
    if pst.RxCount > 0
      serialIn := pst.DecIn  ' it waits until new value comes in
      value := serialIn
      'pst.Dec(value)
      'pst.NewLine
    else
      'pst.Dec(value)
PUB getValue
  return value