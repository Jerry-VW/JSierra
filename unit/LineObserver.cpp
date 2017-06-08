/******************************************************************************
 *  LineObserver.h
 *  Created on: 2017/06/07
 *  Implementation of the Class LineObserver
 *  Author: Jerry W
 *****************************************************************************/

#include "LineObserver.h"

// 定数宣言
const int8_t LineObserver::INITIAL_THRESHOLD = 20;  // 黒色の光センサ値

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineObserver::LineObserver(const ev3api::ColorSensor& colorSensor)
    : mColorSensor(colorSensor),
      mThreshold(INITIAL_THRESHOLD) {
}

/**
 * ライン上か否かを判定する
 * @retval true  ライン上
 * @retval false ライン外
 */
bool LineObserver::isOnLine() {
    // 光センサからの取得値を見て
    // 黒以上であれば「true」を、
    // そうでなければ「false」を返す
    if (mColorSensor.getBrightness() >= mThreshold) {
        return true;
    } else {
        return false;
    }
}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
void LineObserver::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}

// funciton get light rate from sensor: uint8_t
uint8_t LineObserver::getLightRate() {
    // return mColorSensor.get();
    return 0;
}