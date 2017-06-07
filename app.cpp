/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "app.h"
#include "Driver.h"
#include "Comm.h"
//#include "LineTracer.h"

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void *__dso_handle=0;

// using宣言
using ev3api::ColorSensor;
using ev3api::GyroSensor;
using ev3api::Motor;

// Device objects
// オブジェクトを静的に確保する
ColorSensor gColorSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_4);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);

// オブジェクトの定義
// static LineMonitor     *gLineMonitor;
// static Balancer        *gBalancer;
// static BalancingWalker *gBalancingWalker;
// static LineTracer      *gLineTracer;

// Define objects
// app
static Driver* gDriver;
// static Comm *gComm;    TO-DO
// units
static Balancer* gBalancer;
static Engine* gEngine;
static LineObserver* gLineObserver;
// static PID *gPID;         TO-DO
static Steerer* gSteerer;


/**
 * EV3システム生成
 */
static void user_system_create() {
    // オブジェクトの作成
    // create links    ............why?
    // to be available to delete them in user_system_destroy()?
    // UNITS instance
    gBalancer = new Balancer();
    gEngine = new Engine(gGyroSensor, gLeftWheel, gRightWheel, gBalancer);
    gLineObserver = new LineObserver(gColorSensor);
    gSteerer = new Steerer(gLineObserver);
    // APP instane
    gDriver = new Driver(gLineObserver, gEngine, gSteerer);
    // gComm = new   TO-DO
    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.reset();
    gRightWheel.reset();

    // APP
    delete gDriver;
    // delete gComm     TO-DO
    // UNITS
    delete gSteerer;
    delete gLineObserver;
    delete gEngine;
    delete gBalancer;
}

/**
 * トレース実行タイミング
 */
 // caller 4ms version
void invoker_four_ms(intptr_t exinf) {
    act_tsk(DRIVER_TASK);
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    // 周期ハンドラ開始
    ev3_sta_cyc(INVOKER_FOUR_MS);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(INVOKER_FOUR_MS);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void driver_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        gDriver->run();  // 倒立走行
    }

    ext_tsk();
}
