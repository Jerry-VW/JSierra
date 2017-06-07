/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef LINEOBSERVER_H_
#define LINEOBSERVER_H_

#include "ColorSensor.h"

// 定義
class LineObserver {
public:
    explicit LineObserver(const ev3api::ColorSensor& colorSensor);

    bool isOnLine();
    void setThreshold(int8_t threshold);
    //method
    uint8_t getLightRate();
private:
    static const int8_t INITIAL_THRESHOLD;

    const ev3api::ColorSensor& mColorSensor;
    int8_t mThreshold;
};

#endif  // LINEOBSERVER_H_
