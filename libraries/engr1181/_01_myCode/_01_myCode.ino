void myCode()
{
// insert your run code keywords between the dashed lines
// -----------------------------------------------------------

 reverse();
 motorSpeed(4,30); // go forward
 goToMark(40); // for a specific distance (revolutions)
 
//-idle------
  brake(4);
  goFor(5000); // no motor movement for 5 seconds
//-------------

  // go forward again
 motorSpeed(4,30); //motor speed
 goToMark(12); //for a specific distance

  brake(4);
  goFor(5000); 
 
 reverse();
 motorSpeed(4,30); //motor speed
 goToMark(14);

    
// -------------------------------------------------------------
// notes:
// 1. there is always a 1 second 'end of run' reference period that
// is used to check the no motor current level (refCurrentCounts).
// 2. the voltage counts reference to 5 volts, but are 1/3 total battery
// volts (using a simple 10K/10K/10K ohm voltage divider), so:
// battery volts = 3*(5 volts)*(counts/1024)
// 3. current uses a 2.46 volt reference and the sensor voltage output rises
// 0.185 volts per amp, so (refCurrentCounts is automatically subtracted):
// amps=(2.46*counts/1024)/0.185
} //end of void myCode()
