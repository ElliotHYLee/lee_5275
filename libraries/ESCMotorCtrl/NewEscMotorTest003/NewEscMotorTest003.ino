/*
 RPMSensor1 = pin 2
 motor 1 = motor[0] = pin 2
 motot 2 = motor[1] = pin 3
 motor 3 = motor[2] = pin 4
 motor 4 = motor[3] = pin 5
 */
int rpmSensor = A0;
int motor[] = {2,3,4,5};
double k=0;

void setup()
{
  Serial.begin(9600);
  pinMode(rpmSensor+14, INPUT);
 
}

void loop()
{
  analogWrite(motor[0], 150);
}



/**
 * ESC setup for setup part.
 * @param motor ESC motor number 1~4
 * @param Pulse Pulse is a kind of speed.
 */
void speedESC(int motor, int pulse)
{
  digitalWrite(motor, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(motor, LOW); 
}


void printRPM()
{
  k = analogRead(rpmSensor);// analogRead(rpmSensor[0]);
  Serial.println(k);
  Serial.print("RPM: ");
}


