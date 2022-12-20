/*
 * global.c
 *
 *  Created on: Dec 20, 2022
 *      Author: HP
 */

#include "global.h"

/* Các mode của hệ thống:
 *  INIT: khởi tạo
 *  MODE_1: chạy đèn giao thông bình thường
 *  MODE_2, MODE_3, MODE_4: config duration của các đèn */
int currentMode = 0;
// Duration: 5s red, 2s amber, 3s green
int trafficDuration[3] = {5, 2, 3};

/* Các state của traffic light: init, red, amber, green
 * [0: 1st traffic light, 1: 2nd traffic light] */
int trafficState[2] = {0, 0};

// current time of traffic light, display on led 7-seg
int trafficCurrTime[2] = {0, 0};
//buffer for 7seg led, 1st array for time, 2nd array for mode
int trafficTimeBuffer[2][2] = {{0, 5}, {0, 3}};

