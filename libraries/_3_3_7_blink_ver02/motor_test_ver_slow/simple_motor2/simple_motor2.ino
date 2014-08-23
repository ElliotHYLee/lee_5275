const int 
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9;

void setup() {
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  
}

void loop(){
    digitalWrite(BRAKE_A, LOW); 
    digitalWrite(DIR_A, HIGH);
    analogWrite(PWM_A, 255); 
}
