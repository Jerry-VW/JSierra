/******************************************************************************
 *  LineTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Driver.h"

/**
 * コンストラクタ
 * @param lineMonitor     ライン判定
 * @param balancingWalker 倒立走行
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
 * ライントレースする
 */
void Driver::run() {
    if (mIsInitialized == false) {
        mEngine->init();
        mIsInitialized = true;
    }

    //bool isOnLine = mLineObserver->isOnLine();

    // 走行体の向きを計算する
    // int direction = calcDirection(isOnLine);

    // get turn
    mSteerer ->Steer(&iTurn);
    // params: int forward, int turn 
    mEngine->setCommand(Engine::HIGH, iTurn);
    // 倒立走行を行う
    mEngine->run();
}

/**
 * 走行体の向きを計算する
 * @param isOnLine true:ライン上/false:ライン外
 * @retval 30  ライン上にある場合(右旋回指示)
 * @retval -30 ライン外にある場合(左旋回指示)
 */
int Driver::calcDirection(bool isOnLine) {
    if (isOnLine) {
        // ライン上にある場合
        return Engine::LOW;
    } else {
        // ライン外にある場合
        return -Engine::LOW;
    }
}
