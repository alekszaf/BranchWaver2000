#include <AccelStepper.h>
char command;
long inAcceleration;
long inMaxSpeed
long inDistance

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
    command = Serial.read();
    newData = true;
    }
    
  if (newData == true) {
    
    if (command == 's') {
      runAllowed = true;
      }
      
    if (command == 'n') {
       runAllowed = false;
       stepper.stop();
       }
       
    if (command == 'a') {
       runAllowed = false;

       inAcceleration = Serial.parseFloat();

       stepper.setAcceleration(acceleration);
      }
     
   if (command == 'v') {
      runAllowed = false;
      
      inMaxSpeed = Serial.parseFloat();

      stepper.setMaxSpeed(inMaxSpeed);
     }
   if (command == 'd') {
      runAllowed = false;

      inDistance = Serial.parseFloat();

      stepper.moveTo(inDistance);
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
