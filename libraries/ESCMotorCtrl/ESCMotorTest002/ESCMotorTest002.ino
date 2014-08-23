/*
 motor 1 = motor[0] = pin 2
 motot 2 = motor[1] = pin 3
 motor 3 = motor[2] = pin 4
 motor 4 = motor[3] = pin 5
 */
int motor[] = {2,3,4,5}; 
int pulse=0;
int STOP = 0;


void setup()
{
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);
  pinMode(motor[3], OUTPUT);
  setESC(motor[3]);
}

void loop()
{
  speedESC(motor[3],1173);
}


/**
 * ESC setup for setup part. Only needs one-time call
 */
void setESC(int motor)
{
  for (pulse = 0; pulse <=500; pulse +=1)
  {
    // HIGH and LOW: alternating signal: generating voltage!
    digitalWrite(motor, HIGH);
    delayMicroseconds(1100);
    digitalWrite(motor, LOW);
    delay(20); //required for setup
  }
}

/**
 * ESC setup for setup part. Only needs one-time call
 * @param motor ESC motor number 1~4
 * @param Pulse Pulse is a kind of speed.
 */
void speedESC(int motor, int pulse)
{
  digitalWrite(motor, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(motor, LOW); 
}





