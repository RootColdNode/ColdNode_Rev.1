/*The MIT License(MIT)

Copyright (c) 2018 ColdNode <contact@coldnode.com>
Author: Sadok Bdiri
Creation date: 07.06.2018
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


*/
#include "coldnode.h"
COLDNODE coldnode;

//Class constructor
COLDNODE::COLDNODE(void):wurx(AS39xx_CS,AS39xx_SCL,AS39xx_SDI)
{
  ccPacketReceived = NULL;
}

//Initialization function
void COLDNODE::init(){
  pinMode(WuRxVCC, OUTPUT);//WuRx
  pinMode(SiSensor_VCC, OUTPUT);//SI7021: Humidity and Temperature Sensor
  pinMode(RFSwitch, OUTPUT);//ADG
  pinMode(IntP, INPUT);
	
}

//Transmit wake-up packet
void COLDNODE::sendWuPacket(CCPACKET packet, CCPACKET fullPacket){
  radio.setOOKCCregs();
  wurx.setFullPacket(&fullPacket);
  for(int i=0; i<2; i++){
    radio.wuRxSendData(fullPacket);
    radio.wuRxSendData(packet);
  } 
  radio.setFSKCCregs();
}

// Get status of a lithium battery based on its voltage level
 uint8_t COLDNODE::LithiumBatteryStatus(){
   float volt = panstamp.getVcc();
   float level = map(volt, 2200, 3000, 0, 100);
   if (level >90) return 1;
   return 0;
  }
  
 // Put coldnode to sleep and activate the WuRx
void COLDNODE::sleep(){

  digitalWrite(Green_LED, LOW);
  digitalWrite(Blue_LED, LOW);
  digitalWrite(Red_LED, LOW);
  switchWuRxToAntenna();
  panstamp.sleep();
 }
 
 // Redirect the antenna to the CC430 chip by acting on the RF switch
  void COLDNODE::switchCC430ToAntenna(){
  digitalWrite(RFSwitch, HIGH); //Switch to CC430
  radio.setFSKCCregs(); // Registry configuration required for the CC430 for FSK communication
  radio.enableAddressCheck();
  radio.setRxOnState();
}

 // Redirect the antenna to the WuRx chip by acting on the RF switch
void COLDNODE::switchWuRxToAntenna(){
  digitalWrite(RFSwitch, LOW);// Switch to WuRx
  int attempts=10;
  while(digitalRead(IntP) && attempts--){
    delay(10);
    wurx.clearWake();
   }
}

//Taken from panstamp.cpp, Author: Daniel Berunger, Daniel Berenguer. Modified to work with Coldnode
__attribute__((interrupt(CC1101_VECTOR)))
void radioISR(void)
{
  unsigned int coreIntSource = RF1AIV;            // Radio Core      interrupt register

  // Radio Core interrupt
  if(coreIntSource)
  {
    // Check for SYNC interrupt
    if(coreIntSource == RF1AIV_RFIFG9)
    {
      if(MRFI_SYNC_PIN_INT_IS_ENABLED())
      {
        static CCPACKET ccPacket;

        /*  clear the sync pin interrupt, run sync pin ISR */
        /*
         *  NOTE!  The following macro clears the interrupt flag but it also *must*
         *  reset the interrupt capture.  In other words, if a second interrupt
         *  occurs after the flag is cleared it must be processed, i.e. this interrupt
         *  exits then immediately starts again.  Most microcontrollers handle this
         *  naturally but it must be verified for every target.
         */

        MRFI_CLEAR_SYNC_PIN_INT_FLAG();
        MRFI_DISABLE_SYNC_PIN_INT();

        // Any packet waiting to be read?
        if (coldnode.radio.receiveData(&ccPacket) > 0)
        {
          // Is CRC OK?
          if (ccPacket.crc_ok)
          {            
            if (coldnode.ccPacketReceived != NULL)
              coldnode.ccPacketReceived(&ccPacket);
          }
        }

        MRFI_ENABLE_SYNC_PIN_INT();
      }
    }
    // Check for RF_RDY (Event1 WOR) interrupt
    else if(coreIntSource == RF1AIV_RFIFG14)
    {
      RF1AIE |= BIT9 + BIT1;
      RF1AIFG &= ~(BIT9 + BIT1);
      RF1AIES |= BIT9; // Falling edge of RFIFG9
      coldnode.radio.setRxState();
      __bic_SR_register_on_exit(LPM3_bits);
    }
  }
}