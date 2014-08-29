boolean goodToCount=true;
long rpm=0;

void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("RPM: ");
  Serial.println(countRPM());
  
}

long RCTime(int sensor)
{
   long duration = 0;
  
   pinMode(sensor, OUTPUT);     // Make pin OUTPUT
   digitalWrite(sensor, HIGH);  // Pin HIGH (discharge capacitor)
  
   pinMode(sensor, INPUT);      // Make pin INPUT
   digitalWrite(sensor, LOW);   // Turn off internal pullups
   
   while(digitalRead(sensor))// Wait for pin to go LOW
   {  
      duration++;
   }
   //Serial.println(duration);
   return duration;
}

long countRPM()
{
  
  if (RCTime(8)==3 && goodToCount==true)
  {
    rpm++;
    goodToCount=false;
    Serial.println("=============Passed");
  }
  else if(RCTime(8)!=3 && goodToCount==false)
  {
      goodToCount=true;
  }
   else
   {
      //Serial.println("Sth wrong"); 
   }
   
    return rpm/2;
}
