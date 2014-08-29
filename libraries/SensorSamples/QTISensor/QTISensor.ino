int k;
int noiseCount;
void setup()
{
Serial.begin(9600);
}

void loop()
{
  Serial.println(RCTime(8)); // Connects to pin 14, displays results
  
}

long RCTime(int sensorIn)
{
  long duration = 0;
  pinMode(sensorIn, OUTPUT); // Sets pin as OUTPUT
  digitalWrite(sensorIn, HIGH); // Pin HIGH
  //delay(1); // Waits for 1 millisecond
  pinMode(sensorIn, INPUT); // Sets pin as INPUT
  digitalWrite(sensorIn, LOW); // Pin LOW
  
  while(digitalRead(sensorIn)) // Waits for the pin to go LOW
  {
    k=digitalRead(sensorIn);  
    delayMicroseconds(1000);

    if (k==1)
    {
      Serial.println(k);
      noiseCount++;  
    }
  
    
    duration++;
  }
  return noiseCount; // Returns the duration of the pulse
}
