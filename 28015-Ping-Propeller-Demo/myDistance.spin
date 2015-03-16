CON

  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000
  
  trigPin = 14
  echoPin = 15
  
OBJ
  
  usb : "Parallax Serial Terminal"
  
VAR
  Long duration, distance  ,i

PUB main | base
  usb.Start(9600)
  dira[trigPin] := 1
  dira[echoPin] := 0
  usb.Str(String("asfasd"))
  repeat
      outa[trigPin] := 0
      waitcnt(cnt + clkfreq/1000000*100)
      outa[trigPin] := 1
      waitcnt(cnt + clkfreq/1000000*33)
      outa[trigPin] := 0
      base := cnt
      usb.newline 
      repeat while (ina[echoPin]==1)
        usb.dec(ina[echoPin])
        usb.newline
      duration := cnt - base  
      usb.Dec(duration)
      waitcnt(cnt + clkfreq/1000*100)
          '  distance = (duration/2) / 29.1;    