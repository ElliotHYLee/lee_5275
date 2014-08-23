/*
AEV005extAm
 m version communicates with Matlab or Recorder ino
 date 01-08-13
 changes:
 - changed pin assignment to match AEV5 SMC
 - switched to tabs
 - added keyword laserStartEnabled()
 date 03-01-12
 changes:
 - added brake 0 current check at start of run 
   (gives base current counts)
 - time is taken out of goToMark function and
   a 120 second time-out timer is hardwired into the function
 - goToPost removed
*/

// libraries --------------------------------------------
// use eeprom to write to internal 1K byte eeprom storage
#include <EEPROM.h>
// use wire to write to external 32K byte external eeprom 
#include <Wire.h>  
// use metro for timing events
#include <Metro.h>
// Metro is a timer used throughout program
// use !metroTimer.check() == 1 for as a goFor loop timer
// use metroTimer.interval() = x to change length in millis
Metro metroTimer = Metro(100,0);
// second instance used for celerate, goToMark
Metro metroAcc = Metro(250,0);
// define constants --------------------------------------------------
// wait is time in seconds prior to program run
// can be overridden with switch on buttonBypass pin that pulls the pin low;
// also can be overridden with a laser hitting a CdS cell on laserBypass pulling the pin low;
const long wait=90000;
// set address of external eeprom (data storage point)
const byte disk1 = 80;
// pin definitions (revised pin definitions for 2nd generation)
// reverse pins
// all motors use the same reverse pins (analog A2 and A3)
const byte fwdHighPin = 14;
const byte fwdLowPin = 15;
// motor 1 control pins 
const byte stbyPin1 = 7;
const byte pwmPin1 = 5;  
// motor 2 control pins
const byte stbyPin2 = 8;
const byte pwmPin2 = 6;
//motor 3 control pins (optional)
const byte stbyPin3 = 4; 
const byte pwmPin3 = 9;
// override the 60 second program start delay
// by using a switch to gnd pin 14 (analog 0)
const byte buttonBypass=12;
// or by using the laser pointer with CdS cell on gnd pin 15 (analog 1)
const byte laserBypass=11;
// Set sensor pins ----------------------------------------------------
// current is sensed on analog 6
// voltage is sensed on analog 7
const byte curSensePin = A2;
const byte batVoltsPin = A3;
// pretty yellow LED
// its not an arduino without an LED!
const byte yellowLedPin = 13;
//interrupt pin(s)
//pin 2 (interrupt 0) used for collecting trackMarks 
const byte interrupt0 = 2;
//pin 3 (interrupt 1) used for collecting trackPosts 
const byte interrupt1 = 3;
// reference voltages for this board
// votage on aref when analogReference is set to EXTERNAL
const float extRef=2.46;
const float defRef=5.0;
const float lowVolts=7.0;
// global variables -------------------------------------------------
// try to minimize these
unsigned long timeStart = 0;
// eepromAddress is byte location in externaleeprom memory
// data is stored in 8 byte shots
// time as an int placed in 2 bytes, timeNow
// current as an int place in two bytes, cVolts
// battery voltage as an int placed in two bytes, bVolts
// wheel rotational counts as an int placed in two bytes, kounts
unsigned int eepromAddress=0;
// track mark counting 
volatile int trackMarks = 0;
//volatile byte trackPosts = 0;
// starting address to store bat life to int eeprom
byte rl=2;
int cVolt1 = 0; //Initiate the no motor(s) running current variable
byte useLaser=0; // this flag is in the laserStartEnabled command, either 0 or 1

// start program execution ----------------------------------------------------

void setup()   
{ 
  // Serial is used for Matlab detection 
  Serial.begin(115200);
  // Wire is used i2c eeprom writes (address is disk1)
  Wire.begin(disk1);
  // set pinmodes and their initial states
  analogReference(EXTERNAL);
  pinMode(fwdHighPin,OUTPUT);
  digitalWrite(fwdHighPin,HIGH);
  pinMode(fwdLowPin,OUTPUT);
  digitalWrite(fwdLowPin,LOW);
  pinMode(stbyPin1,OUTPUT);
  digitalWrite(stbyPin1,HIGH);
  pinMode(stbyPin2,OUTPUT);
  digitalWrite(stbyPin2,HIGH);
  pinMode(stbyPin3,OUTPUT);
  digitalWrite(stbyPin3,HIGH);
  pinMode(yellowLedPin,OUTPUT);
  pinMode(buttonBypass,INPUT_PULLUP);
  // pins 2 and 3 are interrupts 0 and 1 respectively
  // trackMarks interrupt
  pinMode(interrupt1,INPUT);
  attachInterrupt(1,nMarks,RISING);
  // don't allow a run if the LiPo battery voltage
  // is les than lowVolts
  preRunBatteryChk();
  // this delay allows the program data to be read since
  // plugging the arduino into the USB causes the
  // arduino to restart the program thus erasing data
  // if no delay is added
  delayStart();
  // flash pretty yellow LED four times prior to startup 
  ledFlash(4,500,500);
  // turn off petty yellow LED during run
  digitalWrite(yellowLedPin,LOW);
  // clear first 10 bytes of internal eeprom
  for(byte q=0;q<10;q++) EEPROM.write(q,0);
  // do a current usage check with 0 motorSpeed
  //motorSpeed(4,0);
  brake(4);
  cVolt1=getSamples(curSensePin,200,'e');
  EEPROM.write(8,highByte((int)cVolt1));
  EEPROM.write(9,lowByte((int)cVolt1));
  trackMarks = 0; //Initiate mark counter to zero
  //  trackPosts = 0; //Initiate post counter to zero
  timeStart=millis();
  
  // start of run code (see tab)
  // -----------------
  // -----------------
  myCode(); 
  // -----------------
  // -----------------
  // end of run code (see tab)
  brake(4);
  // 1 second end of run reference period 
  // to check base current  
  goFor(1000);
  // run is over
  // shut everything down
  // store number of data bytes collected to eeprom
  // Serial.println(eepromAddress,DEC);
  EEPROM.write(0,highByte((int)eepromAddress));
  EEPROM.write(1,lowByte((int)eepromAddress));
}

void loop()                     
{
  // turn on pretty yellow LED for 5 seconds
  ledFlash(1,5000,1000);
  // check battery life and write to eeprom
  // battery voltage slowly drifts back to a steady state value
  // we have a history over 30 seconds
  int volts=getSamples(batVoltsPin,200,'d');
  byte life=calcLife(volts);
  // rl, the beginning eeprom address is set as a global prior to setup
  // last set to 2, so saving in address 2 - 7
  // 8 and 9 are used for no motors running current 
  if (rl<8)
  { 
    EEPROM.write(rl,life);
    rl++;
  }
  // flash 0 to 10 times for battery life
  // battery life is calculated using lowVolts
  byte l=map(life,0,100,1,10);
  ledFlash(l,400,400);
}












