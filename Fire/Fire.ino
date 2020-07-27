#include <AFMotor.h>
#include <Servo.h>

Servo servoR;
Servo servoL;
Servo servoP;

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
  Serial.begin(9600);
  //servoL.write(104);
  //servoR.write(76);
}

void loop() {
  //Down positions
  servoL.write(104);
  servoR.write(76);
  delay(3000);
  //Firing positions
  servoL.write(30);
  servoR.write(150);
  delay(3000);
}
