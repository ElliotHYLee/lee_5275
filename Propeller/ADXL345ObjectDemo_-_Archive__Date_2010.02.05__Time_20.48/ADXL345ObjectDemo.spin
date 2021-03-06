{{
ADXL345Object

Author: Andrew Colwell (c) February 2010
Version: 1.0

Please see description in the ADXL345Object for more details.

First, the code tests to see if the ADXL345 is present.

Second, the code runs a Self test.
The Self Test Data often fails, yet the chip seems to work fine. Its
been through some tumbles, and I don't have a second to further test.

Finally, the code reads the acceleration recorded on each axis in
decimal representing +/-16g in 10bits.

+/-16g means a range of 32g
32g / 2^10 bits = 0.03125g per bit

multiplying the value displayed on the Serial Terminal by 0.03125
will give the current g's the axis is experiencing. If the chip
is level, the x and y axes will be 0, and the z axis will be 32
representing 1g (32 * 0.03125 = 1). This is good as the z-axis
measures the vertical axis and if sitting still will experience
1g of acceleration due to gravity!

The arrows on the break out board indicate positive accelerations.

Changing the orientation of the breakout board by 90° will result
in another axis reading +/-32 and the z axis falling to 0.

At an orientation of 45° will result in 23 for two axis. Force is
a vector, and forms a right angle triange with the two axis as the
components. Pythagorean theorem can be used to solve for the hypotenuse.
32² = z² + x²    at 45° the z and x components will be equal
1024 = z²+ z²
1024 = 2*z²
512 = z²
z = 22.6         and the chip experiences 23 in digital
         
}}
CON
   _clkmode      = xtal1 + pll16x
   _xinfreq      = 5_000_000

  ' Register Map addresses (partial list)
   _DeviceID   = $00   'Device ID (0xE5)      r   Always %1110_0101
   _xOffset    = $1E   'User defined offset   r/w Each bit has a factor of 
   _yOffset    = $1F   'User defined offset   r/w 15.6mg/LSB per offset
   _zOffset    = $20   'User defined offset   r/w
   _FreeFallTh = $28   'freefall threshold    r/w 62.5mg/LSB Recommended between 0x05 and 0x09
   _FreeFall   = $29   'freefall time         r/w
   _Rate       = $2C   'Transfer Rate         r/w See datasheet table default 100Hz output
   _PwrCtrl    = $2D   'Measurement Controls  r/w
   _IntEnable  = $2E   'Interrupt control     r/w (%0000_0100 for freefall)
   _IntMap     = $2F   'Interrupt mapping     r/w (%0000_0000 for Int1 output)
   _IntSource  = $30   'Source of interrupts  r   (%0000_0100 freefall triggered int1)
   _DataFormat = $31   'Data format           r/w (%0000_0011 +/-16g with sign extension, 10 bit mode)
                       '                          (%1000_0000 Self-Test)
   _X0         = $32   '                      r    LSB
   _X1         = $33   '                      r    MSB
   _Y0         = $34   '                      r    LSB
   _Y1         = $35   '                      r    MSB
   _Z0         = $36   '                      r    LSB
   _Z1         = $37   '                      r    MSB
   _FifoCtrl   = $38   'FIFO control          r/w
   _FifoStat   = $39   'FIFO status           r
{{
   ACK      = 0        ' I2C Acknowledge
   NAK      = 1        ' I2C No Acknowledge
   Xmit     = 0        ' I2C Direction Transmit
   Recv     = 1        ' I2C Direction Receive
   BootPin  = 28       ' I2C Boot EEPROM SCL Pin
   EEPROM   = $A0      ' I2C EEPROM Device Address
   SCL      = 15       ' I2C SCL Pin
   SDA      = 14       ' I2C SDA Pin
}}
OBJ
  Debug:   "FullDuplexSerialPlus"            ' Use with Parallax Serial Terminal to
  fString: "FloatString"                     ' Use floating math to String routines
  adxl:    "ADXL345Object"                   ' Use the ADXL345 Object

VAR
  long xaxis, yaxis, zaxis, temp, axis, axis0, axis1
  long STxaxis, STyaxis, STzaxis, nSTxaxis, nSTyaxis, nSTzaxis     'self-test variables

PUB Main

  Debug.Start(31, 30, 0, 115200)

  waitcnt(clkfreq + cnt)

  adxl.InitI2C
  
  if adxl.ReadDeviceID <> -1
     debug.str(string(16, "ADXL345 Chip Not Present...Aborting!"))
     abort
  debug.str(string(16, "ADXL345 Detected... First Hurdle Passed!"))

  waitcnt(clkfreq + cnt)

'' Self-test section as prescribed in the ADXL345 DataSheet

  debug.str(string(13, "Performing Self-Test +/- 16g, Full resolution, 100Hz..."))
  adxl.WrLoc(_Rate, %0000_1011)               'Set rate to > 100Hz recommended for SelfTest (%0000_1011 = 200Hz)
  adxl.WriteDataFormat(%0000_1011)                    'Set SelfTest Disabled: +/-16g, full resolution

  temp := 0
  STxaxis := 0
  STyaxis := 0
  STzaxis := 0
  
  repeat temp from 1 to 10
  
     xaxis := adxl.Read2byte(_X0)
     STxaxis := STxaxis + xaxis
     yaxis := adxl.Read2byte(_Y0)
     STyaxis := STyaxis + yaxis
     zaxis := adxl.Read2byte(_Z0)
     STzaxis := STzaxis + zaxis
  
  nSTxaxis := STxaxis / 10
  nSTyaxis := STyaxis / 10
  nSTzaxis := STzaxis / 10


  adxl.WriteDataFormat(%1000_1011)                    'Set SelfTest: +/-16g, full resolution
  temp := 0
  STxaxis := 0
  STyaxis := 0
  STzaxis := 0

  repeat temp from 1 to 4
                                                 
     xaxis := adxl.Read2byte(_X0)                      'needs to wait 4 samples to settle down after formatting
     yaxis := adxl.Read2byte(_Y0)
     zaxis := adxl.Read2byte(_Z0)
                               
  repeat temp from 1 to 10
  
     xaxis := adxl.Read2byte(_X0)
     STxaxis := STxaxis + xaxis
     yaxis := adxl.Read2byte(_Y0)
     STyaxis := STyaxis + yaxis
     zaxis := adxl.Read2byte(_Z0)
     STzaxis := STzaxis + zaxis
  
  STxaxis := STxaxis / 10
  STyaxis := STyaxis / 10
  STzaxis := STzaxis / 10

  STxaxis := STxaxis - nSTxaxis
  STyaxis := STyaxis - nSTyaxis
  STzaxis := STzaxis - nSTzaxis 

  temp :=0
     
  debug.str(string(13, "Self Test Data"))                  ' Regardless of whether pass or fail
  debug.str(string(13, "  X-Axis(between 50~540): "))      ' this section simply reports the
  debug.dec(STxaxis)                                       ' values as per datasheet
  if (STxaxis < 540) and (STxaxis > 50)
      debug.str(string("  Good!"))
      temp++
  else
       debug.str(string("  Failed"))
       temp~
   
  debug.str(string(13, "  Y-Axis(between -540~-50): "))
  debug.dec(STyaxis)
  if STyaxis > -540 and STyaxis < -50
       debug.str(string("  Good!"))
       temp++         
  else
       debug.str(string("  Failed"))
       temp~
         
  debug.str(string(13, "  Z-Axis(between 75~875): "))
  debug.dec(STzaxis)
  if (STzaxis < 875) and (STzaxis > 75) 
      debug.str(string("  Good!"))
      temp++
  else
       debug.str(string("  Failed"))
       temp~

           
  adxl.WriteDataFormat(%0000_0000)                    'Set data format to default
  
  '' Prepare to start reading acceleration measurements.
  
  debug.str(string(13, "Attempting to create +/-16g,  10bit data..."))
  adxl.WriteDataFormat(%0000_0011)                    '%0000_0000 is 2g, %0000_0001 is 4g, %0000_0010 is 8g, %0000_0011 is 16g
                                                 '%0000_1000 where 1 is 13 bit data (4mg/LSB) and 0 is 10 bit data
  temp := adxl.ReadDataFormat
  case temp & %0000_0011
     0: debug.str(string(13, "2g format initiated!"))
     1: debug.str(string(13, "4g format initiated!"))
     2: debug.str(string(13, "8g format initiated!"))
     3: debug.str(string(13, "16g format initiated!"))
     OTHER: debug.str(string(13, "Unknown format initiated...Aborting!"))
            abort
  
  debug.str(string(13, "Second Hurdle Passed!"))

  waitcnt(clkfreq + cnt)
  
  debug.str(string(13, "Attempting to read axis accelerations...")) 
  adxl.WrLoc(_Rate, %0000_1010)               'Set data rate at 100Hz
  adxl.WrLoc(_PwrCtrl, %0000_1000)            'Set chip to take measurements

  waitcnt(clkfreq + cnt)
  'debug.str(string(16))

  repeat 
    xaxis := adxl.Read2byte(_X0)
    yaxis := adxl.Read2byte(_Y0)
    zaxis := adxl.Read2byte(_Z0)

    'debug.str(string(13, "Data", 13)) 

    debug.str(string(Debug#CRSRXY, 1, 12))
    debug.str(string("X-Axis       Y-Axis         Z-Axis", 13, "                                              "))
    debug.str(string(Debug#CRSRXY, 1, 13))
    debug.dec(xaxis)
    debug.str(string(Debug#CRSRXY, 16, 13))    
    debug.dec(yaxis)
    debug.str(string(Debug#CRSRXY, 32, 13))
    debug.dec(zaxis)
 
    waitcnt(clkfreq / 24 + cnt)
    debug.str(string(13))
    'waitcnt(clkfreq / 5 + cnt)

  adxl.WrLoc(_PwrCtrl, %0000_0000)            'Set chip to stop taking measurements


{{
                            TERMS OF USE: MIT License                                                           

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
}}  