/*
	Randy Test software for UNO
*/

#include <Servo.h>
#define ANALOG_PIN A0
#define INTERRUPT_PIN 8   // digital pin 2
int count;
int interruptCount=0;
boolean interruptCalled = false;  // boolean value
unsigned long lastTime = 0;
unsigned long currTime = 0;
unsigned long timeDiff = 0;
float rpm = 0;
Servo m1;

void setup()
{
	pinMode(2, OUTPUT);
	
	m1.attach(2);
	m1.write(50);	
  int i;
  // setup ADC pin
  pinMode(ANALOG_PIN, INPUT);
  
  // initialise pull up resistors on all digital pins
  for(i=0; i<10; i++ ) {
    //digitalWrite(i, HIGH);
    digitalWrite(i, LOW);
  }
  
  // setup interrupt pin
  pinMode(INTERRUPT_PIN, INPUT);
  attachInterrupt(INTERRUPT_PIN, interruptFired, CHANGE);

  Serial.begin(9600);
  Serial.println("UnoTest.pde by Randy Mackay");
}

void interruptFired()
{
    interruptCount++;
    interruptCalled = true;
}

int readAnalog()
{
    int val;
    val = analogRead(ANALOG_PIN);
    return val;
}

void loop()
{
	m1.write(61);
    int i;
    delay(100);
    count++;
   // Serial.print(count);
    //Serial.print("\t");
    /*
    Serial.print(readAnalog());
    for(i=0; i<10; i++) {
      Serial.print("\t");
      Serial.print(i);
      Serial.print(":");
      Serial.print(digitalRead(i));
    }
    Serial.println();
    */
    if( interruptCalled ) {
        currTime = micros();
        timeDiff = currTime - lastTime;
        rpm = (float)interruptCount * 1000000.0 / (float)timeDiff;
        interruptCalled = false;
        Serial.print("ping! ");
        Serial.print(interruptCount);
       Serial.print("\t");
        Serial.print(timeDiff);
        Serial.print("\t");
        Serial.print(rpm);
        Serial.println();
        interruptCount = 0;
        lastTime = currTime;  // store current time for next iteration
    }
    Serial.println();
}