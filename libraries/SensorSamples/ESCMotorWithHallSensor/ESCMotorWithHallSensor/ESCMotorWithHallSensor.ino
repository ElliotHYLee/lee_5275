// counting magnet tickle

#include <Servo.h>

/* 
 * Global Variable
 */
const int hallPin = 8;     // the number of the hall effect sensor pin
const int motor[] = {2};

// variables that will change:
int hallState = 0;          // variable for reading the hall sensor status
int count=0;
boolean go=false;
int input;
int motorOut=1190;
unsigned int pastSpeed;
unsigned long past;
unsigned long current;
unsigned long elapse;
double rpm;
int pulse;


/*
 * Function prototypes
 */
void setup(void);
void loop(void);
void setESC(void);
void speedESC(int, int);
void hallRead(void);

void setup() {
	Serial.begin(9600);
	// initialize the LED pin as an output:

	// initialize the hall effect sensor pin as an input:
	pinMode(hallPin, INPUT);
	pinMode(motor[0], OUTPUT);
	go = false;
	
	//motor setting
	setESC();
	

}

void loop(){
	
	if (Serial.available() > 0)
	{
		input = Serial.parseInt();	
		motorOut = input;
		Serial.print("New motorOut: ");
		Serial.println(motorOut);
	}
			
	speedESC(motor[0], motorOut);
	hallRead();
	
	
}

void setESC()
{

	for (pulse = 0; pulse <=75; pulse +=1)
	{
		// HIGH and LOW: alternating signal: generating voltage!
		digitalWrite(motor[0], HIGH);

		delayMicroseconds(1000);
		digitalWrite(motor[0], LOW);

		delay(20); //required for setup
	}
	//speedESC(motor,STOP);
}

void speedESC(int motor, int pulse)
{
	//Serial.println("Im in spped control");
	digitalWrite(motor, HIGH);
	delayMicroseconds(pulse);
	digitalWrite(motor, LOW);
	//delay(20);
}

void hallRead()
{
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
			rpm = 60.0/(elapse/1000.0)/4.0;
			//Serial.print(" rpm: ");
			Serial.println(rpm);
			
			
			go=false;
		}
		
	}
	
	
}
