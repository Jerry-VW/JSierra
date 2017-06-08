/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2017/06/07
 *  Implementation of the Tasks
 *  Author: Jerry W
 *  like system's root "main frame", controls cycle tasks etc.
 *****************************************************************************/

#include "app.h"
#include "Driver.h"
#include "Comm.h"
//#include "LineTracer.h"

// To prevent destructor problems
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void* __dso_handle = 0;

// using declarations
using ev3api::ColorSensor;
using ev3api::GyroSensor;
using ev3api::Motor;

// Device static objects
ColorSensor gColorSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_4);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);

// Define objects
// app
static Driver* gDriver;
static Comm *gComm;    
// units
static Balancer* gBalancer;
static Engine* gEngine;
static LineObserver* gLineObserver;
// static PID *gPID;         TO-DO
static Steerer* gSteerer;


/**
 * EV3 system construction
 */
static void user_system_create() {
    // Instantiate objects
    // note the order
    // create links    ............why
    // to be available to delete them in user_system_destroy() easily(maybe)
    // UNITS instances
    gBalancer = new Balancer();
    gEngine = new Engine(gGyroSensor, gLeftWheel, gRightWheel, gBalancer);
    gLineObserver = new LineObserver(gColorSensor);
    gSteerer = new Steerer(gLineObserver);
    // PID                               TO-DO
    // APP instanes
    gDriver = new Driver(gLineObserver, gEngine, gSteerer);
    gComm = new Comm();
    
    // Initialization complete, LED go ORANGE
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3 system destruction
 */
static void user_system_destroy() {
    gLeftWheel.reset();
    gRightWheel.reset();

    // APP
    delete gDriver;
    delete gComm;
    // delete gComm     TO-DO
    // UNITS
    delete gSteerer;
    delete gLineObserver;
    delete gEngine;
    delete gBalancer;
}

/**
 * INVOKER 4ms version
 */
void invoker_4_ms(intptr_t exinf) {
    act_tsk(DRIVER_TASK);
}

/**
 * INVOKER 8ms version
 */
void invoker_8_ms(intptr_t exinf) {
    act_tsk(COMM_TASK);
}

/**
 * main task
 */
void main_task(intptr_t unused) {
    // initialize devices
    user_system_create();
    // start cycle
    ev3_sta_cyc(INVOKER_4_MS);
    ev3_sta_cyc(INVOKER_8_MS);
    // sleep this task itself
    slp_tsk();

    // stop cycle
    ev3_stp_cyc(INVOKER_4_MS);
    ev3_stp_cyc(INVOKER_8_MS);
    // Destruct system
    user_system_destroy();

    ext_tsk();
}

/**
 * Driver Task
 */
void driver_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        // Button pressed
        wup_tsk(MAIN_TASK);
    } else {
        gDriver->run();
        ext_tsk();
    }
}

/**
 * Comm Task
 */
void comm_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        // Button pressed
        char gb[10] = "Good Bye.";
        gComm -> sendMessage(gb);
        wup_tsk(MAIN_TASK);
    } else {
        gComm->run();
        ext_tsk();
    }
}
