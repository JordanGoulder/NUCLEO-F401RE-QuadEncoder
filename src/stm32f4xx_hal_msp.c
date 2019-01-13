/**
  ******************************************************************************
  * @file   stm32f4xx_hal_msp.c
  * @author Jordan Goulder
  * @brief  Implements MCU Support Package functions that perform low level
  *         peripheral initialization. This functions are called by the HAL.
  ******************************************************************************
*/

#include "stm32f4xx_hal.h"

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *hTimer)
{
    // Timer 2 Channel 1 and Channel 2 pins are on PA0 and PA1
    // Enable GPIO Port A clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Enable Timer 2 clock
    __HAL_RCC_TIM2_CLK_ENABLE();

    // Structure used to initialize GPIO pins
    GPIO_InitTypeDef gpioInit;

    // Configure GPIO Timer 2 channel 1 pin
    gpioInit.Pin = GPIO_PIN_0;
    gpioInit.Mode =  GPIO_MODE_AF_PP;
    gpioInit.Alternate = GPIO_AF1_TIM2;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &gpioInit);

    // Configure GPIO Timer 2 channel 2 pin
    gpioInit.Pin = GPIO_PIN_1;
    gpioInit.Mode =  GPIO_MODE_AF_PP;
    gpioInit.Alternate = GPIO_AF1_TIM2;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &gpioInit);
}

void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *hTimer)
{
    // Reset Timer 2
    __HAL_RCC_TIM2_FORCE_RESET();
    __HAL_RCC_TIM2_RELEASE_RESET();

    // Put GPIO pins back to default state
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);
}

void HAL_UART_MspInit(UART_HandleTypeDef *hUart)
{
    // USART2 pins are on PA2 and PA3
    // Enable GPIO Port A clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Enable USART2 clock
    __HAL_RCC_USART2_CLK_ENABLE();

    // Structure used to initialize GPIO pins
    GPIO_InitTypeDef gpioInit;

    // Configure GPIO TX pin
    gpioInit.Pin = GPIO_PIN_2;
    gpioInit.Mode =  GPIO_MODE_AF_PP;
    gpioInit.Alternate = GPIO_AF7_USART2;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &gpioInit);

    // Configure GPIO RX pin
    gpioInit.Pin = GPIO_PIN_3;
    gpioInit.Mode =  GPIO_MODE_AF_PP;
    gpioInit.Alternate = GPIO_AF7_USART2;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &gpioInit);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    // Reset USART2
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();

    // Put GPIO pins back to default state
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
}
