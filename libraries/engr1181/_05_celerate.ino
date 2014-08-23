void celerate(byte motor, byte startSpeed,byte endSpeed, int seconds)
{
  if (motor<1) motor=1;
  if (motor>4) motor=4;
  if (startSpeed<0) startSpeed=0;
  if (startSpeed>100) startSpeed=100;
  if (endSpeed<0) endSpeed=0;
  if (endSpeed>100) endSpeed=100;
  if (seconds<1) seconds=1;
  if (seconds >10) seconds=10;
  // create 1/4 second periods
  // gives 250 ms to make incremental changes and get samples
  byte periods=seconds*4;
  byte speedIncrement=abs(startSpeed-endSpeed)/periods;
  if (speedIncrement<0) speedIncrement=1;
  byte s=map(startSpeed,0,100,0,255); 
  byte e=map(endSpeed,0,100,0,255);
  byte is=map(speedIncrement,0,100,1,255);
  byte x=s; 
  do
  {
    switch (motor) 
    {   
    case 1:
      digitalWrite(stbyPin1,HIGH);
      analogWrite(pwmPin1,x);
      break;
    case 2:
      digitalWrite(stbyPin2,HIGH);
      analogWrite(pwmPin2,x);
      break;
    case 3:
      digitalWrite(stbyPin3,HIGH);
      analogWrite(pwmPin3,x);
      break;
    default: 
      digitalWrite(stbyPin1,HIGH);
      analogWrite(pwmPin1,x);
      digitalWrite(stbyPin2,HIGH);
      analogWrite(pwmPin2,x);
      digitalWrite(stbyPin3,HIGH);
      analogWrite(pwmPin3,x);
    }
    metroAcc.interval(240);
    metroAcc.reset();
    do
    { 
      goFor(1);
    } 
    while(!metroAcc.check()==1);
    if ((e-s)>0) x=x+is;
    else x=x-is;
    periods--;
  }
  while (periods>0);
}

