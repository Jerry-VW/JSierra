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
 */
Driver::Driver(const LineObserver* lineObserver,
                     Engine* engine, 
                     Steerer* steerer)
    : mLineObserver(lineObserver),
      mEngine(engine),
      mSteerer(steerer),
      mIsInitialized(false) {
}

/**
 * Driver's main logic, called every 4ms
 */
void Driver::run() {
    if (mIsInitialized == false) {
        mEngine->init();
        mIsInitialized = true;
    }
    // get turn
    mSteerer ->Steer(&iTurn);
    // params: int forward, int turn 
    mEngine->setCommand(Engine::HIGH, iTurn);
    // 倒立走行を行う
    mEngine->run();
}