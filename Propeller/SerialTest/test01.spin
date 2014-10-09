CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000


VAR

  long value
OBJ
  pst : "Parallax Serial Terminal"
  sRec : "serialReceiver"
  model : "model"
    
PUB main
  value :=0
  model.newModel
  sRec.newSerialReceiver(model.getValue) 

  
  
  