/*
 * MasterVersion001.ino
 *
 * Created: 10/1/2014 7:22:04 PM
 * Author: Hongyun
 */ 
int motor1 = 3;
int incoming=0;

void setup()
{
	Serial.begin(9600);
	pinMode(motor1,OUTPUT);
	incoming = 0;
	
}

void loop()
{
	if (Serial.available()>0)
	{
		incoming = Serial.parseInt();
		Serial.write("i have got: ");
		Serial.println(incoming);
		
	}
	analogWrite(motor1, incoming);
	Serial.print(incoming);
	Serial.println(" has been sent");
}
