#include "Wire.h"
#include "ADXL345.h"

const float alpha = 0.5;

double fXg = 0;
double fYg = 0;
double fZg = 0;

ADXL345 acc;

void setup()
{
	acc.begin();
	Serial.begin(9600);
	acc.setRange(acc.RANGE_2G);
	delay(100);
}

void loop()
{
	double pitch, roll, Xg, Yg, Zg;
	
	acc.read(&Xg, &Yg, &Zg);
	acc.setZeroG(Xg, Yg, Zg);

	//Low Pass Filter to smooth out data
	fXg = Xg * alpha + (fXg * (1.0 - alpha));
	fYg = Yg * alpha + (fYg * (1.0 - alpha));
	fZg = Zg * alpha + (fZg * (1.0 - alpha));

	//Roll and Pitch Equations
	roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
	pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;

	//Serial.print(pitch);
	//Serial.print("   ");
	//Serial.println(roll);
	
	Serial.print("x:");
	Serial.print(fXg); 
	Serial.print(",  y:");
	Serial.print(fYg); 
	Serial.print(",  z:");
	Serial.println(fZg);

	delay(50);
}
