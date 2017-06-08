/******************************************************************************
 *  Comm.h
 *  Created on: 2017/06/07
 *  Definition of the Class Comm
 *  Author: Jerry W
 *****************************************************************************/

#ifndef COMM_H_
#define COMM_H_

// moduels' .h files
// #include "LineObserver.h"
#include <string>

class Comm {
  public:
    Comm();

    void run();
    void sendMessage(char*);
    void ReceiveMessage();
    const double& getCmdKp();
    const double& getCmdKi();
    const double& getCmdKd();

  private:
    // modules' pointer that driver needs
    // const LineObserver* mLineObserver;
    // Engine* mEngine;
    // Steerer* mSteerer;

    // normal variables
    // bool mIsInitialized;
    // int iTurn;
    bool bPIDctrl;
    double cmdKp;
    double cmdKi;
    double cmdKd;
};

#endif  // COMM_H_
