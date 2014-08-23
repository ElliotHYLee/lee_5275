void setup()
{
  pinMode(12, OUTPUT);
     
}

void loop()
{
  int pin = 12;
  int tempo = 5;
  int a=40;
  int b=30;
  int loopinterval = 300;
  int binterval = 60;
  a=a*tempo;
  b=b*tempo;
  loopinterval = loopinterval*tempo;
  binterval = binterval*tempo;

   delay(loopinterval);
  for(int j=1; j<=3; j++)
  {
    if (j==1)
    {
      for (int i =1; i<=3; i++)
      {
          digitalWrite(pin, HIGH);
          delay(a);
          digitalWrite(pin, LOW);
          delay(b);
      }
    }
    if (j==2)
    {
      delay(binterval);
      for (int i =1; i<=3; i++)
      {
          digitalWrite(pin, HIGH);
          delay(a);
          digitalWrite(pin, LOW);
          delay(b);
      }
    }
    if (j==3)
    {
      delay(binterval);
      for (int i =1; i<=7; i++)
      {
          digitalWrite(pin, HIGH);
          delay(a);
          digitalWrite(pin, LOW);
          delay(b);
           }
    }
       
  }
  
  
     
       
}

