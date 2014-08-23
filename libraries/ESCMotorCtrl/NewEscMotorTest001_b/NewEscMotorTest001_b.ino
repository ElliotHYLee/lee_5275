/*
 RPMSensor1 = pin 2
 motor 1 = motor[0] = pin 2
 motot 2 = motor[1] = pin 3
 motor 3 = motor[2] = pin 4
 motor 4 = motor[3] = pin 5
 */
int rpmSensor = 0;
int motor[] = {2,3,4,5};
int STOP = 1000;
double pulse=0;
int last = 1300;
double k=0;

void printRPM()
{
  Serial.println();
  k = analogRead(A0);// analogRead(rpmSensor[0]);
  
  Serial.print("RPM: ");
  Serial.println(k);
}


void setup()
{
  
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);
  pinMode(motor[3], OUTPUT);
  setESC();
  printRPM();
}

void loop()
{	
  double low= 1165;
  double high= low+10;
  printRPM();
  for (pulse = low; pulse <=high; pulse +=1)
  {
    digitalWrite(motor[0], HIGH);
    delayMicroseconds(pulse);
    //Serial.println(pulse);
    digitalWrite(motor[0], LOW);
    delayMicroseconds(pulse);//delay(20-(Pulse/1000));
    
  }
  printRPM();
    
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
    delayMicroseconds(1000);
    digitalWrite(motor[0], LOW);
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




