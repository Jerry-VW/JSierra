/******************************************************************************
 *  Steerer.h
 *  Created on: 2017/06/07
 *  Implementation of the Class Steerer
 *  Author: Jerry W
 *  Controls turn value for driver.
 *****************************************************************************/

#include "Steerer.h"

#define CALIBRATE 20.0 // black-white 0 ~ 40

// Constructor
Steerer::Steerer()
    : dTargetBrightness(0.0),
      dKp(5.1), dKi(0.5), dKd(4.1) {
}


void Steerer::init(double* driverCSB) {
    // get brightness address first, then initialize PID
    rawCSBrightness = driverCSB;
    // params: now, set-to, target
    mPID = new PID(&fixedBrightness, &mTurn, &dTargetBrightness, dKp, dKi, dKd, DIRECT);
    mPID -> SetMode(AUTOMATIC);
}

// function : Compute turn power (PID)
// Pass color sensor value here
// param 1:pointer input
// param 2:pointer output twisting force
bool Steerer::Steer(int* driverTurn) {
    // calibrate raw data
    fixedBrightness = calibrateBrightness();
    // PID steer
    mPID -> Compute();
    *driverTurn = (int) mTurn;

    // test use simple steer
    //*pTurn = PSteer();

    return true;
}

/**
 * raw color sensor value: (uint8_t) 0 ~ 100
 * limit range to -CALIBRATE ~ +CALIBRATE
 * center is 0
 */
double Steerer::calibrateBrightness() {
    fixedBrightness = *rawCSBrightness - CALIBRATE;
    if (fixedBrightness > CALIBRATE) {
        // bigger than MAX
        return CALIBRATE;
    } else if (fixedBrightness < -CALIBRATE) {
        // smaller than MIN
        return -CALIBRATE;
    }
    // between MAX and MIN
    return fixedBrightness;
}

// simple Protortional control
int Steerer::PSteer() {
    if (fixedBrightness > 0.0) {
        return -20;
    } else {
        return 20;
    }
}

// function : set Turn directly
void Steerer::setTurn() {

}

// PID tunings
double Steerer::getP() { return mPID -> GetKp(); }
double Steerer::getI() { return mPID -> GetKi(); }
double Steerer::getD() { return mPID -> GetKd(); }

bool Steerer::setPIDTunings(const double& driverP,
                   const double& driverI,
                   const double& driverD) {
    dKp = driverP;
    dKi = driverI;
    dKd = driverD;
    mPID ->SetTunings(dKp, dKi, dKd);
    return true;
}