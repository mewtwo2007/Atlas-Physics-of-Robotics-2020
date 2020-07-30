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

//LED
const int LED = 24;

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
  pinMode (LED, OUTPUT);
  servoR.attach(10);
  servoL.attach(9);
  servoP.attach(22);
  bottom.attach(27);
  top.attach(28);
  
  Serial.begin(9600);
  servoL.write(108);
  servoR.write(71);
  //Starting positions for the reload system
  top.write(0);
  bottom.write(100);
  delay(250);
  top.write(75);
}

void loop() {
  //Read the on/off button
  buttonState = digitalRead(Button);
  //Toggle the activeness
  if(buttonState != lastButtonState){
    if (buttonState == HIGH && active == 0){
      active = 1;
      digitalWrite(LED, HIGH);
    } else if(buttonState == HIGH){
      active = 0;
      digitalWrite(LED, LOW);
    }
    delay(50);
  }
  lastButtonState = buttonState;

  //Read joystick
  float joyValX = analogRead (joyX);
  float joyValY = analogRead(joyY);
  //Is the joystick active? If it is, aim. If it isn't, do the check for firing
  if(joyValX > 505 && joyValX < 515 && joyValY > 405 && joyValY < 505){
    if(active == 1){
      //Get the distance
      distance = ultrasonic.Distance();
      //If it's within the threshold, fire
      if(distance >= 10 && distance <= 400) {
        if(distance <= 30){
          fire();
        }
      }
    }
  } else {
    //Map the values
    joyValX = map (joyValX, 0, 1023, -50, 50);
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

    //Map the values
    joyValY = map (joyValY, 0, 1023, -50, 50);
    //Scale it down
    joyValY = joyValY * 0.0075;
    //Adjust the servo positions
    servValL -= joyValY;
    servValR += joyValY;
    //Make sure it doensn't exceed the boundaries
    if(servValL > 108){
      servValL = 108;
    } else if(servValL < 90){
      servValL = 90;
    }
  
    if(servValR > 90){
      servValR = 90;
    } else if(servValR < 71){
      servValR = 71;
    }
    //Write it to the servos
    servoL.write((int)servValL);
    servoR.write((int)servValR);
  }
}

void fire(){
  //Starting position
  servoL.write(servValL);
  servoR.write(servValR);
  delay(250);
  //Firing positions
  servoL.write(5);
  servoR.write(175);
  delay(500);
  //Back to the starting position
  servoL.write(servValL);
  servoR.write(servValR);
  delay(500);
  //Reload
  reload();
  delay(500);
}

void reload() {
  //Move the bottom out, then back in
  bottom.write(50);
  delay(90);
  bottom.write(100);
  delay(250);
  //Move the top out, then back in
  top.write(0);
  delay(250);
  top.write(75);
}
