//libraries
#include "MakeDrink.h"
#include "Ds18.h"
#include "Wireless.h"
//global character for drink side select
char side = 'L';
void setup() {
  Serial.begin(9600);
    //valves
  //REG_PORT_DIR0=(1<<23);//Valve1
  pinMode(1,OUTPUT);
 // REG_PORT_DIR1=(1<<23);//Valve 2
  pinMode(13,OUTPUT);
  
  //Motor driver 1
 // REG_PORT_DIR0=(1<<10);//Motor 1 direction
   pinMode(2,OUTPUT);
  //REG_PORT_DIR0=(1<<11);//Motor 1 PWM
   pinMode(3,OUTPUT);
 // REG_PORT_DIR0=(1<<22);//Enable 1
   pinMode(0,OUTPUT);

  //unused motor driver 2
 // REG_PORT_DIR1=(1<<10);
 // REG_PORT_DIR1=(1<<11);

  //Motor driver 3
  //REG_PORT_DIR0=(1<<20);//Motor 3 PWM
   pinMode(6,OUTPUT);
  //REG_PORT_DIR0=(1<<21);//Motor 3 direction
   pinMode(7,OUTPUT);
  //REG_PORT_DIR1=(1<<22);//Enable 2 for motor driver 3
   pinMode(14,OUTPUT);
  
   //unused motor driver 4
  // REG_PORT_DIR0=(1<<16);//Motor 4 PWM
  // REG_PORT_DIR0=(1<<17);//Motor 4 direction

  //disables steppers, active low pin
  //REG_PORT_OUTSET0=(1<<22);//enable 1 high
 // REG_PORT_OUTSET1=(1<<22);// enable 2 high
  digitalWrite(0,HIGH);
  digitalWrite(14,HIGH);
  connect_wifi();
  //enable to see status if there is networking errors
  printWifiStatus();
  server.begin();

}
///////////////////////////////////////
//function: Loop
//inputs none
//outputs none
//sends the drink machine an instructions 
/////////////////////////////////////////
void loop() {
  client = server.available();
  char d = '0';
  //checks for clients 
  if (client) {
    //gets the iformation from tcp/ip request
    switch (Command(Get_Command())) {
      case 0:
        d = 'L';
        Motor(d);
        break;
      case 1:
        Motor_Pour();
        break;
      case 2:
        d = 'R';
        Motor(d);
        break;
      case 3:
        side = 'L';
        break;
      case 4:
        Pour_Drink(side);
        break;
      case 5:
        side = 'R';
        break;
      default:
        break;
    }
  }
}
