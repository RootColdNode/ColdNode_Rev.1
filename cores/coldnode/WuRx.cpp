/**
 * Copyright (c) 2014 ColdNode <bdiri.sadok@gmail.com>
 * 
 * This file is part of the ColdNode project.
 * 
 * Author: Sadok Bdiri
 * Creation date: 01.03.2015
 * Revision date: 28.04.2016
 * Version 1.0
 */

#include "WuRx.h"


uint16_t words[32];
/*
Class constructor
*/


void WuRx::WrtietoAS3933Register(char addr, char data){
  uint16_t val;
  val=(addr&0xFF)<<8 | (data&0xFF);
  ConfigureAS3933(1,&val);
}
void WuRx::ConfigureAS3933(unsigned int Count, uint16_t Configuration[]){
  unsigned int BitCounter;
  unsigned int WordCounter;
  typedef union myunion{ /* This union is used to easily access the most significant */
    /* bit of the configuration data */
    uint16_t Data;
    struct
    {
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t :1;
uint16_t MSB:1;
    }
    Str;
  }
  Uni;
  Uni MyUnion;
  uint16_t delayCount;
  delayCount=9;
  digitalWrite(CS,HIGH);
  delayMicroseconds(delayCount);
  for (WordCounter=0;WordCounter<Count;WordCounter++){
    MyUnion.Data= Configuration[WordCounter];
    /* Send address bits */
    for (BitCounter=0;BitCounter<8;BitCounter++){
      digitalWrite(SCL,HIGH);
     delayMicroseconds(delayCount);
      if (MyUnion.Str.MSB==0){
        digitalWrite(SDI,LOW);
        delayMicroseconds(delayCount);
      }
      else{
        digitalWrite(SDI,HIGH);	
        delayMicroseconds(delayCount);
      }
      digitalWrite(SCL,LOW);
     delayMicroseconds(delayCount);
      MyUnion.Data=MyUnion.Data<<1;
    }

    /* Send data bits */
    for (BitCounter=0;BitCounter<8;BitCounter++){
      digitalWrite(SCL,HIGH);
     delayMicroseconds(delayCount);
      if (MyUnion.Str.MSB==0){
        digitalWrite(SDI,LOW);
        delayMicroseconds(delayCount);
      } 
      else{
        digitalWrite(SDI,HIGH);
        delayMicroseconds(delayCount);
      }
      digitalWrite(SCL,LOW);
      delayMicroseconds(delayCount);
      MyUnion.Data=MyUnion.Data<<1;
    }


  } /* Finished with word */
  digitalWrite(CS,LOW);
//  delayMicroseconds(delayCount);
}
void WuRx::clearWake(void){
  words[1]=0x0;
  words[2]=0x0;
  words[3]=0x0;
  words[4]=0x0;
  words[0]=0xC000;
  ConfigureAS3933(6,words);//Clear Wake
}

void WuRx::defaultPreset(void){
  words[1]=0x0;
  words[2]=0x0;
  words[3]=0x0;
  words[4]=0x0;
  words[0]=0xC400;
  ConfigureAS3933(6,words);//Preset default AS3933
}
//Initialize The AS393x
void WuRx::InitAS3933(void){
  pinMode(CS, OUTPUT);//LED
  pinMode(SCL, OUTPUT);//LED
  pinMode(SDI, OUTPUT);//LED
  words[1]=0x0;
  words[2]=0x0;
  words[3]=0x0;
  words[4]=0x0;
  defaultPreset();
  clearWake();
  WrtietoAS3933Register(0x0,0xE2); //Enable 1st channel only/16-bit pattern correlation/ON-OFF mode A2 for 32-bit
  WrtietoAS3933Register(0x8,0xE0); //Set frequency band 20-40 KHz
  //WrtietoAS3933Register(0x10,0x80);// Display Clock Generator
  WrtietoAS3933Register(0x04,0xC0);// Set ON/Offmode 8 ms
  //WrtietoAS3933Register(0x1,0x21);//Disable Correlator
  WrtietoAS3933Register(0x1,0x2A);//Enable manchester
  //WrtietoAS3933Register(0x1,0x33); //Enable Antenna Damper
 // WrtietoAS3933Register(0x1,0x22); //Disable Crystal Oscillator( enable RC osc), Manchester disabled 2A for Manchester
  WrtietoAS3933Register(0x2,0x20); //+3db Amplifer Signal boost
  WrtietoAS3933Register(0x7,0x0D); //Altering bitrate
  WrtietoAS3933Register(0x3,0x20); //Symbol Rate
  delay(1);

  //WrtietoAS3933Register(0xD,0xFF);
  //call DigitIO.set();

  words[0]=0xC200;
  ConfigureAS3933(6,words);//calibrate AS3933

  }
void WuRx::setSourceWakeUpPacketAddress(uint16_t address){
 WrtietoAS3933Register(0x6,address/0x100);// Set 1st  pattern byte
  WrtietoAS3933Register(0x5,address%0x100); // Set 2nd  pattern byte
// WrtietoAS3933Register(0x6,0);//
  //WrtietoAS3933Register(0x5,0);//
}
void WuRx::setDestWakeUpPacketAddress(CCPACKET* txpt ,uint16_t address){
typedef union myunion{ 
    uint16_t Data;
    struct
    {
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t MSB :  1;
    }
    Str;
  }
  Uni;
  Uni MyUnion;
MyUnion.Data=address;
  (*txpt).length = 0x2A;  //1 byte carrier burst
  // Rest of the carrier burst (15 Bytes):

  (*txpt).data[0] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[1] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[2] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[3] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[4] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[5] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[6] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[7] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[8] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[9] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[10] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[11] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[12] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[13] = 0xAA;   // First data byte has to be the destination address
  (*txpt).data[14] = 0xAA;   // First data byte has to be the destination address
  //Sep But+Premable
  (*txpt).data[15] = 0xFF;
  (*txpt).data[16] = 0xAA;    
  (*txpt).data[17] = 0xFF;  
  (*txpt).data[18] = 0xAA;
  (*txpt).data[19] = 0xFF;
  (*txpt).data[20] = 0xAA;
  (*txpt).data[21] = 0xFF;
  (*txpt).data[22] = 0xFF;
    for(int BitCounter=0; BitCounter<16;BitCounter++){
      if (MyUnion.Str.MSB==0)
      (*txpt).data[23+BitCounter]=0xFF;
      else
      (*txpt).data[23+BitCounter]=0xAA;
      
    MyUnion.Data=MyUnion.Data<<1;
    }
    for(int i=39;i<(*txpt).length;i++){
    (*txpt).data[i]=0x00;
  }
}
void WuRx::setDestWakeUpPacketAddress_Man(CCPACKET* txpt ,uint16_t address){
typedef union myunion{ 
    uint16_t Data;
    struct
    {
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t :  1;
uint16_t MSB :  1;
    }
    Str;
  }
  Uni;
  Uni MyUnion;
MyUnion.Data=address;
  (*txpt).length = 0x70;  //1 byte carrier burst
  // Rest of the carrier burst (15 Bytes):

  for (int i=1; i<30;i++){
   (*txpt).data[i] = 0xAA; //carrier burst
  }
  //Sep Bit+Premable
  (*txpt).data[30] = 0xFF;
    (*txpt).data[31] = 0xFF;
  (*txpt).data[32] = 0xAA; 
  (*txpt).data[33] = 0xAA;    
  (*txpt).data[34] = 0xFF;  
   (*txpt).data[35] = 0xFF;
  (*txpt).data[36] = 0xAA;
   (*txpt).data[37] = 0xAA;
  (*txpt).data[38] = 0xFF;
   (*txpt).data[39] = 0xFF;
  (*txpt).data[40] = 0xAA;
  (*txpt).data[41] = 0xAA;
  (*txpt).data[42] = 0xFF;
  (*txpt).data[43] = 0xFF;
    for(int BitCounter=0; BitCounter<64;BitCounter++){
      if (MyUnion.Str.MSB==0){
	 (*txpt).data[44+BitCounter]=0xFF;//0
	 (*txpt).data[44+BitCounter+1]=0xFF;//0
	  (*txpt).data[44+BitCounter+2]=0xAA;//1
	  (*txpt).data[44+BitCounter+3]=0xAA;//1
	}
    else{

      (*txpt).data[44+BitCounter]=0xAA;//1
	   (*txpt).data[44+BitCounter+1]=0xAA;//1
	   (*txpt).data[44+BitCounter+2]=0xFF;//0
	   (*txpt).data[44+BitCounter+3]=0xFF;//0
	  
    } 
	BitCounter++;
	BitCounter++;
	BitCounter++;
    MyUnion.Data=MyUnion.Data<<1;
    }
	(*txpt).data[108]=0xFF;
	(*txpt).data[109]=0xFF;
	(*txpt).data[110]=0xFF;
}
void WuRx::setFullPacket(CCPACKET* txpt){
  (*txpt).length = 0x3F;  //1 byte carrier burst
  // Rest of the carrier burst (15 Bytes):
    for(int i=0;i<(*txpt).length;i++){
    (*txpt).data[i]=0x00;
  }
}