/*
 * fsm_mode_traffic.h
 *
 *  Created on: Dec 18, 2022
 *      Author: HP
 */

#ifndef INC_FSM_MODE_TRAFFIC_H_
#define INC_FSM_MODE_TRAFFIC_H_

// Các mode: init, Mode_1: đèn gt bình thường, mode_2-4: config các led
#define INIT   10
#define MODE_1 11
#define MODE_2 12
#define MODE_3 13
#define MODE_4 14

// FSM main method
void fsmModeTraffic();

#endif /* INC_FSM_MODE_TRAFFIC_H_ */
