/* 
-----------------------------------------------------------------------------
   Available keywords:
   
   brake
   celerate
   goFor
   goToMark
   laserStartEnabled
   motorSpeed
   reverse
   
   details:
   
   brake(x)        --> 1 argument; motor number 1,2,3 or use 4 for all
   example call:
   brake(2); // fully brake motor 2 
   (note: brake invokes a motor controller standby state that minimizes current draw)
   
   celerate(w,x,y,z) -->4 arguments: motor number 1,2,3, or 4 for all;
   start speed in % (0 to 100);
   end speed in percent (0 to 100);
   time in seconds (1 to 10) 
   example calls:
   celerate(4,20,50,7) will accelerate all motors from 20% to 50% power in 7 seconds
   celerate(2,100,20,1) will deaccelerate motor 2 from 100% to 20% in 1 second 
   (note 1: no goFor or goToMark is required after this call, but if used, it will
   continue with the final motorspeed as set in the celerate command)
   (note 2: celerate actually calls goFor while dropping speed in 1/4 second intervals; 
   goFor has priority in the timing cycle since it MUST finish its sampling task, thus celerate
   is not very accurate in terms of time, i.e. a three second call may be off by several millisecs) 
   
   goFor()        --> 1 argument; milliseconds
   example call:
   goFor(20000); which continues with the last set of commands for 20 seconds 
   
   goToMark()     --> 1 arguments; mark number
   example call:
   goToMark(300); which continues with the last set of commands until mark 300 is detected 
   (note 1: sensor must be connected to digital pin 3 -- has stripe on board outer edge)
   
   laserStartEnabled()  --> 1 argument; logical 0 (not enabled) or 1 (enabled) 
   example call:
   laserStartEnabled(1); allows the user to use a laser pointer to trip a digital pin
   called laserPin using a CdS cell/resistor voltage divider
   (note: laserStartEnanbled(0) is issued by default)  
   
   motorSpeed()   --> 2 arguments; motor number 1,2,3,or use 4 for all;
   speed in percent, 0 to 100
   example call:
   motorSpeed(2,67);  //set motor 2 speed to 67% of full power 
   (note: a goFor or goToXxxx command usually must follow this command)
        
   reverse()      --> no arguments; reverses all motors 
   example call:
   reverse(); //reverses ALL motors
   (note: sorry, there just aren't enough pins for individual motor reverse - reverse the motor
   wires if you need one motor to turn the opposite of the other)
   
  ----------------------------------------------------------------------------- 
  */
  
