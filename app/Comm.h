/******************************************************************************
 *  Comm.h
 *  Created on: 2017/06/07
 *  Definition of the Class Comm
 *  Author: Jerry W
 *****************************************************************************/

#ifndef COMM_H_
#define COMM_H_

// modules' .h files
#include "ev3api.h"
#include <cstdio>
//#include "Driver.h"

#define BUFFER_SIZE 101

class Comm {
  public:
    Comm(FILE* bt);

    //void setDriver(Driver*);

    void run();
    void displayLCD(char*);
    void sendMessage(const char*);
    void ReceiveMessage();

    void setBrightnessTurn(double* dB, int* dT);
  
    const double& getCmdKp();
    const double& getCmdKi();
    const double& getCmdKd();

  private:
    void SerialTX();
    void SerialRX();
    void getPIDCommand();
    void sendBrightnessTurn();
    
    FILE* mBt;
    //Driver* mDriver;
    char cSBuffer[BUFFER_SIZE];
    char bufferCount;       //0 ~ BUFFER_SIZE - 1

    char cTemp;
    bool bPIDctrl;
    bool bUsrInputDone;

    double mBrightness;
    int mTurn;

    double cmdKp;
    double cmdKi;
    double cmdKd;
    double steererP;
    double steererI;
    double steererD;
};

#endif  // COMM_H_
