//Welcome to BranchWaver2000
//Type 's' to begin
//You can modify the movement with the following commands:
//'a' - set the acceleration value (steps per second square) e.g. a2000
//'v' - set the maximum speed (steps per second) e.g. v3000
//'d' - set the swing range (steps in one direction, full swing is x2), e.g. d300
//Type 'n' to stop the movement.


#include <AccelStepper.h>
char inputCommand;
long inputAcceleration;
long inputMaxSpeed;
long inputDistance;

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
    inputCommand = Serial.read();
    newData = true;
    }
    
  if (newData == true) {
    
    if (inputCommand == 's') {
      runAllowed = true;
      }
      
    if (inputCommand == 'n') {
      
       runAllowed = false;    
       stepper.stop();
       }
       
    if (inputCommand == 'a') {

       inputAcceleration = Serial.parseFloat();

       stepper.setAcceleration(inputAcceleration);
      }
     
   if (inputCommand == 'v') {

      inputMaxSpeed = Serial.parseFloat();

      stepper.setMaxSpeed(inputMaxSpeed);
     }
   if (inputCommand == 'd') {
    
      inputDistance = Serial.parseFloat();

      stepper.moveTo(inputDistance);
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
