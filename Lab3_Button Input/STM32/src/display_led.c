/*
 * display_led.c
 *
 *  Created on: Dec 20, 2022
 *      Author: HP
 */

#include "display_led.h"
#include "main.h"
#include "global.h"

int led7SegIndex = 0;	// Index của led 7-seg hiện đang sáng

void clearAllLed(){
	HAL_GPIO_WritePin(GPIOA, LED_TEST_Pin, 1);
	HAL_GPIO_WritePin(GPIOA, LED_R1_Pin | LED_Y1_Pin | LED_G1_Pin
							| LED_R2_Pin | LED_Y2_Pin | LED_G2_Pin, 1);
	HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
							| SEG4_Pin | SEG5_Pin | SEG6_Pin, 1);
}

void displayTestLed(){
	HAL_GPIO_WritePin(GPIOA, LED_TEST_Pin, 0);
}

void clearTestLed(){
	HAL_GPIO_WritePin(GPIOA, LED_TEST_Pin, 1);
}

/*--------------------------blink led ở config mode--------------------------------*/
void blinkLed(int index){	// blink đèn giao thông
	switch(index){
		case LED_RED:
			HAL_GPIO_TogglePin(GPIOA, LED_R1_Pin | LED_R2_Pin);
			break;
		case LED_AMBER:
			HAL_GPIO_TogglePin(GPIOA, LED_Y1_Pin | LED_Y2_Pin);
			break;
		case LED_GREEN:
			HAL_GPIO_TogglePin(GPIOA, LED_G1_Pin | LED_G2_Pin);
			break;
		default:
			break;
	}
}

void displayBlinkyLed(int index){
	if (isTimerFlagOn(TIMER_LED)){
		setTimer(TIMER_LED, 500);
		blinkLed(index);
	}
}

/*--------------------------7-segment led--------------------------------*/
// Update lại buffer cho led 7-seg trong config mode
void updateTimeBuffer(int index, int time){
	trafficTimeBuffer[index][0] = time / 10;
	trafficTimeBuffer[index][1] = time % 10;
}

void display7Seg(int num){
	switch (num){
		case 0: // display 0 using leds: a, b, c, d, e, f
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
									SEG3_Pin | SEG4_Pin | SEG5_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG6_Pin, 1);
			break;
		case 1: // display 1 using leds: b, c
			HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG3_Pin | SEG4_Pin |
									SEG5_Pin | SEG6_Pin, 1);
			break;
		case 2: // display 2 using leds: a, b, d, e, g
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG3_Pin |
									SEG4_Pin | SEG6_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG2_Pin | SEG5_Pin, 1);
			break;
		case 3: // display 3 using leds: a, b, c, d, g
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
									SEG3_Pin | SEG6_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG4_Pin | SEG5_Pin, 1);
			break;
		case 4: // display 4 using leds: b, c, f, g
			HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin | SEG5_Pin |
									SEG6_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG3_Pin | SEG4_Pin, 1);
			break;
		case 5: // display 5 using leds: a, c, d, f, g
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin |
									SEG5_Pin | SEG6_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG4_Pin, 1);
			break;
		case 6: // display 6 using leds: a, c, d, e, f, g
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin |
									SEG4_Pin | SEG5_Pin | SEG6_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG1_Pin, 1);
			break;
		case 7: // diplay 7 using leds: a, b, c
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG3_Pin | SEG4_Pin | SEG5_Pin |
									SEG6_Pin, 1);
			break;
		case 8: // display 8 using leds: a, b, c, d, e, f, g
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
									SEG3_Pin | SEG4_Pin | SEG5_Pin |
									SEG6_Pin, 0);
			break;
		case 9: // display 9 using leds: a, b, c, d, f, g
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
									SEG3_Pin | SEG5_Pin | SEG6_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, SEG4_Pin, 1);
			break;
		default:
			break;
	}
}

void enable7Seg(int index){
	switch(index){
		case 0:
			HAL_GPIO_WritePin(GPIOB, EN0_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN3_Pin, 1);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOB, EN1_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, EN0_Pin | EN2_Pin | EN3_Pin, 1);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOB, EN2_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN0_Pin | EN3_Pin, 1);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOB, EN3_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN0_Pin, 1);
			break;
		default:
			break;
	}
	display7Seg(trafficTimeBuffer[index / 2][index % 2]);
}

/*--------------------------Traffic Light--------------------------------*/
void displayTrafficLed(int index){
	switch(trafficState[index]){
		case DISPLAY_INIT:   //initial state
			if (index == TRAFFIC_1ST){
				trafficState[index] = DISPLAY_RED;
				setTimer(index, trafficDuration[LED_RED] * TIME_UNIT);
			}
			else if (index == TRAFFIC_2ND){
				trafficState[index] = DISPLAY_GREEN;
				setTimer(index, trafficDuration[LED_GREEN] * TIME_UNIT);
			}
			break;

		case DISPLAY_RED:{	//display red led
			displayLight(index, LED_RED);
			if (isTimerFlagOn(index)){	// nếu hết tg đèn đỏ, chuyển sang đèn xanh
				trafficState[index] = DISPLAY_GREEN;
				setTimer(index, trafficDuration[LED_GREEN] * TIME_UNIT);
			}
			break;
		}

		case DISPLAY_GREEN: {	//display green led
			displayLight(index, LED_GREEN);
			if (isTimerFlagOn(index)){
				trafficState[index] = DISPLAY_AMBER;
				setTimer(index, trafficDuration[LED_AMBER] * TIME_UNIT);
			}
			break;
		}

		case DISPLAY_AMBER: 	//display amber led
			displayLight(index, LED_AMBER);
			if (isTimerFlagOn(index)){
				trafficState[index] = DISPLAY_RED;
				setTimer(index, trafficDuration[LED_RED] * TIME_UNIT);
			}
			break;
		default:
			break;
	}
	//get current counter (unit: sec), cộng thêm 1s so với counterTimer
	trafficCurrTime[index] = (getCurrTimer(index) + 1000) / TIME_UNIT;
	updateTimeBuffer(index, trafficCurrTime[index]);
}

void displayLight(int index, int type){
	switch(index){
		case TRAFFIC_1ST:	// Bật đèn của trụ số 1
			switch(type){
				case LED_RED:
					HAL_GPIO_WritePin(GPIOA, LED_R1_Pin, 0);
					HAL_GPIO_WritePin(GPIOA, LED_G1_Pin | LED_Y1_Pin, 1);
					break;
				case LED_GREEN:
					HAL_GPIO_WritePin(GPIOA, LED_G1_Pin, 0);
					HAL_GPIO_WritePin(GPIOA, LED_Y1_Pin | LED_R1_Pin, 1);
					break;
				case LED_AMBER:
					HAL_GPIO_WritePin(GPIOA, LED_Y1_Pin, 0);
					HAL_GPIO_WritePin(GPIOA, LED_R1_Pin | LED_G1_Pin, 1);
					break;
				default:
					break;
			}
			break;

		case TRAFFIC_2ND: // Bật đèn của trụ số 2
			switch(type){
				case LED_RED:
					HAL_GPIO_WritePin(GPIOA, LED_R2_Pin, 0);
					HAL_GPIO_WritePin(GPIOA, LED_G2_Pin | LED_Y2_Pin, 1);
					break;
				case LED_GREEN:
					HAL_GPIO_WritePin(GPIOA, LED_G2_Pin, 0);
					HAL_GPIO_WritePin(GPIOA, LED_Y2_Pin | LED_R2_Pin, 1);
					break;
				case LED_AMBER:
					HAL_GPIO_WritePin(GPIOA, LED_Y2_Pin, 0);
					HAL_GPIO_WritePin(GPIOA, LED_R2_Pin | LED_G2_Pin, 1);
					break;
				default:
					break;
			}
			break;

		default:
			break;
	}
}

void displayTime7Seg(){
	if (isTimerFlagOn(TIMER_7SEG)){
		setTimer(TIMER_7SEG, 250);
		enable7Seg(led7SegIndex);
		led7SegIndex = (led7SegIndex + 1) % 4;	// tăng index lên 1
	}
}
