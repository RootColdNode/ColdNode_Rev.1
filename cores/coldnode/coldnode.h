/**
 * Copyright (c) 2018 ColdNode <contact@coldnode.com>
 * 
 * This file is part of the ColdNode project.
 * 
 * ColdNode is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * ColdNode is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with ColdNode; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Sadok Bdiri
 * Creation date: 07/06/2018
 */
#ifndef _COLDNODE_H
#define _COLDNODE_H
#include "panstamp.h"
#include "WuRx.h"
class COLDNODE: public PANSTAMP
{	

public:
	WuRx wurx;
	COLDNODE (void);
	void init();
	void sendWuPacket(CCPACKET packet,CCPACKET fullPacket);
	void switchWuRxToAntenna();
	void switchCC430ToAntenna();
	void sleep();
	uint8_t LithiumBatteryStatus (); //Lithium Batteries
		
};
extern COLDNODE coldnode;
#endif