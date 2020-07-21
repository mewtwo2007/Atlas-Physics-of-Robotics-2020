#include <AFMotor.h>

//Initialize the motor
AF_DCMotor motor(4);

int active = 1;

void setup() {
  //Set speed and make sure it is stopped
  motor.setSpeed(255);
  motor.run(RELEASE);
}

void loop() {
  if(active == 1){
    fire(3000);
    delay(3000);
  }
}

void fire(uint length) {
  //Turn it on, wait, then stop it
  motor.run(FORWARD);
  delay(length);
  motor.run(RELEASE);
}
