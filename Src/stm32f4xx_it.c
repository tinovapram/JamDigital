/**
 ******************************************************************************
 * @file    stm32f4xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 *
 * COPYRIGHT(c) 2017 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
#include "LCD_Char.h"
#include "stdbool.h"
extern uint8_t detik, menit, jam, ms;
extern uint8_t tO1, tO2;
extern bool teken1, teken2;
extern char b1[16], b2[16];
extern enum {
	tampil, ubah_jam, ubah_menit, ubah_detik
} state;
uint8_t blink;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern SDRAM_HandleTypeDef hsdram1;
extern LTDC_HandleTypeDef hltdc;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles FMC global interrupt.
 */
void FMC_IRQHandler(void) {
	/* USER CODE BEGIN FMC_IRQn 0 */

	/* USER CODE END FMC_IRQn 0 */
	HAL_SDRAM_IRQHandler(&hsdram1);
	/* USER CODE BEGIN FMC_IRQn 1 */

	/* USER CODE END FMC_IRQn 1 */
}

/**
 * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
 */
void TIM6_DAC_IRQHandler(void) {
	/* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	/* USER CODE END TIM6_DAC_IRQn 0 */
	HAL_TIM_IRQHandler(&htim6);
	/* USER CODE BEGIN TIM6_DAC_IRQn 1 */

	sprintf(b1, "%2d:%2d:%2d", jam, menit, detik);
	blink = ~blink;
	if (blink) {
		switch (state) {
		case tampil:
			break;

		case ubah_jam:
			b1[0] = ' ';
			b1[1] = ' ';
			break;

		case ubah_menit:
			b1[3] = ' ';
			b1[4] = ' ';
			break;

		case ubah_detik:
			b1[6] = ' ';
			b1[7] = ' ';
			break;
		}
	}
	lcd_gotoxy(0, 0);
	lcd_putstr(b1);
	/* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
 * @brief This function handles TIM7 global interrupt.
 */
void TIM7_IRQHandler(void) {
	/* USER CODE BEGIN TIM7_IRQn 0 */

	/* USER CODE END TIM7_IRQn 0 */
	HAL_TIM_IRQHandler(&htim7);
	/* USER CODE BEGIN TIM7_IRQn 1 */
	if (++ms >= 100) {
		ms = 0;
		++detik;
	}
	if (detik >= 60) {
		detik = 0;
		++menit;
	}
	if (menit >= 60) {
		menit = 0;
		++jam;
	}

	if (jam >= 24) {
		jam = 0;
	}
	if (teken1) {
		tO1++;
	}
	if (teken2) {
		tO2++;
	}
	/* USER CODE END TIM7_IRQn 1 */
}

/**
 * @brief This function handles LTDC global interrupt.
 */
void LTDC_IRQHandler(void) {
	/* USER CODE BEGIN LTDC_IRQn 0 */

	/* USER CODE END LTDC_IRQn 0 */
	HAL_LTDC_IRQHandler(&hltdc);
	/* USER CODE BEGIN LTDC_IRQn 1 */

	/* USER CODE END LTDC_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
