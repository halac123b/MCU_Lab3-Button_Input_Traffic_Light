/*
 * temp.h
 *
 *  Created on: Dec 20, 2022
 *      Author: HP
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

// Số lượng button
#define NO_OF_BUTTONS 3

// Index of button
#define BTN_1  0
#define BTN_2  1
#define BTN_3  2

// Đọc signal từ button
void buttonReading(void);

// Xác nhận button có đc nhấn hay không
int isBtnPressed(int index);

// Đánh dấu button đang đc nhấn hợp lệ
void flagButton(int index);

#endif /* INC_INPUT_READING_H_ */
