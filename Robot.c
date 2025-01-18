#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include <assert.h>
#include "MotorHat.h" // Ensure this header defines Adafruit_MotorHAT, Adafruit_DCMotor, etc.
#include "Robot.h"

void RobotInit(Robot *robot, unsigned int address, int left_id, int right_id, int left_trim, int right_trim, bool stop_at_exit) {
    // Set default values if necessary
    address = (address == 0) ? 0x60 : address;
    left_id = (left_id == 0) ? 1 : left_id;
    right_id = (right_id == 0) ? 2 : right_id;
    left_trim = (left_trim == 0) ? 0 : left_trim;
    right_trim = (right_trim == 0) ? 0 : right_trim;
    stop_at_exit = (stop_at_exit == 0) ? true : stop_at_exit;

    // Initialize MotorHat
    Adafruit_MotorHat *mh = Adafruit_MotorHat_Create(address);
    robot->address = address;
    robot->left_motor = Adafruit_MotorHat_getMotor(mh, left_id);
    robot->right_motor = Adafruit_MotorHat_getMotor(mh, right_id);
    robot->left_trim = left_trim;
    robot->right_trim = right_trim;
    robot->stop_at_exit = stop_at_exit;

    // Release motors at start
    robot->left_motor->run(RELEASE);
    robot->right_motor->run(RELEASE);

    // Register stop function if stop_at_exit is true
    if (stop_at_exit) {
        atexit(RobotStop);
    }
}

void RobotStop(Robot *robot) {
    robot->left_motor->run(RELEASE);
    robot->right_motor->run(RELEASE);
}

void _left_speed(Robot *robot, int speed) {
    assert(0 <= speed && speed <= 255);
    speed += robot->left_trim;
    speed = (speed < 0) ? 0 : (speed > 255) ? 255 : speed;
    robot->left_motor->setSpeed(speed);
}

void _right_speed(Robot *robot, int speed) {
    assert(0 <= speed && speed <= 255);
    speed += robot->right_trim;
    speed = (speed < 0) ? 0 : (speed > 255) ? 255 : speed;
    robot->right_motor->setSpeed(speed);
}

void RobotForward(Robot *robot, int speed, int seconds) {
    _left_speed(robot, speed);
    _right_speed(robot, speed);
    robot->left_motor->run(FORWARD);
    robot->right_motor->run(FORWARD);
    if (seconds > 0) {
        bcm2835_delay(seconds * 1000);
        RobotStop(robot);
    }
}

void RobotBackward(Robot *robot, int speed, int seconds) {
    _left_speed(robot, speed);
    _right_speed(robot, speed);
    robot->left_motor->run(BACKWARD);
    robot->right_motor->run(BACKWARD);
    if (seconds > 0) {
        bcm2835_delay(seconds * 1000);
        RobotStop(robot);
    }
}

void RobotRight(Robot *robot, int speed, int seconds) {
    _left_speed(robot, speed);
    _right_speed(robot, speed);
    robot->left_motor->run(FORWARD);
    robot->right_motor->run(BACKWARD);
    if (seconds > 0) {
        bcm2835_delay(seconds * 1000);
        RobotStop(robot);
    }
}

void RobotLeft(Robot *robot, int speed, int seconds) {
    _left_speed(robot, speed);
    _right_speed(robot, speed);
    robot->left_motor->run(BACKWARD);
    robot->right_motor->run(FORWARD);
    if (seconds > 0) {
        bcm2835_delay(seconds * 1000);
        RobotStop(robot);
    }
}
