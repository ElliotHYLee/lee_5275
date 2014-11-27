CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR
 long pwm[4]
 long dirCos[3]
  
OBJ
  mainData     : "data.spin"
  reporterData : "data.spin"
  actuatorData : "data.spin"
  
PUB main | i

  
  reporterData.Start  

  i :=0
  repeat 4
    pwm[i] := 50 
    i++

  i:=0
  repeat 3
    dirCos[i] := i*2
    i++
      
  shareObjects

  repeat
    if reporterData.getPwm(0) == pwm[0]
      reporterData.setPwm(1, 77) 
    else
      reporterData.setPwm(2, 33)
   
PUB shareObjects
  reporterData.receiveMe(@pwm[0], @pwm[1], @pwm[2], @pwm[3], @dirCos[0], @dirCos[1],@dirCos[3]) 
  'actuatorData.receiveMe(@pwm[0], @pwm[1], @pwm[2], @pwm[3], @dirCos[0], @dirCos[1],@dirCos[3])  


  
 

