void brake(byte motor)
{
  switch (motor) 
  {   
  case 1:
    analogWrite(pwmPin1,0);
    digitalWrite(stbyPin1,LOW);
    break;
  case 2:
    analogWrite(pwmPin2,0);
    digitalWrite(stbyPin2,LOW);
    break;
  case 3:
    analogWrite(pwmPin1,0);
    digitalWrite(stbyPin3,LOW);
    break;
  default: 
    analogWrite(pwmPin1,0);
    digitalWrite(stbyPin1,LOW);
    analogWrite(pwmPin2,0);
    digitalWrite(stbyPin2,LOW);
    analogWrite(pwmPin3,0);
    digitalWrite(stbyPin3,LOW);
  }
}

