OBJ
  SERVO : "Servo32v7.spin"

CON
    _clkmode = xtal1 + pll16x                           
    _xinfreq = 5_000_000 

    ServoCh1 = 0                ' Servo to pin 0

PUB Servo32_DEMO

    SERVO.Start                 ' Start servo handler
    
  repeat
    ' Syntax: SERVO.Set(Pin, Width)
    SERVO.Set(ServoCh1,500)   
    waitcnt(cnt + clkfreq*1)
    SERVO.Set(ServoCh1,0)   
    waitcnt(cnt + clkfreq*1)              
    SERVO.Set(ServoCh1,500)   
    waitcnt(cnt + clkfreq*1)
    SERVO.Set(ServoCh1,1000)   
    waitcnt(cnt + clkfreq*1)
    SERVO.Set(ServoCh1,1500)   
    waitcnt(cnt + clkfreq*1)
    SERVO.Set(ServoCh1,2000)   
    waitcnt(cnt + clkfreq*1)
    SERVO.Set(ServoCh1,2500)   
    waitcnt(cnt + clkfreq*1)  
    