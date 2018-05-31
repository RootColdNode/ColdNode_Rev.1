/**
 * Copyright (c) 2011 panStamp <contact@panstamp.com>
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
 */

#ifndef _CC430RADIO_H
#define _CC430RADIO_H

#ifdef __cplusplus
 extern "C" {
#endif
#include "rf1a.h"
#ifdef __cplusplus
}
#endif

#include "wiring.h"
#include "ccpacket.h"

/**
 * Carrier frequencies
 */
enum CFREQ
{
  CFREQ_868 = 0,
  CFREQ_915,
  CFREQ_918,
  CFREQ_433,
  CFREQ_LAST
};

/**
 * RF STATES
 */
enum RFSTATE
{
  RFSTATE_IDLE = 0,
  RFSTATE_RXON,
  RFSTATE_RXOFF,
  RFSTATE_PWRDWN
};

/**
 * Working modes
 */
#define MODE_LOW_SPEED  0x01  // RF speed = 4800 bps (default is 38 Kbps)

/**
 * Frequency channels
 */
#define NUMBER_OF_FCHANNELS      10

/**
 * CC430 configuration registers
 */
 
/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 *  RF device: CC430
 *
 ***************************************************************/


#define CCDEF_FSK_IOCFG2        0x29
#define CCDEF_FSK_IOCFG1        0x2E
#define CCDEF_FSK_IOCFG0        0x06
#define CCDEF_FSK_FIFOTHR       0x07
#define CCDEF_FSK_SYNC1         0xD3
#define CCDEF_FSK_SYNC0         0x91
#define CCDEF_FSK_PKTLEN        0xFF
#define CCDEF_FSK_PKTCTRL1      0x06
#define CCDEF_FSK_PKTCTRL0      0x05
#define CCDEF_FSK_ADDR          0x00
#define CCDEF_FSK_CHANNR        0x00
#define CCDEF_FSK_FSCTRL1       0x0C
#define CCDEF_FSK_FSCTRL0       0x00
#define CCDEF_FSK_FREQ2         0x21
#define CCDEF_FSK_FREQ1         0x62
#define CCDEF_FSK_FREQ0         0x76
#define CCDEF_FSK_MDMCFG4       0x3D
#define CCDEF_FSK_MDMCFG3       0x3B
#define CCDEF_FSK_MDMCFG2       0x83
#define CCDEF_FSK_MDMCFG1       0x22
#define CCDEF_FSK_MDMCFG0       0xF8
#define CCDEF_FSK_DEVIATN       0x57
#define CCDEF_FSK_MCSM2         0x07
#define CCDEF_FSK_MCSM1         0x30
#define CCDEF_FSK_MCSM0         0x10
#define CCDEF_FSK_FOCCFG        0x1D
#define CCDEF_FSK_BSCFG         0x1C
#define CCDEF_FSK_AGCCTRL2      0xC7
#define CCDEF_FSK_AGCCTRL1      0x00
#define CCDEF_FSK_AGCCTRL0      0xB0
#define CCDEF_FSK_WOREVT1       0x80
#define CCDEF_FSK_WOREVT0       0x00
#define CCDEF_FSK_WORCTRL       0xFB
#define CCDEF_FSK_FREND1        0xB6
#define CCDEF_FSK_FREND0        0x10
#define CCDEF_FSK_FSCAL3        0xEA
#define CCDEF_FSK_FSCAL2        0x2A
#define CCDEF_FSK_FSCAL1        0x00
#define CCDEF_FSK_FSCAL0        0x1F
#define CCDEF_FSK_FSTEST        0x59
#define CCDEF_FSK_PTEST         0x7F
#define CCDEF_FSK_AGCTEST       0x3F
#define CCDEF_FSK_TEST2         0x88
#define CCDEF_FSK_TEST1         0x31
#define CCDEF_FSK_TEST0         0x09
#define CCDEF_FSK_PARTNUM       0x00
#define CCDEF_FSK_VERSION       0x06
#define CCDEF_FSK_FREQEST       0x00
#define CCDEF_FSK_LQI           0x00
#define CCDEF_FSK_RSSI          0x00
#define CCDEF_FSK_MARCSTATE     0x00
#define CCDEF_FSK_WORTIME1      0x00
#define CCDEF_FSK_WORTIME0      0x00
#define CCDEF_FSK_PKTSTATUS     0x00
#define CCDEF_FSK_VCO_VC_DAC    0x00
#define CCDEF_FSK_TXBYTES       0x00
#define CCDEF_FSK_RXBYTES       0x00
#define CCDEF_FSK_RF1AIFCTL0    0x00
#define CCDEF_FSK_RF1AIFCTL1    0x00
#define CCDEF_FSK_RF1AIFCTL2    0x00
#define CCDEF_FSK_RF1AIFERR     0x00
#define CCDEF_FSK_RF1AIFERRV    0x00
#define CCDEF_FSK_RF1AIFIV      0x00
#define CCDEF_FSK_RF1AINSTRW    0x00
#define CCDEF_FSK_RF1AINSTR1W   0x00
#define CCDEF_FSK_RF1AINSTR2W   0x00
#define CCDEF_FSK_RF1ADINW      0x00
#define CCDEF_FSK_RF1ASTAT0W    0x00
#define CCDEF_FSK_RF1ASTAT1W    0x00
#define CCDEF_FSK_RF1ASTAT2W    0x00
#define CCDEF_FSK_RF1ADOUT0W    0x00
#define CCDEF_FSK_RF1ADOUT1W    0x00
#define CCDEF_FSK_RF1ADOUT2W    0x00
#define CCDEF_FSK_RF1AIN        0x00
#define CCDEF_FSK_RF1AIFG       0x00
#define CCDEF_FSK_RF1AIES       0x00
#define CCDEF_FSK_RF1AIE        0x00
#define CCDEF_FSK_RF1AIV        0x00
#define CCDEF_FSK_RF1ARXFIFO    0x00
#define CCDEF_FSK_RF1ATXFIFO    0x00

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
#define PA_TABLE {0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00}
/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 *  RF device: CC430
 *
 ***************************************************************/


#define CCDEF_OOK_IOCFG2        0x0B
#define CCDEF_OOK_IOCFG1        0x2E
#define CCDEF_OOK_IOCFG0        0x2D
#define CCDEF_OOK_FIFOTHR       0x07
#define CCDEF_OOK_SYNC1         0xAA
#define CCDEF_OOK_SYNC0         0xAA
#define CCDEF_OOK_PKTLEN        0xFF
#define CCDEF_OOK_PKTCTRL1      0x04
#define CCDEF_OOK_PKTCTRL0      0x00
#define CCDEF_OOK_ADDR          0x00
#define CCDEF_OOK_CHANNR        0x00
#define CCDEF_OOK_FSCTRL1       0x0C
#define CCDEF_OOK_FSCTRL0       0x00
#define CCDEF_OOK_FREQ2         0x21
#define CCDEF_OOK_FREQ1         0x62
#define CCDEF_OOK_FREQ0         0x76
#define CCDEF_OOK_MDMCFG4       0xFA
#define CCDEF_OOK_MDMCFG3       0x57 //0x6B= 36 Kbaud; 0x52=33.5 Kbaud; 0x57=37 Kbaud
#define CCDEF_OOK_MDMCFG2       0x30
#define CCDEF_OOK_MDMCFG1       0x01
#define CCDEF_OOK_MDMCFG0       0xF8
#define CCDEF_OOK_DEVIATN       0x62
#define CCDEF_OOK_MCSM2         0x07
#define CCDEF_OOK_MCSM1         0x00
#define CCDEF_OOK_MCSM0         0x10
#define CCDEF_OOK_FOCCFG        0x1D
#define CCDEF_OOK_BSCFG         0x1C
#define CCDEF_OOK_AGCCTRL2      0x04
#define CCDEF_OOK_AGCCTRL1      0x00
#define CCDEF_OOK_AGCCTRL0      0x92
#define CCDEF_OOK_WOREVT1       0x80
#define CCDEF_OOK_WOREVT0       0x00
#define CCDEF_OOK_WORCTRL       0xFB
#define CCDEF_OOK_FREND1        0xB6
#define CCDEF_OOK_FREND0        0x11
#define CCDEF_OOK_FSCAL3        0xE9
#define CCDEF_OOK_FSCAL2        0x2A
#define CCDEF_OOK_FSCAL1        0x00
#define CCDEF_OOK_FSCAL0        0x1F
#define CCDEF_OOK_FSTEST        0x59
#define CCDEF_OOK_PTEST         0x7F
#define CCDEF_OOK_AGCTEST       0x3F
#define CCDEF_OOK_TEST2         0x81
#define CCDEF_OOK_TEST1         0x33
#define CCDEF_OOK_TEST0         0x09



/**
 * Macros
 */
// RADIO
#define CC430_STATE_TX                   (0x20)
#define CC430_STATE_IDLE                 (0x00)
#define CC430_STATE_TX_UNDERFLOW         (0x70)
#define CC430_STATE_MASK                 (0x70)
#define CC430_FIFO_BYTES_AVAILABLE_MASK  (0x0F)
#define CC430_STATE_RX                   (0x10)
#define CC430_STATE_RX_OVERFLOW          (0x60)

#define MIN(n,m) (((n) < (m)) ? (n) : (m))

#define MRFI_CLEAR_GDO0_INT_FLAG()                  (RF1AIFG &= ~BIT0)
#define MRFI_GDO0_INT_FLAG_IS_SET()                 (RF1AIFG & BIT0)
 
#define MRFI_ENABLE_SYNC_PIN_INT()                  (RF1AIE |= BIT9)
#define MRFI_DISABLE_SYNC_PIN_INT()                 (RF1AIE &= ~BIT9)
#define MRFI_CLEAR_SYNC_PIN_INT_FLAG()              (RF1AIFG &= ~BIT9)
#define MRFI_SYNC_PIN_INT_FLAG_IS_SET()             (RF1AIFG & BIT9)
#define MRFI_STROBE_IDLE_AND_WAIT()              \
{                                                \
  Strobe(RF_SIDLE);                              \
  /* Wait for XOSC to be stable and radio in IDLE state */ \
  while (Strobe(RF_SNOP) & 0xF0) ;               \
}
#define MRFI_SYNC_PIN_INT_IS_ENABLED()     (RF1AIE & BIT9)

// Disable address check
#define disableAddressCheck()     enableAddressCheck(false)
// Disable CCA
#define disableCCA()              enableCCA(false)
// PATABLE values
#define PA_LowPower               0x60
#define PA_LongDistance           0xC0
// Enable Rx state
#define setRxState                setRxOnState

/**
 * Class: CC430RADIO
 * 
 * Description:
 * CC430RADIO interface
 */
class CC430RADIO
{
  private:
    /*
     * RF state
     */
    uint8_t rfState;

  public:
    /**
     * Carrier frequency
     */
    uint8_t carrierFreq;
    
    /**
     * Working mode (speed, ...)
     */
    uint8_t workMode;

    /**
     * Frequency channel
     */
    uint8_t channel;

    /**
     * Synchronization word
     */
    uint8_t syncWord[2];

    /**
     * Device address
     */
    uint8_t devAddress;

    /**
     * CC430RADIO
     * 
     * Class constructor
     */
    CC430RADIO(void);

    /**
     * setCCregs
     * 
     * Configure CC1101 registers
     */
    void setFSKCCregs(void);
    void setOOKCCregs(void);
    /**
     * reset
     * 
     * Reset CC1101
     */
    void reset(void);

    /**
     * init
     * 
     * Initialize CC1101
     *
     * @param freq Carrier frequency
     * @param mode Working mode (speed, ...)
     */
    void init(uint8_t freq=CFREQ_868, uint8_t mode=0);
    
    /**
     * setRxOnState
     * 
     * Put radio in Rx mode
     */
    void setRxOnState(void);

    /**
     * setRxOffState
     * 
     * Disable Rx mode
     */
    void setRxOffState(void);

    /**
     * setSyncWord
     * 
     * Set synchronization word
     * 
     * @param syncH	Synchronization word - High byte
     * @param syncL	Synchronization word - Low byte
     */
    void setSyncWord(uint8_t syncH, uint8_t syncL);

    /**
     * setSyncWord (overriding method)
     * 
     * Set synchronization word
     * 
     * @param syncH	Synchronization word - pointer to 2-byte array
     */
    void setSyncWord(uint8_t *sync);

    /**
     * setDevAddress
     * 
     * Set device address
     * 
     * @param addr Device address
     */
    void setDevAddress(uint8_t addr);

    /**
     * setCarrierFreq
     * 
     * Set carrier frequency
     * 
     * @param freq New carrier frequency
     */
    void setCarrierFreq(uint8_t freq);
    
    /**
     * setChannel
     * 
     * Set frequency channel
     * 
     * 'chnl'	Frequency channel
     */
    void setChannel(uint8_t chnl);

    /**
     * setPowerDownState
     * 
     * Put CC1101 into power-down state
     */
    void setPowerDownState();

    /**
     * wakeUp
     * 
     * Wake-up core
     */
    void wakeUp();

    /**
     * WuRx sendData
     * 
     * Send data packet via RF
     * 
     * @param packet Packet to be transmitted. First byte is the destination address
     *
     *  @return True if the transmission succeeds. False otherwise
     */
    bool wuRxSendData(CCPACKET packet);

    /**
     * sendData
     * 
     * Send data packet via RF
     * 
     * @param packet Packet to be transmitted. First byte is the destination address
     *
     *  @return True if the transmission succeeds. False otherwise
     */
    bool sendData(CCPACKET packet);

    /**
     * receiveData
     * 
     * Read data packet from RX FIFO
     * 
     * @return Amount of bytes received
     */
    uint8_t receiveData(CCPACKET *packet);

    /**
     * enableAddressCheck
     *
     * Turn on/ff address check
     *
     * @param enable True if address check has to be enabled
     */
    void enableAddressCheck(bool enable=true);

    /**
     * enableCCA
     *
     * Turn on/ff CCA mechanism
     *
     * @param enable True if address check has to be enabled
     */
    void enableCCA(bool enable=true);
    
    /**
     * setWorState
     *
     * Enter Wake-On-Radio state
     * 
     * @param millis Sleeping interval in milliseconds
     *   This interval has to be greater than 12 ms and not greater than 2000 ms
     */
    void setWorState(uint16_t millis);
    
    /**
     * setTxPowerAmp
     * 
     * Set PATABLE value
     * 
     * @param paLevel amplification value
     */
    inline void setTxPowerAmp(uint8_t paLevel, bool modulation) //modulation==1 for OOK and 0 for FSK
    {
	uint8_t  paTable[] = {0x00, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
      if(modulation){
		paTable[0]=paLevel;
		WriteBurstReg(PATABLE, paTable, sizeof(paTable));
	  }
	  else
		WritePATable(paLevel);
    }
};

#endif
