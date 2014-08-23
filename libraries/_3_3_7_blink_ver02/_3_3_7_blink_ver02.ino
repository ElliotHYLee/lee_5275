
void setup()
{
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);  
}

void loop()
{
  flashRed(10, 100,100);
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
  int j=0;
    delay(loopinterval);
  while(j==0){
  

  
    for(j=j+1; j<=3; j++)
    {
      if (j==1 || j==2)
      {
        for (int i =1; i<=3; i++)
        {
           flash(pin,a,b);
           
        }
        delay (binterval);
      }
    
      else if (j==3)
      {
        delay(binterval);
        for (int i =1; i<=7; i++)
        {
           flash(pin,a,b);  
          
         }
      }
         
    }
  }
      
       
}

void flash (int pin, int a, int b)
{
         digitalWrite(pin, HIGH);
         delay(a);
         digitalWrite(pin, LOW);
         delay(b);
}
void flashRed (int pin, int a, int b)
{
    for(int k=1;k<=11;k++){
         digitalWrite(pin, HIGH);
         delay(a);
         digitalWrite(pin, LOW);
         delay(b);
       }
         
}

