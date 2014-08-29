/*
 * phtotoSensor.ino
 *
 * Created: 8/27/2014 11:40:56 PM
 * Author: Hongyun
 */ 

int L = 9;
int out = 8;
int count=0;


void setup()
{
	Serial.begin(9600);
	pinMode(L,INPUT);
	pinMode(out,INPUT);
	  /* add setup code here, setup code runs once when the processor starts */

}

void loop()
{
	//int read1 = digitalRead(L);
	
	int read2 = digitalRead(out);
	//Serial.println(read1);
	Serial.println(read2);
	//Serial.println("====================")	;
	  /* add main program code here, this code starts again each time it ends */

}
