/*
 * fsm_mode_traffic.c
 *
 *  Created on: Dec 20, 2022
 *      Author: HP
 */

#include "fsm_mode_traffic.h"
#include "main.h"
#include "global.h"
#include "input_reading.h"
#include "display_led.h"
#include "config_duration.h"

void fsmModeTraffic(){
	switch(currentMode){
		// Initial state
		case INIT:
			clearAllLed();
			currentMode = MODE_1;
			trafficState[TRAFFIC_1ST] = DISPLAY_INIT;
			trafficState[TRAFFIC_2ND] = DISPLAY_INIT;
			setTimer(TIMER_7SEG, 250);
			break;

		// Normal state
		case MODE_1:
			displayTrafficLed(TRAFFIC_1ST);
			displayTrafficLed(TRAFFIC_2ND);
			displayTime7Seg();

			// when pressing button 1, change to next mode
			if (isBtnPressed(BTN_1)){
				currentMode = MODE_2;
				changeModeBuffer(MODE_2);
				setTimer(TIMER_LED, 500);
				clearAllLed();
			}
			break;

		// Set led red duration
		case MODE_2:
			displayBlinkyLed(LED_RED);
			displayTime7Seg();

			// when pressing button 1, change to next mode
			if (isBtnPressed(BTN_1)){
				currentMode = MODE_3;
				changeModeBuffer(MODE_3);
				setTimer(TIMER_LED, 500);
				clearAllLed();
			}
			//when pressing button 2, increase duration of led red
			if (isBtnPressed(BTN_2))
				increaseTempLedDuration();
			//when pressing button 3, apply new duration for led red
			if (isBtnPressed(BTN_3))
				updateLedDuration(LED_RED);
			break;

		// Set led amber duration
		case MODE_3:
			displayBlinkyLed(LED_AMBER);
			displayTime7Seg();
			//when pressing button 1, change to next mode
			if (isBtnPressed(BTN_1)){
				currentMode = MODE_4;
				changeModeBuffer(MODE_4);
				setTimer(TIMER_LED, 500);
				clearAllLed();
			}
			//when pressing button 2, increase duration of led amber
			if (isBtnPressed(BTN_2))
				increaseTempLedDuration();
			//when pressing button 3, apply new duration for led amber
			if (isBtnPressed(BTN_3))
				updateLedDuration(LED_AMBER);
			break;

		// Set led green duration
		case MODE_4:
			displayBlinkyLed(LED_GREEN);
			displayTime7Seg();
			//when pressing button 1, change to next mode
			if (isBtnPressed(BTN_1)){
				currentMode = MODE_1;
				trafficState[TRAFFIC_1ST] = DISPLAY_INIT;
				trafficState[TRAFFIC_2ND] = DISPLAY_INIT;
				clearAllLed();
			}
			//when pressing button 2, increase duration of led amber
			if (isBtnPressed(BTN_2))
				increaseTempLedDuration();
			//when pressing button 3, apply new duration for led amber
			if (isBtnPressed(BTN_3))
				updateLedDuration(LED_GREEN);
			break;

		default:
			break;
	}
}
