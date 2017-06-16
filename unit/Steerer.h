/******************************************************************************
 *  Steerer.h
 *  Created on: 2017/06/07
 *  Definition of the Class Steerer
 *  Author: Jerry W
 *****************************************************************************/

#ifndef STEERER_H_
#define STEERER_H_

#include "PID.h"

class Steerer {
  public:
    explicit Steerer();
    void init(double* driverCSB);
    bool Steer(int* driverTurn);
    void setTurn();

    // PID tuning
    double getP();
    double getI();
    double getD();
    bool setPIDTunings(const double&, const double&, const double&);

  private:
    double calibrateBrightness();
    int PSteer();

    PID* mPID;
    double fixedBrightness; // fixed brightness, ready for PID
    double* rawCSBrightness; // raw driver's value
    double mTurn;
    double dSensorBrightness;
    double dTargetBrightness;
    double dKp;
    double dKi;
    double dKd;
};
#endif // STEERER_H_
