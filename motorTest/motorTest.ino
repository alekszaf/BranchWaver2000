
int degToStep;
char dir;
double deg;
const int stepPin = 2;
const int dirPin = 4;
const int motorDelay1 = 2000;
/*pins for microstepping small stepper*/

const int ms1 = 5;
const int ms2 = 18;
const int ms3 = 19;
const int moveDel = 300;
int swingReps = 0;
int i = 0;
const int microsteps1 = 800;  // quarter step = 200*4 steps per revolution

/*communication vars*/

bool isData = false;
String Command;

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin, OUTPUT); // small stepper
  pinMode(dirPin, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, LOW);  // Quarter step (0,1,0)
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, LOW);

  Serial.begin(115200);
  while (!Serial);
}


void jogMot(String str) {

  /* Expected string is of form JOGCART+45 or JOGCART-23 to move the motor in ccw or cw direction
    by the requested angle in degrees. Angle is converted based on microstepping. 200 steps per
    revolution in full step. Using quarter step, this means 800 steps per revolution (360 degrees)*/

  dir = str[6];
  Serial.println("DIR CHAR >");
  Serial.println(dir);
  if ((dir == '+') || (dir == '-')) {
    Serial.println("Direction received");
    if (dir == '+') {
      digitalWrite(dirPin, LOW);
      Serial.println("Jogging - anticlockwise");
    }
    else {
      digitalWrite(dirPin, HIGH);
      Serial.println("Jogging - clockwise");
    }
    Serial.println("");
    deg = str.substring(7).toDouble();
    Serial.println("Degrees:");
    Serial.println(deg);
    Serial.println("");
    degToStep = int((microsteps1 / 360) * deg);
    Serial.println("Steps:");
    Serial.println(degToStep);
    Serial.println("");

    for (int x = 0; x < degToStep; x++) {
      digitalWrite(stepPin, LOW);
      delayMicroseconds(motorDelay1);
      digitalWrite(stepPin, HIGH);
    }
  }
  else {
    Serial.println("Invalid syntax: Expected 'JOGMOT<sign><degrees>' e.g. 'JOGMOT+34' or 'JOGMOT-33' ...");
  }
}


void swing(String comm){
  swingReps = comm.substring(5).toInt();
  for (int i=0; i <= swingReps; i++){
    if (i == 0) {
      jogMot("JOGMOT-40");
    }
    else {
    
        jogMot("JOGMOT-80");
        
    }
    delay(moveDel);
    
    jogMot("JOGMOT+80");
    if (i == swingReps) {
          delay(moveDel);
          jogMot("JOGMOT-40"); 
      }
    
    delay(moveDel);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  while (Serial.available() > 0) {

    char value = Serial.read();
    Command += value;

    if (value == '\n') {
      isData = true;
    }
  }

  if (isData) {
    isData = false;

    if (Command.startsWith("JOGMOT")) {
      jogMot(Command);
    }
    if (Command.startsWith("SWING")) {
      swing(Command);
    }
        Command = "";
  }
  delay(20);
}
