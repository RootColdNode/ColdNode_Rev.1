/**
 * Copyright (c) 2014 ColdNode <bdiri.sadok@gmail.com>
 * 
 * This file is part of the ColdNode project. Arduino Libraries are not included.
 * 
 * Author: Sadok Bdiri
 * Creation date: 15.03.2015
 * Revision date: 20.04.2016
 * Version 1.0
 */
 #ifndef _WuRx_H
#define _WuRx_H

#include "cc430radio.h"

class WuRx
{

private:

void WrtietoAS3933Register(char addr, char data);

//void CalibrateAS3933_RC(char Count, uint16_t Configuration[]);
void defaultPreset(void);
unsigned int SDI,CS,SCL;
public:


 //AS3933 SPI pins
WuRx(unsigned int MCU_P0,unsigned int MCU_P1, unsigned int MCU_P2){CS=MCU_P0;SCL=MCU_P1;SDI=MCU_P2;};
void ConfigureAS3933(unsigned int Count, uint16_t Configuration[]);
void InitAS3933(void);
void clearWake(void);
void setFullPacket(CCPACKET* txpt);
void setDestWakeUpPacketAddress(CCPACKET* txpt ,uint16_t address);
void setDestWakeUpPacketAddress_Man(CCPACKET* txpt ,uint16_t address);
void setSourceWakeUpPacketAddress(uint16_t address);
void powerOn(void){ digitalWrite(WuRxVCC, HIGH);};
};
#endif