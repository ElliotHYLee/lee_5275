#include <Thread.h>
/*
 RPMSensor1 = pin 2
 motor 1 = motor[0] = pin 2
 motot 2 = motor[1] = pin 3
 motor 3 = motor[2] = pin 4
 motor 4 = motor[3] = pin 5
 */
int rpmSensor = A0;
int motor[] = {2,3,4,5};
int STOP = 1000;
int pulse=0;
int last = 1185;
double k=0;

Thread myThread = Thread();

void setup()
{
  
  Serial.begin(9600);
  pinMode(rpmSensor+14, INPUT);
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);
  pinMode(motor[3], OUTPUT);
  setESC();
  myThread.onRun(printRPM);
  myThread.setInterval(10);
  
}

void loop()
{
  if(myThread.shouldRun())
  {
    //myThread.run();
  }
		
  //printRPM();
  for (pulse = 1150; pulse <=last; pulse +=1)
  {
    digitalWrite(motor[0], HIGH);
    delayMicroseconds(pulse);
    digitalWrite(motor[0], LOW);
    delay(20);//delay(20-(Pulse/1000));
    //printRPM();
  }
  
  for (pulse = last; pulse >=1150; pulse-=1)
  {
    digitalWrite(motor[0], HIGH);
    delayMicroseconds(pulse);
    digitalWrite(motor[0], LOW);
    delay(20);//delay(20-(Pulse/1000));
  }
  
}


/**
 * ESC setup for setup part. Only needs one-time call
 */
void setESC()
{

  for (pulse = 0; pulse <=75; pulse +=1)
  {
    // HIGH and LOW: alternating signal: generating voltage!
    digitalWrite(motor[0], HIGH);
    digitalWrite(motor[1], HIGH);
    digitalWrite(motor[2], HIGH);
    digitalWrite(motor[3], HIGH);
    delayMicroseconds(1000);
    digitalWrite(motor[0], LOW);
    digitalWrite(motor[1], LOW);
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], LOW);
    delay(20); //required for setup
  }
  //speedESC(motor,STOP);
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


