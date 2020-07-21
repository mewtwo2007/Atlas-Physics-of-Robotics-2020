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
}

void loop() {
  //Read the on/off button
  buttonState = digitalRead(Button);
  //Toggle the activeness
  if(buttonState != lastButtonState){
    if (buttonState == HIGH && active == 0){
      active = 1;
    } else if(buttonState == HIGH){
      active = 0;
    }
    delay(50);
  }
  lastButtonState = buttonState;

  //Read joystick
  float joyValX = analogRead (joyX);
  //Map the values
  joyValX = map (joyValX, 0, 1023, -50, 50);
  //Dead zone
  if(joyValX > -3 && joyValX < 3)
  {
    joyValX = 0;
  }
  //Scale it down
  joyValX = joyValX * 0.0015;
  //Adjust the servo pos
  servValP -= joyValX;
  //Make sure it doesn't exceed the boundaries
  if(servValP > 180){
    servValP = 180;
  } else if(servValP < 0)
  {
    servValP = 0;
  }
  //Write it to the servo
  servoP.write((int)servValP);

  //Read joystick
  float joyValY = analogRead(joyY);
  //Map the values
  joyValY = map (joyValY, 0, 1023, -50, 50);
  //Dead zone
  if(joyValY > -3 && joyValY < 3){
    joyValY = 0;
  }
  //Scale it down
  joyValY = joyValY * 0.0075;
  
  //Adjust the servo positions
  servValL -= joyValY;
  servValR += joyValY;
  //Make sure it doensn't exceed the boundaries
  if(servValL > 100){
    servValL = 100;
  } else if(servValL < 86){
    servValL = 86;
  }
  if(servValR > 100){
    servValR = 100;
  } else if(servValR < 86){
    servValR = 86;
  }
  //Write it to the servos
  servoL.write((int)servValL);
  servoR.write((int)servValR);
} 
