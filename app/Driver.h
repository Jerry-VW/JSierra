/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef DRIVER_H_
#define DRIVER_H_

#include "LineObserver.h"
#include "Engine.h"
#include "Steerer.h"

class Driver {
public:
    Driver(const LineObserver* lineobserver, 
                 Engine* engine, 
                 Steerer* steerer);

    void run();

private:
    const LineObserver* mLineObserver;
    Engine* mEngine;
    Steerer* mSteerer;

    bool mIsInitialized;

    int calcDirection(bool isOnLine);

    int iTurn;
};

#endif  // EV3_APP_LINETRACER_H_
