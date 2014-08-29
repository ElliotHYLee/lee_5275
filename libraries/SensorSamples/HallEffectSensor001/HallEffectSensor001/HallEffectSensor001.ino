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
 double rpm;


/*
 * Function prototypes
 */
void setup(void);
void loop(void);


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
	
	input = Serial.parseInt();
	if (input!=0)
	{
		angle=input;
		Serial.print("Current angle: ");
		Serial.println(angle);
	}	
	
	
	m1.write(angle);
	
	// read the state of the hall effect sensor:
	hallState = digitalRead(hallPin);
    
	if (hallState == LOW) // no magnet
	{
		go = true;
		//Serial.println("LOW")		;
	}
	else // if magnet is near
	{
		if (go)  // to count only once a detection
		{
			// count part
			count++;
			//Serial.print(" count ");
			//Serial.print(count);
			
			// time part
			current = millis();
			elapse = current - past;
			//Serial.print(" time elapse: ");
			//Serial.print(elapse);
			past = current;
			
			// rpm calc part
			rpm = 60.0/(elapse/1000.0);
			//Serial.print(" rpm: ");
			Serial.println(rpm);
			
			
			go=false;
		}	
		
	}
}
