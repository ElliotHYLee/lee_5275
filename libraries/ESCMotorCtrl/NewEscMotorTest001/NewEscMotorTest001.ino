#include <Servo.h> 
 
Servo m1;  // create servo object to control a servo 
double k=0;

void printPRM()
{
  k=analogRead(A0);
  Serial.println();
  Serial.print("RPM: ");
  Serial.println(k);
}
 
 
void setup() 
{ 
  pinMode(A0,INPUT);
  Serial.begin(9600);
  m1.attach(2);  // attaches the servo on pin 9 to the servo object 
  m1.write(50);
  delay(5000);
  printPRM();
} 
 
void loop() 
{ 
  Serial.println(0);
  m1.write(0);
  delay(2000);
  
  int angle=63;
  for (int i=0; i< 5; i++)
  {
    m1.write(angle);
    Serial.println(angle);
    angle++;
    printPRM();
    delay(2000);
  }
} 
