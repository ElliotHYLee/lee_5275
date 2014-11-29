CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

OBJ

  pst : "Parallax Serial Terminal.spin"
  adc : "PropBOE ADC"
  time: "Timing"
Var
  long ad

PUB Go

  repeat
    ad := adc.In  