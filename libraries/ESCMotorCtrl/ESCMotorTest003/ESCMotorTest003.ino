/*
 motor 1 = motor[0] = pin 2
 motot 2 = motor[1] = pin 3
 motor 3 = motor[2] = pin 4
 motor 4 = motor[3] = pin 5
 */
int motor[] = {2,3,4,5};
int STOP = 1000;
int pulse=0;



void setup()
{
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);
  pinMode(motor[3], OUTPUT);
  setESC();
}

void loop()
{
  if (true) // sensor exist
  {
    speedESC(motor[0], 1200);
    speedESC(motor[1], 1200);
    speedESC(motor[2], 1200);
    speedESC(motor[3], 1200);
  }
  else // no sensor
  {
    speedESC(motor[0], STOP);
    speedESC(motor[1], STOP);
    speedESC(motor[2], STOP);
    speedESC(motor[3], STOP);
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





