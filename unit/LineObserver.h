/******************************************************************************
 *  LineObserver.h
 *  Created on: 2017/06/07
 *  Definition of the Class LineObserver
 *  Author: Jerry W
 *****************************************************************************/

#ifndef LINEOBSERVER_H_
#define LINEOBSERVER_H_

#include "ColorSensor.h"


class LineObserver {
public:
    explicit LineObserver(const ev3api::ColorSensor& colorSensor);

    bool isOnLine();
    void setThreshold(int8_t threshold);
    //method
    uint8_t getBrightness();
private:
    static const int8_t INITIAL_THRESHOLD;

    const ev3api::ColorSensor& mColorSensor;
    int8_t mThreshold;
};

#endif  // LINEOBSERVER_H_
