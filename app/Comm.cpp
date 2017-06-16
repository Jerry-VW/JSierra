/******************************************************************************
 *  Comm.cpp
 *  Created on: 2017/06/07
 *  Implementation of the Class Comm
 *  Author: Jerry W
 *  Called every 8ms
 *****************************************************************************/
#include "Comm.h"

//#include <syssvc/serial.h>

/**
 * Constructor
 * @param lineObserver
 * @param engine
 * @param steerer
 */
Comm::Comm(FILE* bt) : mBt(bt), cSBuffer("Transmitting B&T from buffer") {
          bufferCount = 0;
          bUsrInputDone = false;
}

// void Comm::setDriver(Driver* driver) {
//     mDriver = driver;
// }

/**
 * Driver's main logic, called every 4ms
 */
void Comm::run() {
    //receive data from serial to buffer every 4ms
    //getPIDCommand();
    sendBrightnessTurn();
    displayLCD(cSBuffer);
}

void Comm::sendMessage(const char* inMessage) {
    // edit cSerialBuffer
    SerialTX();
}

void Comm::displayLCD(char* inString) {
    ev3_lcd_set_font(EV3_FONT_MEDIUM);
    ev3_lcd_draw_string("JSierra Running...", 10, 30);
    ev3_lcd_set_font(EV3_FONT_SMALL);
    ev3_lcd_draw_string(inString, 10, 60);
}

/**
 * Send things to serial
 */
void Comm::SerialTX() {
    fputc(cTemp, mBt);
}

/**
 * Receive things from serial
 */
void Comm::SerialRX() {
    //cSBuffer = fgetc(mBt);
    //fgets(cSBuffer , BUFFER_SIZE + 1 , mBt);
    bUsrInputDone = false;

    while (!bUsrInputDone) {
        cTemp = fgetc(mBt);
        //echo back
        SerialTX();

        if (cTemp != '\n') {
            // no enter key detected
            // usr input is not over yet
            cSBuffer[(int)bufferCount] = cTemp;
        } else {
            bUsrInputDone = true;
        }
    }

    // snprintf(iBuffer, 6, "%d", ev3_gyro_sensor_get_rate(gyro_sensor));// get gyro rate and convert the int16 into string

    // // echo back and value display
    // fputs("Got >", bt);
    // fputc(c, bt); /* エコーバック */
    // fputs("\n\r Gyro: ", bt);
    // fputs(iBuffer, bt);
    // fputs("\n\r", bt);
}

void Comm::getPIDCommand() {
    SerialRX();
}
// called every 4ms by driver.run() to get newest values
void Comm::setBrightnessTurn(double* dB, int* dT) {
    mBrightness = *dB;
    mTurn = *dT;
}

void Comm::sendBrightnessTurn() {
    fprintf(mBt, "%d, %d\r\n", (int)mBrightness, mTurn);
    // fputc(mBrightness, mBt);
    // fputs(", ", mBt);
    // fputc(mTurn, mBt);
    // fputs("\n\r", mBt);
}
