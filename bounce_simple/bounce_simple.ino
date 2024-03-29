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
long inputAngle;
long inputSteps;
long currentPos;
long currentSpeed;


// Initialize pins for microstepping
const int ms1 = 7;
const int ms2 = 8;
const int ms3 = 9;

// Enable pin
const int enbl = 10;


// Flags
bool newData = false;      
bool runAllowed = false;

// Define a stepper and the pins it will use
AccelStepper stepper(1, 4, 3); 

void setup(){
  Serial.begin(115200);

// Enable
  stepper.setEnablePin(enbl);
  stepper.setPinsInverted(false, false, true);

//Microstepping
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, HIGH); // 1, 1, 1 -> 1/16
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);

// Initial stepper movement parameters
  stepper.setMaxSpeed(500); //steps per second
  stepper.setAcceleration(1000); //steps per second square
  stepper.moveTo(533); //number of steps

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
       
       stepper.disableOutputs();
       }
       
    if (inputCommand == 'a') {

       inputAcceleration = Serial.parseFloat();

       stepper.setAcceleration(inputAcceleration);

       Serial.println("New acceleration: " + String(inputAcceleration));
      }
     
   if (inputCommand == 'v') {

      inputMaxSpeed = Serial.parseFloat();

      stepper.setMaxSpeed(inputMaxSpeed);

      Serial.println("New speed: " + String(inputMaxSpeed));
     }
   if (inputCommand == 'd') {
    
      inputAngle = Serial.parseFloat();

      inputSteps = inputAngle*8.8889;

      stepper.moveTo(inputSteps);

      Serial.println("New angle: " + String(inputAngle));
    }
  }
}

void runSwing(){
  
  if (runAllowed == true){
    
    stepper.enableOutputs();
    
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
      
      stepper.run();
    }
} 
