#include <AccelStepper.h>

const int ms1 = 5;
const int ms2 = 18;
const int ms3 = 19;

// Define a stepper and the pins it will use
AccelStepper stepper(1, 2, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
void setup(){

//Microstepping
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, HIGH); // 1, 1, 1 -> 1/16
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);
    
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(1000); //steps per second
  stepper.setAcceleration(2000); //steps per second square
  stepper.moveTo(500);
}
void loop()
{
   
 for (int i=0; i <= 5; i++) {
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());         // If at the end of travel go to the other end
      stepper.run();
//      if (i == 5) {
//        stepper.moveTo(0);}
        }
}
