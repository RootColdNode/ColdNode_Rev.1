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
/* TX power = 10 */
/* Address config = No address check */
/* Channel number = 0 */
/* Data format = Normal mode */
/* Packet length = 255 */
/* Base frequency = 867.999939 */
/* Manchester enable = false */
/* PA ramping = false */
/* Modulation format = ASK/OOK */
/* Whitening = false */
/* Channel spacing = 49.987793 */
/* Data rate = 0.50056 */
/* Device address = 0 */
/* Sync word qualifier mode = 30/32 sync word bits detected */
/* Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word */
/* Preamble count = 4 */
/* Carrier frequency = 867.999939 */
/* RX filter BW = 203.125000 */
/* Deviation = 5.157471 */
/* CRC enable = true */
/* CRC autoflush = false */
/* PA table */
/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 * O
 *  RF device: CC1101
 * OOK configuration for WuRx, valid for CC1101
 ***************************************************************/


class WuRx
{

private:

void WrtietoAS3933Register(char addr, char data);

//void CalibrateAS3933_RC(char Count, uint16_t Configuration[]);
void defaultPreset(void);
public:
unsigned int SDI,CS,SCL;
 //AS3933 SPI pins
WuRx(unsigned int MCU_P0,unsigned int MCU_P1, unsigned int MCU_P2){CS=MCU_P0;SCL=MCU_P1;SDI=MCU_P2;};
void ConfigureAS3933(unsigned int Count, uint16_t Configuration[]);
void InitAS3933(void);
void clearWake(void);
void setFullPacket(CCPACKET* txpt);
void setDestWakeUpPacketAddress(CCPACKET* txpt ,uint16_t address);
void setDestWakeUpPacketAddress_Man(CCPACKET* txpt ,uint16_t address);
void setSourceWakeUpPacketAddress(uint16_t address);
};
#endif