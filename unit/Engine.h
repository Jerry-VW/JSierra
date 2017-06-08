/******************************************************************************
 *  Engine.h
 *  Created on: 2017/06/07
 *  Definition of the Class Engine
 *  Author: Jerry W
 *****************************************************************************/

#ifndef ENGINE_H_
#define ENGINE_H_

#include "GyroSensor.h"
#include "Motor.h"
#include "BalancerCpp.h"

class Engine {
public:
    static const int LOW;
    static const int NORMAL;
    static const int HIGH;

    Engine(const ev3api::GyroSensor& gyroSensor,
           ev3api::Motor& leftWheel,
           ev3api::Motor& rightWheel,
                    Balancer* balancer);

    void init();
    void run();
    void setCommand(int forward, int turn);

private:
    // get only
    // no "command" thing or "change" thing
    const ev3api::GyroSensor& mGyroSensor;
    // get set
    // engine resets motors and set their PWMs so cannot be const
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    Balancer* mBalancer;
    // normal variables
    int mForward;
    int mTurn;
};

#endif  // ENGINE_H_
