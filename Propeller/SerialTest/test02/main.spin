CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR

  long value
OBJ
  pst : "Parallax Serial Terminal"
  ser: "serialReceiver"
    
PUB main
  pst.Start(115200)
  pst.Str(String("Seiral Ready"))

  ser.newSerialReceiver(value)
  pst.Dec(ser.getVal)
  pst.NewLine
  repeat
   if pst.RxCount > 0  
    value := pst.DecIn
    ser.setVal(value)
   else
    value:=ser.getVal
    pst.Dec(value)
    pst.NewLine


  
  