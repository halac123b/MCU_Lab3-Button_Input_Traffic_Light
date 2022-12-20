/*
 * config_duration.c
 *
 *  Created on: Dec 20, 2022
 *      Author: HP
 */

#include "config_duration.h"
#include "global.h"
#include "fsm_mode_traffic.h"
#include "main.h"
#include "display_led.h"

int currMode = 0;
int tempDuration = 0;

// Reset lại thời gian trên led-7  khi đổi mode hoặc config lại các gt
void modifyTrafficBuffer(int mode, int duration){
	trafficTimeBuffer[0][0] = duration / 10;
	trafficTimeBuffer[0][0] = duration % 10;
	trafficTimeBuffer[1][0] = mode / 10;
	trafficTimeBuffer[1][1] = mode % 10;
}

void changeModeBuffer(int mode){
	switch(mode){
		case MODE_2:   //config led RED duration
			tempDuration = trafficDuration[LED_RED];
			currMode = 2;
			break;

		case MODE_3:   //config led AMBER duration
			tempDuration = trafficDuration[LED_AMBER];
			currMode = 3;
			break;

		case MODE_4:   //config led GREEN duration
			tempDuration = trafficDuration[LED_GREEN];
			currMode = 4;
			break;

		default:
			break;
	}
	// làm mới lại thời gian của led 7-seg
	modifyTrafficBuffer(currMode, tempDuration);
}

void increaseTempLedDuration(){
	tempDuration = tempDuration + 1;
	if (tempDuration == 100)
		tempDuration = 1;
	modifyTrafficBuffer(currMode, tempDuration);
}

void updateLedDuration(int led){
	trafficDuration[led] = tempDuration;
	modifyTrafficBuffer(currMode, tempDuration);
}
