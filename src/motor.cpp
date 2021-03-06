#include <Motor.h>
#include <Arduino.h>
#include <PinDefinitions.h>
#include <Display.h>

int freq;

void setupMotors(){
    pinMode(MOTOR_LEFT_FWD, OUTPUT);
    pinMode(MOTOR_LEFT_REV, OUTPUT);
    pinMode(MOTOR_RIGHT_FWD, OUTPUT);
    pinMode(MOTOR_RIGHT_REV, OUTPUT);
    freq=200;
}

void driveMotors(int LFpwm, int LRpwm, int RFpwm, int RRpwm){
    pwm_start(MOTOR_LEFT_FWD, freq, LFpwm, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(MOTOR_LEFT_REV, freq, LRpwm, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(MOTOR_RIGHT_FWD, freq, RFpwm, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(MOTOR_RIGHT_REV, freq, RRpwm, RESOLUTION_12B_COMPARE_FORMAT);
}

void stopMotors(){
    driveMotors(0,0,0,0);
    pwm_stop(MOTOR_LEFT_FWD);
    pwm_stop(MOTOR_LEFT_REV);
    pwm_stop(MOTOR_RIGHT_FWD);
    pwm_stop(MOTOR_RIGHT_REV);
}

