 #include <AccelStepper.h>

long recDist = 0;
long recSpeed = 0;
long recAccel = 0;
char recCommand;
// s = start 
// a = set acceleration
// v = set speed
// d = set distance
// n = stop

const int ms1 = 5;
const int ms2 = 18;
const int ms3 = 19;

bool newData, runallowed = false;

AccelStepper stepper(1, 2, 4);

void setup() {
  Serial.begin(115200);

//Microstepping
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, HIGH); // 1, 1, 1 -> 1/16
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);
  
  stepper.setMaxSpeed(3000);
  stepper.setAcceleration(2000);
  stepper.moveTo(800);

}

void loop() {

  checkSerial();
  runSwing();
  
}

void runSwing(){
  if (runallowed == true){
    if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());

    stepper.run();}
  }

void checkSerial(){
  if (Serial.available() > 0) {
    recCommand = Serial.read();
    newData = true;
    }
  if (newData == true) {
    if (recCommand == 's'){
      runallowed = true;
      
      recDist = Serial.parseFloat();
      recSpeed = Serial.parseFloat();

      Serial.println("Swing distance set to" + String(recDist));
      Serial.println("Swing speed set to" + String(recSpeed));

      stepper.setMaxSpeed(recSpeed);
      stepper.move(recDist);}
      
    if (recCommand == 'n') {
      runallowed = false;
      Serial.println("STOP");
      stepper.stop();
      stepper.setMaxSpeed(0);
      stepper.move(0);
      delay(10);}
  }}
