OBJ
  SERVO : "Servo32v7.spin"
  usb: "Parallax Serial Terminal"
CON
  _clkmode = xtal1 + pll16x                           
  _xinfreq = 5_000_000 

  ServoCh1 = 0                ' Servo to pin 0
  sMin = 559  '-90 deg
  sMax = 2443 '+90 deg
PUB Servo32_DEMO
  usb.start(115200)
  SERVO.Start                 ' Start servo handler
    
  repeat
    servoPoseAt(0)   
    waitcnt(cnt + clkfreq/1000000*50)


PUB servoPoseAt(angleDeg) | y, m
  m := (sMax-sMin)/180
  'usb.dec(m)
  'usb.newline
  y := m*(angleDeg-90) + sMax
  usb.dec(y)
  usb.newline
  Servo.set(ServoCh1, y)
 


