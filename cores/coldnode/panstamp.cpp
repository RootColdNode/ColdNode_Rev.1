/**
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 06/03/2013
   Author: Sadok Bdiri
   Revision date: 07/06/2018
 */

#include "panstamp.h"
/**
 * PANSTAMP
 *
 * Class constructor
 */
PANSTAMP::PANSTAMP(void)
{
  ccPacketReceived = NULL;
}

/**
 * init
 * 
 * Initialize panStamp board
 * 
 * @param freq Carrier frequency
 * @param mode Working mode (speed, ...)
 */
void PANSTAMP::init(uint8_t freq, uint8_t mode) 
{
  // Disable wireless bootloader
  enableWirelessBoot(false);
  
  // Initialize MCU core
  core.init();
  // Initialize onboard LED pin
  INIT_ONBOARD_LED();

  // Initialize internal ACC power pin
  #if defined(__NRG_VERSION_1_0__) || defined(__NRG_VERSION_1_1__)
  INIT_ACC_POWER();
  #endif
   
  // Setup radio interface
  radio.init(freq, mode);

  delayMicroseconds(50);
}

/**
 * rxOn
 *
 * Enable RF reception
 */
void PANSTAMP::rxOn(void)
{
  MRFI_ENABLE_SYNC_PIN_INT();
}

/**
 * rxOff
 *
 * Disable RF reception
 */
void PANSTAMP::rxOff(void)
{
  MRFI_DISABLE_SYNC_PIN_INT();
}

/**
 * sleep
 *
 * Enter LPM4
 */
void PANSTAMP::sleep(void)
{
  // Power down radio
  radio.setPowerDownState();
  
  // If RTC calendar is running
  if (rtc.calendarIsRunning)
    core.setLowPowerMode();        // Enter LPM3
  else
    core.setLowPowerMode(true);    // Enter LPM4
  
  // Wake-up
  wakeUp();
}

/**
 * sleepSec
 *
 * put the MCU in sleep mode
 *
 * @param time Sleep time in seconds
 * @param source Source of interruption (RTCSRC_VLO or RTCSRC_XT1)
 */
void PANSTAMP::sleepSec(uint16_t time, RTCSRC source)
{ 
  if (time == 0)
    return;
   
  // Power down radio
  radio.setPowerDownState();

  core.delayClockCycles(0xFFFF);

  // Sleep
  rtc.sleep(time, source);
   
  // Wake-up radio
  radio.setRxState();
}

/**
 * reset
 * 
 * Reset panStamp
 */
void PANSTAMP::reset(void)
{
  WDTCTL = 0;
  while (1) {}
}
    
/**
 * Pre-instantiate PANSTAMP object
 */
PANSTAMP panstamp;

