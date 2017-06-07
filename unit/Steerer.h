//
//  Steer.h
//  JSierra
//
//  Created by WANGWENQIAN on 2017/06/01.
//
//

#ifndef Steer_h
#define Steer_h

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
#endif /* Steer_h */
