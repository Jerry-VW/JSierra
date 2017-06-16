/******************************************************************************
 *  Driver.h
 *  Created on: 2017/06/07
 *  Implementation of the Class Driver
 *  Author: Jerry W
 *****************************************************************************/

#include "Driver.h"

/**
 * Constructor
 * @param lineObserver
 * @param engine
 * @param steerer
 * @param comm
 */
Driver::Driver(LineObserver* lineObserver,
               Engine* engine,
               Steerer* steerer,
               Comm* comm)
    : mLineObserver(lineObserver),
      mEngine(engine),
      mSteerer(steerer),
      mComm(comm),
      mIsInitialized(false) {
}

/**
 * Driver's main logic, called every 4ms
 */
void Driver::run() {
    if (mIsInitialized == false) {
        mEngine -> init();
        mSteerer -> init(&dCSBrightness);
        mIsInitialized = true;
    }
    // update color sensor brightness value
    dCSBrightness = mLineObserver -> getBrightness();
    // get turn
    mSteerer -> Steer(&iTurn);
    // params: int forward, int turn
    // normal drive
    //mEngine -> setCommand(Engine::NORMAL, iTurn);
    // idle test
    mEngine -> setCommand(Engine::LOW, 0);
    // 倒立走行を行う
    mEngine -> run();

    mComm -> setBrightnessTurn(&dCSBrightness, &iTurn);
}

// PID tuning
double Driver::getSteererP() { return mSteerer -> getP(); }
double Driver::getSteererI() { return mSteerer -> getI(); }
double Driver::getSteererD() { return mSteerer -> getD(); }

bool Driver::setSteererPIDTunings(double commP,
                                  double commI,
                                  double commD) {
    mSteerer -> setPIDTunings(commP, commI, commD);
    return true;
}