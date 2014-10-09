CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR

  long value
OBJ
  pst : "Parallax Serial Terminal"
  sRec: "serialReceiver"
    
PUB main
  pst.Start(9600)  
  value :=0
  sRec.newSerialReceiver 
  repeat
   pst.Dec(sRec.getValue)
 


  
  