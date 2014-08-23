  int STATE=1;
  int Arming_Time=0;
  int Motor2=3;
  int Pulse=1000;
  int last = 1350;


void setup()
{
  int STATE=1;
  int Arming_Time=0;
  int Motor2=3;
  int Pulse=1000;
  int last = 1350;
  pinMode(Motor2, OUTPUT);
  
  for (Pulse = 0; Pulse <=500; Pulse +=1)
  {
    // HIGH and LOW: alternating signal: generating voltage!
    digitalWrite(Motor2, HIGH);
    delayMicroseconds(1100);
    digitalWrite(Motor2, LOW);
    delay(20); //delay(20-(Pulse/1000));
  }
  
 }
void loop()
{
  
  for (Pulse = 1150; Pulse <=last; Pulse +=1)
  {
    digitalWrite(Motor2, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(Motor2, LOW);
    delay(20);//delay(20-(Pulse/1000));
  }

  for (Pulse = last; Pulse >=1150; Pulse-=1)
  {
    digitalWrite(Motor2, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(Motor2, LOW);
    delay(20);//delay(20-(Pulse/1000));
  }
    
}


