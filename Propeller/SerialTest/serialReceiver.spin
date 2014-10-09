CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000


VAR

  long serialIn
OBJ
  pst : "Parallax Serial Terminal"
    
PUB newSerialReceiver(model)
  pst.Start(115200)

PUB start


PUB stop

PUB run
  repeat
    serialIn := pst.DecIn  ' it waits until new value comes in
    pst.Str(String("Incoming value: "))
    pst.Dec(serialIn)
    pst.NewLine
        