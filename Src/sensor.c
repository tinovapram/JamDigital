/*
 * sensor.c
 *
 *  Created on: 9 Nov 2017
 *      Author: tinova
 */

#include "sensor.h"
extern uint8_t tO1, tO2;
extern bool teken1, teken2;
uint8_t btn_advance(void) {
	uint8_t FlagDetect = 0;
	if (HAL_GPIO_ReadPin(SSBtn_GPIO_Port, SSBtn_Pin) == GPIO_PIN_RESET) {
		teken1 = 1;
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(SSBtn_GPIO_Port, SSBtn_Pin) == GPIO_PIN_RESET) {
			while (HAL_GPIO_ReadPin(SSBtn_GPIO_Port, SSBtn_Pin)
					== GPIO_PIN_RESET && tO1 <= 100)
				;
			if (tO1 > 100) {
				FlagDetect = 2;
			} else {
				FlagDetect = 1;
				tO1 = 0;
			}
		}
	} else {
		tO1 = 0;
	}
	teken1 = 0;
	return FlagDetect;
}
uint8_t btn_mode(void) {
	tO2 = 0;
	uint8_t FlagDetect = 0;
	if (HAL_GPIO_ReadPin(RstBtn_GPIO_Port, RstBtn_Pin) == GPIO_PIN_RESET) {
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(RstBtn_GPIO_Port, RstBtn_Pin) == GPIO_PIN_RESET) {
			while (HAL_GPIO_ReadPin(RstBtn_GPIO_Port, RstBtn_Pin)
					== GPIO_PIN_RESET && tO2 <= 100)
				;
			if (tO2 > 100) {
				FlagDetect = 2;
			} else {
				FlagDetect = 1;
			}
		}
	}
	teken2 = 0;
	return FlagDetect;
}
