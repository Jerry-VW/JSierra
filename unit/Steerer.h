/******************************************************************************
 *  Steerer.h
 *  Created on: 2017/06/07
 *  Definition of the Class Steerer
 *  Author: Jerry W
 *****************************************************************************/

#ifndef STEERER_H_
#define STEERER_H_

//#include "PID.h"
#include "LineObserver.h"

class Steerer {
public:
    explicit Steerer(LineObserver* lineObserver);
    bool Steer(int* pTurn);
    void setTurn();
    void SetTargetReflect(int);
    // test
    int PSteer();

private:
    LineObserver* mLineObserver;
    signed char cTurn;
    int iColorReflect;
    int iTargetRefect;
    double Kp;
    double Ki;
    double Kd;
};
#endif // STEERER_H_
