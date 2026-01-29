/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define VSYNC_FREQ_Pin GPIO_PIN_2
#define VSYNC_FREQ_GPIO_Port GPIOE
#define RENDER_TIME_Pin GPIO_PIN_3
#define RENDER_TIME_GPIO_Port GPIOE
#define FRAME_RATE_Pin GPIO_PIN_4
#define FRAME_RATE_GPIO_Port GPIOE
#define MCU_ACTIVE_Pin GPIO_PIN_5
#define MCU_ACTIVE_GPIO_Port GPIOE
#define SPI5_NCS_Pin GPIO_PIN_1
#define SPI5_NCS_GPIO_Port GPIOC

#define BTN_PORT GPIOC
#define BTN_UP_PIN GPIO_PIN_15
#define BTN_DOWN_PIN GPIO_PIN_4
#define BTN_LEFT_PIN GPIO_PIN_14
#define BTN_RIGHT_PIN GPIO_PIN_8

#define MSK_UP 0x01
#define MSK_DOWN 0x02
#define MSK_LEFT 0x04
#define MSK_RIGHT 0x08

uint8_t HAL_Get_Button_State(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
