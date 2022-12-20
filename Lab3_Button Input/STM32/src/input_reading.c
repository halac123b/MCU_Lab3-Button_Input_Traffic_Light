/*
 * temp.c
 *
 *  Created on: Dec 20, 2022
 *      Author: HP
 */

#include "input_reading.h"
#include "main.h"

// Define state of button
#define IS_PRESSED   GPIO_PIN_RESET
#define IS_RELEASED  GPIO_PIN_SET

// Store button state in 3 buffers for debouncing
int keyReg0[NO_OF_BUTTONS] = {IS_RELEASED};
int keyReg1[NO_OF_BUTTONS] = {IS_RELEASED};
int keyReg2[NO_OF_BUTTONS] = {IS_RELEASED};

// Buffer lưu state chuẩn trc đó, để check nhấn đè
int keyReg3[NO_OF_BUTTONS] = {IS_RELEASED};

// Thời gian chờ khi nhấn đè (500ms)
int timeOutForKeyPress[NO_OF_BUTTONS] = {500};
// Nếu button đang bị nhấn đè thì phải chờ 500ms flag mới hợp lệ
int flagBtn[NO_OF_BUTTONS];

void buttonReading(void){
	for (int i = 0; i < NO_OF_BUTTONS; i++){
		// Lưu lại các kết quả đọc đc từ 2 lần trc đó vào buffer
		keyReg2[i] = keyReg1[i];
		keyReg1[i] = keyReg0[i];
		switch(i){	// check button nào đang đc nhấn, đọc signal từ button đó vào regKey0
			case BTN_1:
				keyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_1_Pin);
				break;
			case BTN_2:
				keyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_2_Pin);
				break;
			case BTN_3:
				keyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_3_Pin);
				break;
			default:
				break;
		}
		// Check 3 buffer xem có bằng nhau không
		if (keyReg1[i] == keyReg0[i] && keyReg1[i] == keyReg2[i]){
			// Check xem có bằng giá trị trong buffer 4 check nhấn đè k
			if (keyReg2[i] != keyReg3[i]){
				// Nếu khác thì lưu gt mới đó vào buffer 4
				keyReg3[i] = keyReg2[i];

				// Nếu là signal nhấn, thì flag hợp lệ, và đặt tg chờ 500ms nếu nhấn đè
				if (keyReg3[i] == IS_PRESSED){
					timeOutForKeyPress[i] = 500;
					flagButton(i);
				}
			} else {  // hoặc nếu 2 gt bằng nhau thì đó có thể là nhấn đè
				timeOutForKeyPress[i]--;  // giảm tg chờ
				// Nếu đã đếm xong đặt buffer 4 về RELEASE để button đc nhận tín hiệu mới
				if (timeOutForKeyPress[i] <= 0)
					keyReg3[i] = IS_RELEASED;
			}
		}
	}
}

void flagButton(int index){
	flagBtn[index] = 1;
}

int isBtnPressed(int index){
	// Chỉ khi đc flag hợp lệ thì mới return 1, sau đó set flag lại về 0
	if (flagBtn[index] == 1){
		flagBtn[index] = 0;
		return 1;
	}
	return 0;
}

