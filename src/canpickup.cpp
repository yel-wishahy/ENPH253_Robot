#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
#include <sonar.h>
#include <canpickup.h>
#include <pindefinitions.h>
#include <rservos.h>
#include <Servo.h>
#include <Display.h>
#include <parameters.h>

//**********Servo Angle Parameters**************//
//change these for open and close positions of servos
int sweepOpenAngle = SWEEP_OPEN_ANGLE;
int sweepCloseAngle = SWEEP_CLOSE_ANGLE;

int armDownAngle = ARM_DOWN_ANGLE;
int armUpAngle = ARM_UP_ANGLE;

int gateTopAngle = GATE_TOP_ANGLE; // 47
int gateBotAngle = GATE_BOT_ANGLE; // 175

//*********State Machine Function Dec. and Variables**********//
//Two options for step in state machine
//angle clearance or timers

//time it takes for servo to finish task
const int servoTaskTimeDelay = 100;
const int armUpDelay = 300;
const int sweepCloseDelay = 250;


GateState gateState;
volatile int canCount;

void setupCanPickup() {
  canCount = 0;
  gateState = bottom;
}

void resetCanPickup(){
  canCount = 0;
  gateState = bottom;
}

void canPickup(){
  printDisplay("Can\nPickup",3,1);
  if(canCount >= 3){
    gateState = top;
    gateServo.write(gateTopAngle);
    delay(servoTaskTimeDelay);
  }else if(canCount < 3){
    gateState = bottom;
    gateServo.write(gateBotAngle);
    delay(servoTaskTimeDelay);
  }

  servoTurn(sweepServo, sweepCloseAngle, 700);
  delay(sweepCloseDelay);

  sweepServo.write(sweepOpenAngle);
  delay(servoTaskTimeDelay);

  servoTurn(armServo, armUpAngle, 500);
  // delay(servoTaskTimeDelay);

  if (gateState == bottom) {
    // servoTurn(armServo, 100, 500);
    delay(armUpDelay);
  }

  armServo.write(armDownAngle);
  delay(servoTaskTimeDelay);
  canCount++;

}