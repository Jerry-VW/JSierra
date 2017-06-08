/******************************************************************************
 *  Steerer.h
 *  Created on: 2017/06/07
 *  Implementation of the Class Steerer
 *  Author: Jerry W
 *  Controls turn value for driver.
 *****************************************************************************/

#include "Steerer.h"
//#include "PID.h"


// Constructor
Steerer::Steerer(LineObserver* lineObserver) : mLineObserver(lineObserver), Kp(1.0), Ki(1.0), Kd(1.0) {
    //mLineObserver = lineObserver;
    // initialize PID tracer
    // params: now, set-to, target
    //PID pTracer(&iColorReflect, &cTurn, &iTargetRefect, Kp, Ki, Kd, DIRECT);
}

// function : Compute turn power (PID)
// Pass color sensor value here
// param 1:pointer forward force
// param 2:pointer twisting force
// param 3:uint8_t color sensor reflect power (0-100)
bool Steerer::Steer(int* pTurn){
    // test use simple steer
    *pTurn = PSteer();
    return true;
}

// function : set Turn manually
void Steerer::setTurn() {

}

// simple Protortional control
int Steerer::PSteer() {
    if (mLineObserver -> isOnLine()) {
        return -25;
    } else {
        return 25;
    }
}


void Steerer::SetTargetReflect(int iNewTarget){
    iTargetRefect = iNewTarget;
}