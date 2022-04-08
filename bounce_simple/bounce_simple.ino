#include <AccelStepper.h>
char inpCommand;
long inpAcceleration;
long inpMaxSpeed;
long inpDistance;

// Initialize pins for microstepping
const int ms1 = 5;
const int ms2 = 18;
const int ms3 = 19;

// Flags
bool newData = false;      
bool runAllowed = false;

// Define a stepper and the pins it will use
AccelStepper stepper(1, 2, 4); 


void setup(){
  Serial.begin(115200);

//Microstepping
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, HIGH); // 1, 1, 1 -> 1/16
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);
    
// Initial stepper movement parameters
  stepper.setMaxSpeed(5000); //steps per second
  stepper.setAcceleration(3000); //steps per second square
  stepper.moveTo(800); //number of steps
}

void loop()
{
checkSerial();
runSwing();

}

void checkSerial(){
  if (Serial.available() > 0) {
    inpCommand = Serial.read();
    newData = true;
    }
    
  if (newData == true) {
    
    if (inpCommand == 's') {
      runAllowed = true;
      }
      
    if (inpCommand == 'n') {
       stepper.moveTo(0);       
       runAllowed = false;
       stepper.stop();
       }
       
    if (inpCommand == 'a') {

       inpAcceleration = Serial.parseFloat();

       stepper.setAcceleration(inpAcceleration);
      }
     
   if (inpCommand == 'v') {

      inpMaxSpeed = Serial.parseFloat();

      stepper.setMaxSpeed(inpMaxSpeed);
     }
   if (inpCommand == 'd') {
    
      inpDistance = Serial.parseFloat();

      stepper.moveTo(inpDistance);
    }
  }
}

void runSwing(){
  if (runAllowed == true){
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
      
      stepper.run();
    }
}
