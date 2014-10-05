int sender = 12;      // LED connected to digital pin 9
int reader = A3;   // potentiometer connected to analog pin 3
float val = 0;         // variable to store the read value
int go = 10;
int oldIn;
int newIn;


void setup(){
   Serial.begin(9600);
   pinMode(sender, OUTPUT);   // sets the pin as output
   pinMode(reader, INPUT);
}

void loop(){
 
    if (Serial.available() >0){
      newIn = Serial.parseInt();
    }
    if(newIn!=0){
      if (oldIn!=newIn){
        oldIn=newIn;    
      }
    }
    go = oldIn;
    
    val = analogRead(reader);   // read the input pin
    val=val/1024*5;
    analogWrite(sender, go);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    Serial.print("sent: ");
    Serial.print( go);
    Serial.print(" Received: ");
    Serial.println(val);
}
