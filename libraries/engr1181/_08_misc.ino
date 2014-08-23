
void preRunBatteryChk()
{
  // check battery Voltage
  // if less than lowVolts STOP NOW !!!
  // never want a single cell to go lower than 3 volts
  // flash 2 sec on .5 sec off
  int bVolts=getSamples(batVoltsPin,200,'d');
  // Serial.println(bVolts,DEC);
  float volts=3.0*defRef*(float)bVolts/1024.0;
  // Serial.println(volts,DEC);
  // catch a very low battery voltage and stop the run!
  // bvolts of 7 volts is (7/(3*5))*1023 = 478 counts (1/3 voltage divider)
  if (volts<lowVolts)
  {
    // loop forever if battery voltage is too low
    // (do not allow the run to take place)
    while(1)
    {
      // set rapid flash if volts to low for run
      ledFlash(1,200,200);
    }
  } 
  // else, battery looks okay -- let's proceed
}

void delayStart()
{
  // Delay prior to run ----------------------------------------------------------
  // This section provides time to pull data from the last run
  // first:
  // set pretty LED high for 90 seconds
  // will flash yellow LED four times prior to start
  digitalWrite(yellowLedPin,HIGH);
  metroTimer.interval(wait);
  // next: 
  // 90 second delay can be overcome with pushbutton or laser
  // or:
  // Matlab or eepromAEVreader sends an 'A' char
  // --
  // first check to see if laserStart is enabled
  if (useLaser==1)
  {
    while (!metroTimer.check()==1 && (digitalRead(buttonBypass)==HIGH) && (digitalRead(laserBypass)==HIGH))
    {
      // check to see if matlab is calling (send an 'A' - wait for return character)
      if (establishContact())
      {
        boolean myflag = sendIt();
        if (myflag)
        {
          ledFlash(10,3000,3000);
          while(1)
          {    
            // after data is collected just sit in an endless loop
            delay(10);
          }
        }        
      }
    } 
  }
  else
  {
    while (!metroTimer.check()==1 && digitalRead(buttonBypass)==HIGH)
    {
      // check to see if matlab is calling (send an 'A' - wait for return character)
      if (establishContact())
      {
        boolean myflag = sendIt();
        if (myflag)
        {
          ledFlash(10,3000,3000);
          while(1)
          {    
            // after data is collected just sit in an endless loop
            delay(10);
          }
        }        
      }
    }
  }
  // Continuing with run!
}

void laserStartEnabled(byte toggle)
{
  if (toggle==1) 
  {
    useLaser=1;
    pinMode(laserBypass,INPUT_PULLUP);
  }
  else
  {
    useLaser=0;
  }
}

void ledFlash(byte numOfTimes, int flashDuration, int timeBetweenFlashes)
{
  digitalWrite(yellowLedPin,LOW);
  metroTimer.reset();
  do
  { 
    metroTimer.interval(flashDuration);
    digitalWrite(yellowLedPin,HIGH);
    do
    {
    } 
    while (!metroTimer.check()==1);
    metroTimer.interval(timeBetweenFlashes);
    digitalWrite(yellowLedPin,LOW);
    do
    {
    } 
    while (!metroTimer.check()==1);
    numOfTimes--;
  } 
  while (numOfTimes>0);
}

byte calcLife(int rawVolts)
{
  float volts=3.0*defRef*(float)rawVolts/1024.0;
  byte life=map(volts,6.4,8.2,0,100); 
  return life; 
}

// keep this interrupt call as simple as possible
void nMarks()
{
  trackMarks=trackMarks+1;
}

int timeNow()
{
  int currentTime=(int)((millis()-timeStart)/10);
  return currentTime;
}

int getSamples(byte pin, int numOfSamples, char type)
{
  if (type=='e') analogReference(EXTERNAL); 
  else analogReference(DEFAULT);
  long sampleAvg=0; 
  // get numOfSamples samples
  for (byte j=0;j<(numOfSamples+2);j++)
  {
    // oddly, the first two values are considerably off 
    if (j<2) analogRead(pin);
    else sampleAvg=sampleAvg+analogRead(pin);
  }
  int valueOut=(int)(sampleAvg/numOfSamples);
  return valueOut;       
}

void eepromWrite(int theDeviceAddress, unsigned int theMemoryAddress, int theByteCount, byte* theByteArray) 
{
  for (int theByteIndex = 0; theByteIndex < theByteCount; theByteIndex++) 
  {
    Wire.beginTransmission(theDeviceAddress);
    Wire.write(highByte(theMemoryAddress + theByteIndex));
    Wire.write(lowByte(theMemoryAddress + theByteIndex));
    Wire.write(theByteArray[theByteIndex]);
    Wire.endTransmission();
    delay(4);
  }
}

void eepromWriteByte(int theDeviceAddress, unsigned int theMemoryAddress, byte theByte) 
{
  byte theByteArray[sizeof(byte)] = {
    (byte)(theByte >> 0)                  };
  eepromWrite(theDeviceAddress, theMemoryAddress, sizeof(byte), theByteArray);
  eepromAddress++;
}

void eepromWriteInt(int theDeviceAddress, unsigned int theMemoryAddress, int theInt) 
{
  byte theByteArray[sizeof(int)] = {
    (byte)(theInt >> 8), (byte)(theInt >> 0)                  };
  eepromWrite(theDeviceAddress, theMemoryAddress, sizeof(int), theByteArray);
  eepromAddress=eepromAddress+2;
}

// ============== communicate with matlab ===============

boolean establishContact() 
{    
  boolean flag=false;
  unsigned long timer1=millis();
  while (millis()-timer1 < 500)  
  {
    if (Serial.available() <= 0)
    {
      //Serial.write('A');   // send a capital A
      //Serial.println('A');
      Serial.println(1, DEC); // Try sending a number
      delay(50);
    }
    else
    {
      flag=true;
      break;
    }
  }
  return flag;
}

boolean sendIt()
{
  boolean flagSiT = 0; 
  // Send an opening sequence
  Serial.println(1,DEC);
  Serial.println(2,DEC);
  Serial.println(3,DEC);
  // eeprom external storage bytes used
  byte a = EEPROM.read(0);
  byte b = EEPROM.read(1);
  int number=word(a,b);
  Serial.println(number,DEC);
  // send seven after run battery life calcs
  // some may be zero - depends on how long they left unit powered on after run
  for (b=2;b<8;b++)
  {
    a = EEPROM.read(b);
    Serial.println(a,DEC);
  }
  // send the motor zero current state
  a = EEPROM.read(8);
  b = EEPROM.read(9);
  int number1 = word(a,b);
  Serial.println(number1,DEC);

  // send data stored as bytes in external eeprom
  // time, current, voltage, wheel counts, post counts
  //  for (int j=0;j<number;j=j+9) 
  for (int j=0;j<number;j=j+8)    
  {   
    // time
    int A = eepromReadInt(disk1,j);
    Serial.println(A,DEC);
    // current
    A = eepromReadInt(disk1,j+2);
    Serial.println(A,DEC);
    // voltage
    A = eepromReadInt(disk1,j+4);
    Serial.println(A,DEC);
    // wheel counts
    A = eepromReadInt(disk1,j+6);
    Serial.println(A,DEC);
    // posts
    // A = eepromReadByte(disk1,j+8);
    // Serial.println(A,DEC);
    // rpm
  } 
  // Send a closing numerical sequence 
  Serial.println(4,DEC);
  Serial.println(5,DEC);
  Serial.println(7,DEC);
  flagSiT=1;
  return flagSiT;
}

void eepromRead(int theDeviceAddress, unsigned int theMemoryAddress, int theByteCount, byte* theByteArray) 
{
  for (int theByteIndex = 0; theByteIndex < theByteCount; theByteIndex++) 
  {
    Wire.beginTransmission(theDeviceAddress);
    Wire.write(highByte(theMemoryAddress + theByteIndex));
    Wire.write(lowByte(theMemoryAddress + theByteIndex));
    Wire.endTransmission();
    delay(3);
    Wire.requestFrom(theDeviceAddress, sizeof(byte));
    theByteArray[theByteIndex] = Wire.read();
  }
}

byte eepromReadByte(int theDeviceAddress, unsigned int theMemoryAddress) 
{
  byte theByteArray[sizeof(byte)];
  eepromRead(theDeviceAddress, theMemoryAddress, sizeof(byte), theByteArray);
  return (byte)(((theByteArray[0] << 0)));
}

int eepromReadInt(int theDeviceAddress, unsigned int theMemoryAddress) 
{
  byte theByteArray[sizeof(int)];
  eepromRead(theDeviceAddress, theMemoryAddress, sizeof(int), theByteArray);
  return (int)(((theByteArray[0] << 8)) | (int)((theByteArray[1] << 0)));
}




