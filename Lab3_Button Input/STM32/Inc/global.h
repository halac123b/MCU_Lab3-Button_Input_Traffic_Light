/*
 * global.h
 *
 *  Created on: Dec 18, 2022
 *      Author: HP
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "input_reading.h"

extern int flagTimer1;
extern int currentMode;

extern int trafficDuration[3];
extern int trafficState[2];
extern int trafficCurrTime[2];
extern int trafficTimeBuffer[2][2];

#endif /* INC_GLOBAL_H_ */
