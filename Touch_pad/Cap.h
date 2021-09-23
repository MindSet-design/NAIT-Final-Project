#include <Wire.h>
#define cap 0x28
///////////////////////////////////////
//function: Cap_Read
//inputs:none
//outputs byte Register_Value, 0x03 register value
//0x03 register is the pin status register
//checks the pin status of CAP1298 
///////////////////////////////////////
byte Cap_Read() {
  byte Register_Value = 0;
  //begins communication with cap128 and reads register 0x03
  //and prints the register value
  Wire.beginTransmission(cap);
  Wire.write(0x03);       // input status register 
  Wire.endTransmission();
  Wire.requestFrom(cap, 1);
  Register_Value = Wire.read();
  return  Register_Value;
}
///////////////////////////////////////
//function: Cap_Clear
//inputs: none
//outputs:none
//clears the interupt alert which resets the status register
///////////////////////////////////////
void Cap_Clear() {
  //begins communication with cap128 and writes register 0x00 to 0
  Wire.beginTransmission(cap);
  Wire.write(0x00);//genral status register
  Wire.write(0);
  Wire.endTransmission();
}
///////////////////////////////////////
//function: Cap_Sense
//inputs: none
//outputs:none
//sets the sensitivity register to 4x insted of default 32x
///////////////////////////////////////
void Cap_Sense(){
  Wire.beginTransmission(cap);
  Wire.write(0x1f);//sensitivity register
  Wire.write(0x5f);//4x value
  Wire.endTransmission();
  
}
