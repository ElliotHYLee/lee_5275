void reverse()
{
  if (digitalRead(fwdHighPin)==HIGH)
  {
    digitalWrite(fwdHighPin,LOW);
    digitalWrite(fwdLowPin,HIGH); 
  }
  else
  {
    digitalWrite(fwdHighPin,HIGH);
    digitalWrite(fwdLowPin,LOW);
  }     
}
