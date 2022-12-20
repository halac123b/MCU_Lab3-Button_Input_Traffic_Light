/*
 * software_timer.c
 *
 *  Created on: Dec 20, 2022
 *      Author: HP
 */

#include "global.h"
#include "software_timer.h"

// Array gồm flag khi các counter đã đếm xong
int flagTimer[MAX_TIMER] = {0};
// Array gồm các biến counter
int counterTimer[MAX_TIMER] = {0};

void setTimer(int index, int duration){
	counterTimer[index] = duration / CYCLE;
	flagTimer[index] = 0;
}

int getCurrTimer(int index){
	return counterTimer[index] * CYCLE;
}

char isTimerFlagOn(int index){
	if (flagTimer[index] == 1){
		flagTimer[index] == 0;
		return 1;
	}
	return 0;
}


void timerRun(){
	for (int i = 0; i < MAX_TIMER; i++){
		if (counterTimer[i] > 0){
			counterTimer[i]--;
			if (counterTimer[i] <= 0){
				flagTimer[i] = 1;
			}
		}
	}
}


