/*
 * config_duration.h
 *
 *  Created on: Dec 18, 2022
 *      Author: HP
 */

#ifndef INC_CONFIG_DURATION_H_
#define INC_CONFIG_DURATION_H_

// Switch giữa các mode
void changeModeBuffer(int mode);
// khi nhấn button burration của đèn đó sẽ tăng lên (<100)
void increaseTempLedDuration();
// Xác nhận update duraion của led
void updateLedDuration(int led);

#endif /* INC_CONFIG_DURATION_H_ */
