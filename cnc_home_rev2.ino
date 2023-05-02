/* Example sketch to control a stepper motor with TB6600 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */


/* example of stepping and for loop for c++ reference
for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  } 
  */

// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin_t 8
#define stepPin_t 9
#define dirPin_m 3
#define stepPin_m 2
#define motorInterfaceType 1

const int proxPin = 7;

int homeState = 0;
int proxState = 1;
int prevProxState = 0;
int currPos = 0;
int maxTravel = -16000;

// Create a new instance of the AccelStepper class:
// AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin_t, dirPin_t);
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin_m, dirPin_m);

void setup() {
  stepper.setMaxSpeed(7000);
  stepper.setAcceleration(2500);
  pinMode(proxPin, INPUT);
  Serial.begin(9600);

  while (homeState != HIGH) {
    proxState = digitalRead(proxPin);
    if (proxState == LOW) {
      homeState = HIGH;
      stepper.setCurrentPosition(0);
    } else {
      stepper.setSpeed(150);
      stepper.move(50);
      stepper.run();
    }
    delayMicroseconds(100);
    }
  }

void loop() {
  stepper.runToNewPosition(maxTravel);
  stepper.runToNewPosition(-200);
  stepper.stop();
}