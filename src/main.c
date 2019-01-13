/**
  ******************************************************************************
  * @file   main.c
  * @author Jordan Goulder
  * @brief  Setup the encoder interface and continuously print the current
  *         position.
  ******************************************************************************
*/

#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

UART_HandleTypeDef hUart;

void error_handler();

int main(void)
{
    // Initialize the Hardware Abstraction Library
    HAL_Init();

    // Initialize LED2, it remain solid unless there is an error
    // If there is an error, LED2 will be blinking
    BSP_LED_Init(LED2);
    BSP_LED_On(LED2);


    // Configure the timer settings
    TIM_HandleTypeDef hTimer;
    memset(&hTimer, 0, sizeof(hTimer));

    hTimer.Instance = TIM2;
    hTimer.Init.Period = UINT32_MAX;

    // Configure the encoder settings
    TIM_Encoder_InitTypeDef hEncoderConfig;
    memset(&hEncoderConfig, 0, sizeof(hEncoderConfig));

    hEncoderConfig.EncoderMode  = TIM_ENCODERMODE_TI12;

    hEncoderConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    hEncoderConfig.IC1Filter    = 0;
    hEncoderConfig.IC1Prescaler = TIM_ICPSC_DIV1;
    hEncoderConfig.IC1Polarity  = TIM_ICPOLARITY_RISING;

    hEncoderConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    hEncoderConfig.IC2Filter    = 0;
    hEncoderConfig.IC2Prescaler = TIM_ICPSC_DIV1;
    hEncoderConfig.IC2Polarity  = TIM_ICPOLARITY_RISING;

    // Initialize the encoder interface
    if (HAL_TIM_Encoder_Init(&hTimer, &hEncoderConfig) != HAL_OK)
    {
        error_handler();
    }

    // Start the encoder interface
    if (HAL_TIM_Encoder_Start(&hTimer, TIM_CHANNEL_ALL) != HAL_OK)
    {
        error_handler();
    }

    // Configure the USART settings
    hUart.Instance             = USART2;
    hUart.Init.BaudRate        = 9600;
    hUart.Init.WordLength      = UART_WORDLENGTH_8B;
    hUart.Init.Parity          = UART_PARITY_NONE;
    hUart.Init.StopBits        = UART_STOPBITS_1;
    hUart.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
    hUart.Init.Mode            = UART_MODE_TX_RX;
    hUart.Init.OverSampling    = UART_OVERSAMPLING_8;

    // Initialize the USART
    if (HAL_UART_Init(&hUart) != HAL_OK)
    {
        error_handler();
    }

    // Loop forever printing out the encoder position
    for(;;)
    {
        // Get the current encoder position
        int position = __HAL_TIM_GET_COUNTER(&hTimer);

        // Print out the current encoder position
        printf("Position: %d\r\n", position);

        HAL_Delay(250);
    }
}

int __io_putchar(int ch)
{
    // Transmit character with the UART
    HAL_UART_Transmit(&hUart, (uint8_t *) &ch, 1, HAL_MAX_DELAY);
    return ch;
}

void error_handler()
{
    // loop forever flashing LED2
    while(1)
    {
        BSP_LED_Toggle(LED2);
        HAL_Delay(250);
    }
}
