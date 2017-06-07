/******************************************************************************
 *  BalancingWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class BalancingWalker
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
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
    const ev3api::GyroSensor& mGyroSensor;
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    Balancer* mBalancer;
    int mForward;
    int mTurn;
};

#endif  // ENGINE_H_
