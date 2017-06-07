/******************************************************************************
 *  Engine.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class BalancingWalker
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Engine.h"

// 定数宣言
const int Engine::LOW    = 30;    // 低速
const int Engine::NORMAL = 50;    // 通常
const int Engine::HIGH   = 70;    // 高速

/**
 * コンストラクタ
 * @param gyroSensor ジャイロセンサ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 * @param balancer   バランサ
 */
Engine::Engine(const ev3api::GyroSensor& gyroSensor,
                                 ev3api::Motor& leftWheel,
                                 ev3api::Motor& rightWheel,
                                 Balancer* balancer)
    : mGyroSensor(gyroSensor),
      mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mBalancer(balancer),
      mForward(LOW),
      mTurn(LOW) {

}

/**
 * バランス走行する
 */
void Engine::run() {
    int16_t angle = mGyroSensor.getAnglerVelocity();  // ジャイロセンサ値
    int rightWheelEnc = mRightWheel.getCount();       // 右モータ回転角度
    int leftWheelEnc  = mLeftWheel.getCount();        // 左モータ回転角度

    mBalancer->setCommand(mForward, mTurn);

    int battery = ev3_battery_voltage_mV();
    mBalancer->update(angle, rightWheelEnc, leftWheelEnc, battery);

    // 左右モータに回転を指示する
    mLeftWheel.setPWM(mBalancer->getPwmLeft());
    mRightWheel.setPWM(mBalancer->getPwmRight());
}

/**
 * バランス走行に必要なものをリセットする
 */
void Engine::init() {
    int offset = mGyroSensor.getAnglerVelocity();  // ジャイロセンサ値

    // モータエンコーダをリセットする
    mLeftWheel.reset();
    mRightWheel.reset();

    // 倒立振子制御初期化
    mBalancer->init(offset);
}

/**
 * PWM値を設定する
 * @param forward 前進値
 * @param turn    旋回値
 */
void Engine::setCommand(int forward, int turn) {
    mForward = forward;
    mTurn    = turn;
}
