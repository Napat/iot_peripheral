

#ifndef __TEMP_DS1621_H__
#define __TEMP_DS1621_H__

#include <Wire.h>

#define DS1621_BASEADDR   (0x48)

enum ds1621_cmd{
	//cmd: temp control
	DS1621_READ_TEMP 		= 0xAA,		//read dat length = 1byte
	DS1621_READ_COUNTER		= 0xA8,		//read dat length = 1byte
	DS1621_READ_SLOPECOUNTER = 0xA9,	//read dat length = 1byte
	DS1621_START_TEMPING 	= 0xEE,		//no data
	DS6121_STOP_TEMPING		= 0x22,		//no data

	//cmd: termostate mode
	DS1621_ACCESS_TH		= 0xA1,		//write dat length = 1byte
	DS1621_ACCESS_TL		= 0xA2,		//write dat length = 1byte
	DS1621_CONFIG_REGISTER	= 0xAC,		//write dat length = 1byte

} ds1621_cmd_t;

#endif /* __TEMP_DS1621_H__ */
