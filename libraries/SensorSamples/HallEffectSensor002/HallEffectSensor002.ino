// counting magnet tickle


const int hallPin = 8;     // the number of the hall effect sensor pin
// variables will change:
int hallState = 0;          // variable for reading the hall sensor status
int count=0;
boolean go=false;

/*
 * Function prototypes
 */
void setup(void);
void loop(void);


void setup() {
	Serial.begin(9600);
	// initialize the LED pin as an output:
	pinMode(ledPin, OUTPUT);
	// initialize the hall effect sensor pin as an input:
	pinMode(hallPin, INPUT);
	go = false;
}

void loop(){
	// read the state of the hall effect sensor:
	hallState = digitalRead(hallPin);
    
	if (hallState == LOW) // no magnet
	{
		go = true;		
	}
	else // if magnet is near
	{
		if (go)  // to count only once a detection
		{
			count++;
			Serial.println(count);
			go=false;
		}	
		
	}
}
