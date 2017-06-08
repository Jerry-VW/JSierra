/******************************************************************************
 *  Driver.h
 *  Created on: 2017/06/07
 *  Definition of the Class Driver
 *  Author: Jerry W
 *****************************************************************************/

#ifndef DRIVER_H_
#define DRIVER_H_

// moduels' .h files
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
    // modules' pointer that driver needs
    const LineObserver* mLineObserver;
    Engine* mEngine;
    Steerer* mSteerer;
    // normal variables
    bool mIsInitialized;
    int iTurn;
};

#endif  // DRIVER_H_
