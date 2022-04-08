#include <AccelStepper.h>
char command;
long acceleration;


const int ms1 = 5;
const int ms2 = 18;
const int ms3 = 19;

bool newData = false;
bool runAllowed = false;

// Define a stepper and the pins it will use
AccelStepper stepper(1, 2, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
void setup(){
  Serial.begin(115200);

//Microstepping
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, HIGH); // 1, 1, 1 -> 1/16
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);
    
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(5000); //steps per second
  stepper.setAcceleration(3000); //steps per second square
  stepper.moveTo(800);
}

void loop()
{
checkSerial();
runSwing();

}

void checkSerial(){
  if (Serial.available() > 0) {
    command = Serial.read();
    newData = true;}
  if (newData == true) {
    if (command == 's') {
      runAllowed = true;
      Serial.println("Command recieved");
      }
    if (command == 'n') {
       runAllowed = false;
       stepper.stop();
       }
    if (command == 'a') {
        runAllowed = false;

        acceleration = Serial.parseFloat();

        stepper.setAcceleration(acceleration);
      
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
