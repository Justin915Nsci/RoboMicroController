#include <AccelStepper.h>

//define step pin and directions for AccelStepper objects
int enA = 8;
int In1 = 7;
int In2 = 9;

AccelStepper stepperF(AccelStepper::DRIVER, 3, 2); //front
AccelStepper stepperL(AccelStepper::DRIVER, 5, 4); //left
AccelStepper stepperR(AccelStepper::DRIVER, 7, 6); //right

char val =0; //holds ascii from serial line
//values which must be calibrated during testing
int fFwSpeed;
int lFwSpeed;
int rFwSpeed;

int fBkwSpeed;
int lBkwSpeed;
int rBkwSpeed;

int fLtSpeed;
int lLtSpeed;
int rLtSpeed;

int fRtSpeed = 100;
int lRtSpeed = -50;
int rRtSpeed = -50;

int fCwSpeed = 200;
int lCwSpeed = 200;
int rCwSpeed = 200;

int fCcwSpeed;
int lCcwSpeed;
int rCcwSpeed;
//---------------------------------------------------------------------
 
void setup() {
  // put your setup code here, to run once:S
   stepperF.setMaxSpeed(200.0);
   stepperF.setAcceleration(200.0);
   stepperR.setMaxSpeed(200.0);
   stepperR.setAcceleration(200.0);
   stepperL.setMaxSpeed(200.0);
   stepperL.setAcceleration(200.0);
  

}

void loop() {
  if (Serial.available()){
    val = Serial.read();
    //Serial.println(val);
    if(val == 'w')fwd();
    else if (val == 's')bkw();
    else if (val == 'a')rt();
    else if (val == 'd')lt();
    else if (val == 'q')ccw();
    else if (val == 'e')cw();
    else if (val == 'k')stp();
    stepperF.runSpeed();
    stepperL.runSpeed();
    stepperR.runSpeed();

    if (val == 'o')up();
    else if(val == 'p')down();
  }
  stepperF.runSpeed();
  stepperL.runSpeed();
  stepperR.runSpeed();

}

//HIGH LEVEL MOTOR FUNCTIONS (fwd, bkw, rt, lt, cw, ccw)

void fwd(){
  //Serial.println("Bot moving forward");
  //Make Front, Left, and Right wheels turn clockwise
  fMotor(fFwSpeed);
  rMotor(rFwSpeed);
  lMotor(lFwSpeed);
}

void bkw(){
  //Serial.println("Bot moving backwards");
  //Make Front, Left, Right wheels turn counterclockwise
  fMotor(fBkwSpeed);
  rMotor(rBkwSpeed);
  lMotor(lBkwSpeed);
  
}

void rt(){
  //Serial.println("Bot moving right");
  fMotor(fRtSpeed);
  rMotor(rRtSpeed);
  lMotor(lRtSpeed);
}

void lt(){
  //Serial.println("Bot moving left");
  fMotor(fRtSpeed);
  rMotor(rRtSpeed);
  lMotor(lRtSpeed);
}

void cw() {
  //Serial.println("Bot moving clockwise");
  fMotor(fCwSpeed);
  rMotor(rCwSpeed);
  lMotor(lCwSpeed);
}

void ccw() {
  //Serial.println("Bot moving clockwise");
  fMotor(fCcwSpeed);
  rMotor(rCcwSpeed);
  lMotor(lCcwSpeed);
}

void stp(){
  //Serial.println("Bot Stop");
  fMotor(0);
  rMotor(0);
  lMotor(0);
  digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);
}

//Low Level Motor Functions

void fMotor(int spd){
  //if (spd>0) Serial.println("Front motor clockwise");
  //else if (spd<0) Serial.println("Front motor counterclockwise");
  
  stepperF.setSpeed(spd);
}

void rMotor(int spd){
  //if (spd>0) Serial.println("right motor clockwise");
  //else if (spd<0) Serial.println("right motor counterclockwise");
  
  stepperR.setSpeed(spd);
}

void lMotor(int spd){
  //if (spd>0) Serial.println("left motor clockwise");
  //else if (spd<0) Serial.println("left motor counterclockwise");
  
  stepperL.setSpeed(spd);
}
//Linear actuator functions
void up(){
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  analogWrite(enA,100);
}

void down(){
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  analogWrite(enA,100);
}
