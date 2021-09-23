//time varriable
unsigned long RunTime=0;
///////////////////////////////////////
//function: MotionSensor
//inputs: int trigger, value to compare analog read to
//outputs: nonw
//if motion sensors triped turns transistor on
//if motion sensor reads nothing turns transistor off
///////////////////////////////////////
void MotionSensor(int trigger, int OffDelay) {
  //sensor value
  int Msense=0;
  //reads pin
   Msense= analogRead(A0);
  //checks activity
  if(Msense<trigger)
  {
    REG_PORT_OUTSET0=(1<<20);//sets pin 6 high
    RunTime=millis();
  }
  //if low wait 5 seconds then turn off
  if(Msense>=trigger && (millis()>=RunTime+OffDelay))
  {
    REG_PORT_OUTSET0=(1<<20);//sets pin 6 low
  }
}
