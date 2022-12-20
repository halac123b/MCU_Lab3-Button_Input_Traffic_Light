/*
 * display_led.h
 *
 *  Created on: Dec 18, 2022
 *      Author: HP
 */

#ifndef INC_DISPLAY_LED_H_
#define INC_DISPLAY_LED_H_

// Index for color led
#define LED_RED     0
#define LED_AMBER   1
#define LED_GREEN   2

// Index for display mode of traffic light
#define DISPLAY_INIT   22
#define DISPLAY_RED    23
#define DISPLAY_GREEN  24
#define DISPLAY_AMBER  25

// Turn off all led
void clearAllLed();

//for test led in PA5
void displayTestLed();
void clearTestLed();

// Trong các mode config duration, đèn của màu đó sẽ blink
void displayBlinkyLed(int index);

//for 7 segments led
void display7Seg(int num);
// điều khiển signal transistor để enable led-7 nào đc sáng
void enable7Seg(int index);

// Display các traffic light trong MODE_1
void displayLight(int index, int type);
// Display các led-7 đếm giờ của traffic light
void displayTime7Seg();
// Điều khiển các state của traffic light, display ra đèn và đếm ngược thời gian cho led 7-seg
void displayTrafficLed(int index);

#endif /* INC_DISPLAY_LED_H_ */
