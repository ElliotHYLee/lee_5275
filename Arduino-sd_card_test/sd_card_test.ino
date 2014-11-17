

//*****Arduino Connection Type*******       *Pin*          
//Air Speed Sensor                            A0          //  A1  
//Red Writing LED  anode                      D2             
//Green Power LED anode                       D3             
//Button Input                                D4
// TMP 35                                     A1          // A0
//
//SD CARD:
//CS                                         D10
//DI                                         D11
//DO                                         D12
//CLK                                        D13
//CARD POWER                                 D9
//


//Program Start 

#include <SD.h>
#include <SFE_BMP180.h>
#include <Wire.h>

//Variables:
// bmp180

SFE_BMP180 pressure;
double baseline; // baseline pressure


int time_delay = 250;
int mode = 4; 
int LEDP = 8;  //3
int LED  = 3;  //2
int P    = A1; //0
int TMP  = A0; //1

//SD Card
int CS_pin = 10;
int SD_Power= 9;


float V[5];
float v=0;
float average;
float cal2;
float TMP_val;
float TMP_volt;
float T_C;
float T_F;

int k=0;
float ADJUST;
float velocity;

float cal=0.11;

//Flags
int calibrate=1;
int start=0;
int SD_flag=1;
int SD_flag2=1;


void setup(){
  //Serial Communication
  // bmp 180
   Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }

  // Get the baseline pressure:
  
  baseline = getPressure();
  
  Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" mb");  


  Serial.begin(9600);
  Serial.println("Program Start");
  Serial.println("Initializing Card...");
  delay (1000);
  
   //Set Pins
  pinMode(mode, INPUT);
  pinMode(LEDP, OUTPUT);  
  pinMode(LED, OUTPUT);  
  pinMode(LEDP, OUTPUT);  
  pinMode(CS_pin, OUTPUT);
  pinMode(SD_Power, OUTPUT);
  
  
  
   //Check SD Card Availability******************************************
  digitalWrite(SD_Power, HIGH);
  digitalWrite(LEDP, HIGH);
  
  if (!SD.begin(CS_pin))
  { Serial.println("**********");
  Serial.println("Card Failed, Try Again.");
  Serial.println("**********");
  digitalWrite(LEDP, LOW);
  return;
  }
  
  Serial.println("Card Ready!");
  Serial.println();

}


////////////////////////////LOOP///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void loop(){
   // STEP 1 SD Card file writing (SD_flag1)
   if (SD.exists("log.txt")==1 && SD_flag ==1 ) {
     Serial.println("File already exisits, erasing...");
      SD.remove("log.txt");
      SD_flag = 0;
   }
   else{
   SD_flag = 0;
   }
  File logfile = SD.open("log.txt", FILE_WRITE);  // if file does not exist, the file will be created
  //The second commna FILE_WRITE allows for writing to the txt file, normally only read data.
  digitalWrite(LED, HIGH);
  // ******************************************************************
   //STEP 2 WRITE VALUES TO CARD (SD_flag2)
  if (logfile && SD_flag2 == 1){  //if able to connect to the log file, then write the data
    logfile.println("Flight Data");
    SD_flag2=0;
  }
  //*************************************************************************
  
  double a,P, SensorValue;
  // Get a new pressure reading:
  P = getPressure();
  // Show the relative altitude difference between
  // the new reading and the baseline reading:
  a = pressure.altitude(P,baseline);
  
  Serial.print("sensor reading: ");
  Serial.println(a);

//PRINT DATA TO SD CARD
 if (logfile){
   Serial.println("saving value..");
   logfile.print(a);
   logfile.print("             ");
   logfile.close();
   digitalWrite(LED, LOW);
 }
 else 
 {//    Serial.println("I couldn't access the file. I don't know what happened. I think I dropped it.");  
   Serial.println("I couldn't access the file. I don't know what happened. I think I dropped it.");  
 }
 
 //*************************************************
  delay (time_delay);
}


double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}








