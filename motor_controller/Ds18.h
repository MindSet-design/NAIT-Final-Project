#include <OneWire.h>
#define DS18TempSensor 10
OneWire ds(DS18TempSensor);
//////////////////////////////////////////
//function: WaterTemp
//inputs:none
//Outputs:none
//returns the DS18 temp for the client returns
//////////////////////////////////////////
String WaterTemp() {

  byte data[12];
  byte addr[8];
//gets temp sensors 8 byte adress
 if ( !ds.search(addr)) {
 //no more sensors on chain, reset search
 ds.reset_search();
 } 
 //resets and reads temp
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);//starts conversion, parasite power on at the end
  byte present = ds.reset();
  ds.select(addr);
  
  //reads information
  ds.write(0xBE);
  for (int i = 0; i < 9; i++) { //reads 9 bytes
    data[i] = ds.read();
  }
    ds.reset_search();

    byte MSB = data[1];
    byte LSB = data[0];
    float tempRead = ((MSB << 8) | LSB); //using two's compliment
    float TemperatureSum = tempRead / 16;

    String temp=String(TemperatureSum);//change float value to sting for wireless comms
    return temp;

  
}
