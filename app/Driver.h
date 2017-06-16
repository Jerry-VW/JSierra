/******************************************************************************
 *  Driver.h
 *  Created on: 2017/06/07
 *  Definition of the Class Driver
 *  Author: Jerry W
 *****************************************************************************/

#ifndef DRIVER_H_
#define DRIVER_H_

// modules' .h files
#include "LineObserver.h"
#include "Engine.h"
#include "Steerer.h"
#include "Comm.h"

class Driver {
  public:
    Driver(LineObserver* lineobserver,
           Engine* engine,
           Steerer* steerer,
           Comm* comm);
    void run();

    // PID tuning
    double getSteererP();
    double getSteererI();
    double getSteererD();
    bool setSteererPIDTunings(double, double, double);

  private:
    // modules' pointer that driver needs
    LineObserver* mLineObserver;
    Engine* mEngine;
    Steerer* mSteerer;
    Comm* mComm;
    // normal variables
    bool mIsInitialized;
    int iTurn;
    double dCSBrightness; //color sensor brightness
};

#endif  // DRIVER_H_
