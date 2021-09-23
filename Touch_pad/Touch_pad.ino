#include "Wireless.h"
#include "MotionSensor.h"
#include "Cap.h"
void setup() {
  Wire.begin();
  Serial.begin(9600);
  REG_PORT_DIR0=(1<<20);//sets pin 6 to output
  Cap_Sense();
  connect_wifi();
  //activate if device is not working to check network
  //printWifiStatus();
}
///////////////////////////////////////
//function: loop
//inputs: none
//outputs: none
//gets info to turn on leds and to send to server
///////////////////////////////////////
void loop() {

  MotionSensor(100, 5000);
  //switches register value from cap128 with string
  //that has either L for liquor or P for pop infront
  //of an action ie left, right or pour
  switch (Cap_Read()) {
    case 2:
      Send_Command("Lleft\n");
      break;
    case 1:
      Send_Command("Lpour\n");
      break;
    case 128:
      Send_Command("Lright\n");
      break;
    case 8:
      Send_Command("Pleft\n");
      break;
    case 16:
      Send_Command("Ppour\n");
      break;
    case 32:
      Send_Command("Pright\n");
      break;
    case 4:
      // button available for other functions
      break;
    case 64:
     // button available for other functions
      break;
    default:
      break;
  }
  //clears the alert pin which clears the status register
  Cap_Clear();

}
