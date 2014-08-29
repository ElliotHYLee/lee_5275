// counting magnet tickle

#include <Servo.h>

/* 
 * Global Variable
 */
const int hallPin = 8;     // the number of the hall effect sensor pin
// variables will change:
int hallState = 0;          // variable for reading the hall sensor status
int count=0;
boolean go=false;
Servo m1;
int input;
int angle=63;
unsigned long past;
unsigned long current;
unsigned long elapse;
boolean goodToCount=true;
long rpm=0;

/*
 * Function prototypes
 */
void setup(void);
void loop(void);
long RCTime(int);
long countRPM(void);



void setup() {
	Serial.begin(9600);

	// initialize the LED pin as an output:

	// initialize the hall effect sensor pin as an input:
	pinMode(hallPin, INPUT);
	go = false;
	
	m1.attach(2);
	m1.write(50);
}

void loop(){
	  Serial.print("RPM: ");
	  Serial.println(countRPM());
	
	
	input = Serial.parseInt();
	if (input!=0)
	{
		angle=input;
		Serial.print("Current angle: ");
		Serial.println(angle);
	}	
	
	m1.write(angle);

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