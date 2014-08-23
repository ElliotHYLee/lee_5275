int STATE=1;
int Arming_Time=0;
int pin0=0;
int pin1=1;
int pin2=2;
int pin3=3;
int Pulse=1000;
int last = 1350;

void setup()
{
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  for (Pulse = 0; Pulse <=500; Pulse +=1)
  {
    digitalWrite(pin0, HIGH);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    delayMicroseconds(1100);
    digitalWrite(pin0, LOW);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    delay(20-(Pulse/1000));
  }
  
 }
void loop()
{
  for (Pulse = 1150; Pulse <=last; Pulse +=1)
  {
    digitalWrite(pin0, HIGH);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(pin0, LOW);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    delay(20-(Pulse/1000));
  }
  for (Pulse = last; Pulse >=1150; Pulse-=1)
  {
    digitalWrite(pin0, HIGH);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(pin0, LOW);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    delay(20-(Pulse/1000));
  }
  
  
}


