void motorSpeed(byte motor, byte percentSpeed)
{
  byte s=map(percentSpeed,0,100,0,255); 
  switch (motor) 
  {   
  case 1:
    digitalWrite(stbyPin1,HIGH);
    analogWrite(pwmPin1,s);
    break;
  case 2:
    digitalWrite(stbyPin2,HIGH);
    analogWrite(pwmPin2,s);
    break;
  case 3:
    digitalWrite(stbyPin3,HIGH);
    analogWrite(pwmPin3,s);
    break;
  default: 
    digitalWrite(stbyPin1,HIGH);
    analogWrite(pwmPin1,s);
    digitalWrite(stbyPin2,HIGH);
    analogWrite(pwmPin2,s);
    digitalWrite(stbyPin3,HIGH);
    analogWrite(pwmPin3,s);
  }
}

