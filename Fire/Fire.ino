#include <AFMotor.h>
#include <Servo.h>
#include <SR04.h>

//Pins for the ultrasonic sensor
#define TRIG_PIN 25
#define ECHO_PIN 26

//Define the ultrasonic sensor and the variable for the distance
SR04 ultrasonic = SR04(ECHO_PIN,TRIG_PIN);
long distance;

//The various servos
Servo servoR;
Servo servoL;
Servo servoP;

Servo bottom;
Servo top;

//Joystick Pins
const int joyX = 1;
const int joyY = 0;

//Variables for the on/off button
const int Button = 23;
int buttonState = 0;
int lastButtonState = 0;

//Joystick Values
float joyValY;
float joyValX;

//Servo positions
float servValR = 90;
float servValL = 90;
float servValP = 90;

int active = 0;

void setup() {
  pinMode (joyX, INPUT);
  pinMode (joyY, INPUT);
  pinMode (Button, INPUT);
  servoR.attach(10);
  servoL.attach(9);
  servoP.attach(22);
  bottom.attach(27);
  top.attach(28);
  Serial.begin(9600);
  //servoL.write(104);
  //servoR.write(76);
  servoL.write(104);
  servoR.write(76);
}

void loop() {
  //Get the distance
  distance = ultrasonic.Distance();
  if(distance >= 10 && distance <= 400) {
    if(distance <= 40){
      fire();
    }
  }
  delay(3000);
  
}

void fire(){
  //Down positions
  servoL.write(104);
  servoR.write(76);
  delay(250);
  //Firing positions
  servoL.write(5);
  servoR.write(175);
  delay(250);
  servoL.write(104);
  servoR.write(76);
}
