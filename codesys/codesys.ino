#include "Wireless.h"
unsigned long wait = 0; //time
float temp = 20;

void setup() {
  Serial.begin(9600);

  // inputs
 // REG_PORT_DIR0 = (0 << 22); //D0
 // REG_PORT_DIR0 = (0 << 23); //D1
  //REG_PORT_DIR0 = (0 << 10); //D2
 // REG_PORT_DIR0 = (0 << 11); //D3
 // REG_PORT_DIR0 = (0 << 20); //D6
  //REG_PORT_DIR0 = (0 << 21); //D7
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(14, INPUT);

  // outputs
  //REG_PORT_DIR1 = (1 << 11); //D5 light
  //REG_PORT_DIR1 = (1 << 10); //D4 cold
  //REG_PORT_DIR1 = (1 << 22); //D13 room temp
  //REG_PORT_DIR1 = (1 << 23); //D14 hot
  pinMode(5, OUTPUT);//light
  pinMode(4, OUTPUT);//cold
  pinMode(13, OUTPUT);//hot
  //set inital state to room temp with cooling on
  digitalWrite(5,HIGH);
  digitalWrite(13, LOW);
  digitalWrite(4,LOW);
  //wifi setup
  connect_wifi();

  //use if networking not working
  printWifiStatus();
  wait = millis();
}

///////////////////////////////////////
//function: Loop
//inputs none
//outputs none
//sends the drink machine an instructions and reads temp
//sends info about temp to rasp pi
/////////////////////////////////////////
void loop() {
  String Stemp;
  //checks the input port and sends commands accordingly
  switch (int index = PORTA_Read()) {
    case 0:
      Stemp = Send_Command("Lleft\n");
      wait = millis();
      break;
    case 1:
      Stemp = Send_Command("Lpour\n");
      wait = millis();
      break;
    case 2:
      Stemp = Send_Command("Lright\n");
      wait = millis();
      break;
    case 3:
      Stemp = Send_Command("Pleft\n");
      wait = millis();
      break;
    case 4:
      Stemp = Send_Command("Ppour\n");
      wait = millis();
      break;
    case 5:
      Stemp = Send_Command("Pright\n");
      wait = millis();
      break;
    case 6:
      break;
    default:
      break;
  }
  temp = Stemp.toFloat();
  //checks temperature every 15 seconds if theres no input
  if (millis() > (wait + 15000)) {
    Send_Command("temp");
    temp = Stemp.toFloat();
    wait = millis();
  }

  //sets a pin high for temp in codesys
  if (temp < 18) { //cold
    //REG_PORT_OUTSET1 = (1 << 10);
   // REG_PORT_OUTCLR1 = (1 << 22);
    //REG_PORT_OUTCLR1 = (1 << 23);
    //cooling light off
   // REG_PORT_OUTCLR1 = (1 << 11);
    digitalWrite(4, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(5, LOW);
  }

  if (temp < 25 && temp > 18) { //room temp
    //REG_PORT_OUTSET1 = (1 << 22);
    //REG_PORT_OUTCLR1 = (1 << 10);
    //REG_PORT_OUTCLR1 = (1 << 23);
    //cooling light on
    //REG_PORT_OUTSET1 = (1 << 11);
    digitalWrite(4, LOW);
    digitalWrite(13, LOW);
    digitalWrite(5, HIGH);
  }

  if (temp > 25 && temp < 100) { //hot
   // REG_PORT_OUTSET1 = (1 << 23);
   // REG_PORT_OUTCLR1 = (1 << 22);
    //REG_PORT_OUTCLR1 = (1 << 10);
    //cooling light on
    //REG_PORT_OUTSET1 = (1 << 11);
    digitalWrite(4, LOW);
    digitalWrite(13, LOW);
    digitalWrite(5, HIGH);
  }
}

///////////////////////////////////////
//function: PORTA_READ
//inputs none
//outputs int 0-5
//checks inputs and returns int for switch
/////////////////////////////////////////
int PORTA_Read() {
  //reads PORTA inputs
  // int D0 = (REG_PORT_IN0 >> 22) & 1;
  // int D1 = (REG_PORT_IN0 >> 23) & 1;
  // int D2 = (REG_PORT_IN0 >> 10) & 1;
  // int D3 = (REG_PORT_IN0 >> 11) & 1;
  // int D6 = (REG_PORT_IN0 >> 20) & 1;
  // int D7 = (REG_PORT_IN0 >> 21) & 1;
  bool D0 = digitalRead(0);
  bool D1 = digitalRead(1);
  bool D2 = digitalRead(2);
  bool D3 = digitalRead(3);
  bool D6 = digitalRead(6);
  bool D14 = digitalRead(14);
  Serial.println(D0);
  Serial.println(D1);
  Serial.println(D2);
  Serial.println(D3);
  Serial.println(D6);
  Serial.println(D14);
  //returns the button pressed
  if (D0) {
    return 0;
  }
  if (D1) {
    return 1;
  }
  if (D2) {
    return 2;
  }
  if (D3) {
    return 3;
  }
  if (D6) {
    return 4;
  }
  if (D14) {
    return 5;
  }
  return 6;
}
