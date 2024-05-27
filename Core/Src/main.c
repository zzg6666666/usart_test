/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  //初始化HAL库
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  // 配置system clock pll HCLK PCLK1 PCK2
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //初始化DMA
  MX_DMA_Init();
  // 初始化串口
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  char TxData[] = "ABCADADADDADAD1213ADSADADADvcDADADvxvADSADADgdg5gljkdk;  \r\nhgsuirgfiuwgrfajyfdgayujdfajydfaudfaudfyauydfyafdyaiudgaiodgaiodaidg\n\r";
  while (1)
  {
    /* USER CODE END WHILE */
    HAL_UART_Transmit_DMA(&huart1,(uint8_t*)TxData,strlen(TxData));
    HAL_Delay(1000);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  //内部/外部振荡器结构体
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  //RCC系统、AHB总线和APB总线的时钟配置结构定义
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  //配置时钟结构体
  //配置外置时钟
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  //开启外置时钟
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  //HSE时钟预分频器 设置为不分频 RCC_CFGR bit17
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  //开启内置时钟
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  //使用PLL
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  //PLL时钟源是HSE
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  //PLL倍频9倍
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

  //配置HSE、PLL
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  //使能HCLK、SYSCLK、PCLK1、PCLK2
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  //系统时钟使用PLL
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  //AHB预分频器不分频
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  //APB1预分频器2分频
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  //APB2预分频器不分频
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
