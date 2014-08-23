
#define echoPin 11 // Echo Pin
#define trigPin 10 // Trigger Pin
/*
 motor 1 = motor[0] = pin 2
 motot 2 = motor[1] = pin 3
 motor 3 = motor[2] = pin 4
 motor 4 = motor[3] = pin 5
 */
const int motor[] = {2,3,4,5};
int STOP = 0;
int pulse=0;

int maximumRange = 400; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor[0], OUTPUT);
  pinMode(motor[1], OUTPUT);
  pinMode(motor[2], OUTPUT);
  pinMode(motor[3], OUTPUT);
  setESC();
}

void loop()
{
  
  outTrigPin();
  duration = pulseIn(echoPin, HIGH);
  
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  
  if (distance >= maximumRange || distance <= minimumRange) // if out of range
  {
    Serial.println("-1");
    speedESC(motor[0], STOP);
    speedESC(motor[1], STOP);
    speedESC(motor[2], STOP);
    speedESC(motor[3], STOP);
  }
  else 
  {
    /*  Send the distance to the computer using Serial protocol, and
    turn LED OFF to indicate successful reading. */
    Serial.println(distance);
    
    if (distance<50)
    {
      
      speedESC(motor[0], distance/2);
      speedESC(motor[1], distance/2);
      speedESC(motor[2], distance/2);
      speedESC(motor[3], distance/2);
    }
    else
    {
      
      speedESC(motor[0], STOP);
      speedESC(motor[1], STOP);
      speedESC(motor[2], STOP);
      speedESC(motor[3], STOP);
      
    }
  }
  delay(10);
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
void speedESC(int motor, int power)
{
  pulse = motorPulse(motor, power);
  digitalWrite(motor, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(motor, LOW); 
}

void outTrigPin()
{
  /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
}

int motorPulse(int motorNumber, int power)
{
  pulse=0;
  if (motorNumber==motor[0])
  {
    pulse = (2465-1171)/100*power+1171;
  }
  if (motorNumber==motor[1])
  {
    pulse = (2469-1173)/100*power+1173;
  }
  if (motorNumber==motor[2])
  {
    pulse = (2451-1167)/100*power+1166;
  }
  if (motorNumber==motor[3])
  {
    pulse = (2451-1163)/100*power+1163;
  }
  return pulse;
  
}




