/*
 * software_timer.h
 *
 *  Created on: Dec 18, 2022
 *      Author: HP
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX_TIMER   4
#define CYCLE 	    10	  // Cycle của interrupt, 10ms
#define TIME_UNIT   1000  // Đơn vị tg, 1000ms = 1s

// List các counter
#define TRAFFIC_1ST 0
#define TRAFFIC_2ND 1
#define TIMER_7SEG  2  // Counter switch qua lại giữa các led-7 (250ms)
#define TIMER_LED   3  // Counter khi blink các đèn giao thông ở config mode (500ms)

void setTimer(int index, int duration);	 // Set duration cho timer in (ms)
int getCurrTimer(int index);	// Get current time of a counter
char isTimerFlagOn(int index);  // Check xem flag của counter đó đã kích hoạt chưa
void timerRun();  // Run time

#endif /* INC_SOFTWARE_TIMER_H_ */
