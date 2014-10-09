CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000


VAR
  long value
    
PUB newSerialReceiver(val)
  setVal(val)

PUB setVal(val)
  value :=val

PUB getVal
  return value
  