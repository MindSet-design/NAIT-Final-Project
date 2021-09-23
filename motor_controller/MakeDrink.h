//define PORTs to output
//UNUSED
//motor driver 4
//#define M4Step 16
//#define M4Dir 17
//motor driver 2
//#define M2Dir 10
//#define M2Step 11

//USED

//motor driver 1
#define M1Dir 10
#define M1Step 11
#define Enable1 22

//motor driver 3
#define M3Step 20
#define M3Dir 21
#define Enable2 22

//valves
#define Valve1 23
#define Valve2 23
unsigned long tNow;

//////////////////////////////////////////
//function: Pour_Drink
//inputs:char drink , what valve to use
//Outputs:none
//operates Valve1 and Valve2
//////////////////////////////////////////
void Pour_Drink(char drink) {
  Serial.println(drink);
  //checks letter for what valve to use
  if (drink == 'L') {
    //REG_PORT_OUTSET0=(1<<Valve1);
    digitalWrite(1,HIGH);
    tNow=millis();
    //opens for a second, takes time to open at min voltage
    while (millis()<=(tNow+3000)){
     ; 
    }
    //REG_PORT_OUTCLR0=(1<<Valve1);
    digitalWrite(1,LOW);
  }
if (drink == 'R') {
    //REG_PORT_OUTSET1=(1<<Valve2);
    digitalWrite(13,HIGH);
    tNow=millis();
    //opens for a second
    while (millis()<=(tNow+3000)){
     ; 
    }
    digitalWrite(13,LOW);
   // REG_PORT_OUTCLR1=(1<<Valve2);
  }
}
//////////////////////////////////////////
//function: Motor
//inputs:char d , direction of motor
//Outputs:none
//moves the drinks
//////////////////////////////////////////
void Motor(char d) {
  Serial.println("move");
  if (d == 'L')
  {
   // REG_PORT_OUTSET0=(1<<M1Dir);
    digitalWrite(2,HIGH);
  }
  if (d == 'R')
  {
   // REG_PORT_OUTCLR0=(1<<M1Dir);
    digitalWrite(2,LOW);
  }
  int x = 0;//count
  tNow = millis();
  //enables motor
 // REG_PORT_OUTCLR0=(1<<Enable1);
  digitalWrite(0,LOW);
  while (x <= 102) {
    if (millis() >= 5 + tNow) {
     // REG_PORT_OUTSET0=(1<<M1Step);
      digitalWrite(3,HIGH);
    }
    if (millis() >= 10 + tNow) {
     // REG_PORT_OUTCLR0=(1<<M1Step);
      digitalWrite(3,LOW);
      x++;
      tNow = millis();
    }
  }
  //disables motor
  //REG_PORT_OUTSET0=(1<<Enable1);
  digitalWrite(0,HIGH);
}

//////////////////////////////////////////
//function: Motor_Pour
//inputs:none
//Outputs:none
//Pours shot
//////////////////////////////////////////
void Motor_Pour() {
  int x = 0;//count
  //REG_PORT_OUTSET0=(1<<M3Dir);
  digitalWrite(7,HIGH);
  //enables motor
  //REG_PORT_OUTCLR1=(1<<Enable2);
  digitalWrite(14,LOW);
  tNow = millis();
  while (x <= 550) {
    if (millis() >= 5 + tNow) {
      //REG_PORT_OUTSET0=(1<<M3Step);
      digitalWrite(6,HIGH);
    }
    if (millis() >= 10 + tNow) {
     // REG_PORT_OUTCLR0=(1<<M3Step);
      digitalWrite(6,LOW);
      x++;
      tNow = millis();
    }
  }
  tNow=millis();
  while(millis()<=tNow+5000){
    ;//wait and hold 5 seconds
  }
  x = 0;
  //return to inital position
  //REG_PORT_OUTCLR0=(1<<M3Dir);
  digitalWrite(7,LOW);
  tNow = millis();
  while (x <= 450) {
    if (millis() >= 5 + tNow) {
     // REG_PORT_OUTSET0=(1<<M3Step);
      digitalWrite(6,HIGH);
    }
    if (millis() >= 10 + tNow) {
     // REG_PORT_OUTCLR0=(1<<M3Step);
      digitalWrite(6,LOW);
      x++;
      tNow = millis();
    }
  }
  //disables motor
 // REG_PORT_OUTSET1=(1<<Enable2);
  digitalWrite(14,HIGH);
}
