void goFor(unsigned long numOfMillis)
{
  // the 32K eeprom can record 4096 data sets (4 intergers in a set, 
  // 2 bytes per integer or 32768/8)
  // therefore for a maximum length run of 120 seconds then
  // only 34 sets per second are allowed or approximately 1 every 30 ms
  // this current code loop executes in 10 to 11 ms
  // added a delay of 20 ms to keep data logging manageable 
  metroTimer.reset();
  metroTimer.interval(numOfMillis);
  do
  { 
    // get time
    int theTime=timeNow();
    // if run exceeds 120 seconds 12000 in hundredths - timeNow returns hundreds) stop recording
    // if eeprom is full stop recording (external 32768 bytes)
    if ((theTime <= 12000) && (eepromAddress <= 32767))
    {
      eepromWriteInt(disk1,eepromAddress,theTime);
      int cVolts=getSamples(curSensePin,200,'e');
      cVolts = cVolts - cVolt1;
      eepromWriteInt(disk1,eepromAddress,cVolts); 
      int bVolts=getSamples(batVoltsPin,200,'d');
      eepromWriteInt(disk1,eepromAddress,bVolts);
      eepromWriteInt(disk1,eepromAddress,trackMarks);
      // eepromWriteByte(disk1,eepromAddress,trackPosts);
    }
    // check time and leave subroutine if it is greater than numOfmillis
  } 
  while (!metroTimer.check()==1); 
}
