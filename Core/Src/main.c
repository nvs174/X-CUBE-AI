/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "sine_model.h"
#include "sine_model_data.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_MODBUS_FRAME_SIZE 15

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim11;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */

char rx_buffer[MAX_MODBUS_FRAME_SIZE] = {0};
char tx_buffer[MAX_MODBUS_FRAME_SIZE] = {0};
char buffer[MAX_MODBUS_FRAME_SIZE] = {0};
double sum = 0;
float y_val;
bool flagMeasure = false;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM11_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void restartDMA();
void initRX();
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


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





	char buf[50]; // буфер для строк вывода данных
	int buf_len = 0; //
	ai_error ai_err; // код ошибок
	ai_i32 nbatch;
	uint32_t timestamp; // метка времени


	// Массив для хранения активаций модели, выровненный на 4 байта,
	// тип данных - беззнаковый 8-битный целочисленный
	AI_ALIGNED(4) ai_u8 activations[AI_SINE_MODEL_DATA_ACTIVATIONS_SIZE];

	// Массив для хранения входных данных модели, выровненный на 4 байта,
	//тип данных - знаковый 8-битный целочисленный
	AI_ALIGNED(4) ai_i8 in_data[AI_SINE_MODEL_IN_1_SIZE_BYTES];

	// Массив для хранения выходных данных модели, выровненный на 4 байта,
	//тип данных - знаковый 8-битный целочисленный
	AI_ALIGNED(4) ai_i8 out_data[AI_SINE_MODEL_OUT_1_SIZE_BYTES];

	// Инициализация дескриптора модели синусоиды значением NULL,
	//указывающим на отсутствие активной модели
	ai_handle sine_model = AI_HANDLE_NULL;

	// Массив буферов для хранения входных данных модели,
	//количество буферов определяется константой AI_SINE_MODEL_IN_NUM
	ai_buffer ai_input[AI_SINE_MODEL_IN_NUM];
	ai_input[0] = ai_sine_model_inputs_get(AI_HANDLE_NULL, NULL)[0];


	// Массив буферов для хранения выходных данных модели, инициализированный
	//значением AI_SINE_MODEL_OUT,
	//количество буферов определяется константой AI_SINE_MODEL_OUT_NUM

	ai_buffer ai_output[AI_SINE_MODEL_IN_NUM];
	ai_output[0] = ai_sine_model_outputs_get(AI_HANDLE_NULL, NULL)[0];
	//ai_buffer ai_output[AI_SINE_MODEL_OUT_NUM] = AI_SINE_MODEL_OUT;

	// Инициализация структуры параметров сети
		ai_network_params ai_params = {
			// Получение весов модели синусоиды и установка их в параметры сети
			AI_SINE_MODEL_DATA_WEIGHTS(ai_sine_model_data_weights_get()),

			// Указание буфера активации для хранения
			//промежуточных данных во время выполнения модели
			AI_SINE_MODEL_DATA_ACTIVATIONS(activations)
	};

	ai_input[0].data = AI_HANDLE_PTR(in_data);  // Установка указателя на входные данные
	ai_input[0].size = sizeof(in_data);          // Установка размера входных данных, замените на актуальный размер
	ai_input[0].format = AI_BUFFER_FORMAT_FLOAT; // Установка формата данных (например, float, если это необходимо)

	ai_output[0].data = AI_HANDLE_PTR(out_data); // Установка указателя на выходные данные
	ai_output[0].size = sizeof(out_data);         // Установка размера выходных данных
	ai_output[0].format = AI_BUFFER_FORMAT_FLOAT; // Установка формата данных

	// time 9.25
	/*ai_input[0].n_batches = 1;
	ai_input[0].data = AI_HANDLE_PTR(in_data);
	ai_output[0].n_batches = 1;
	ai_input[0].data = AI_HANDLE_PTR(in_data);*/


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM11_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim11);
  //Взводим прием данных по USART 1 раз
  		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rx_buffer, MAX_MODBUS_FRAME_SIZE);
  		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
  //buf_len = sprintf(buf, "\r\n\r\nStm32 x-cube-ai test\r\n");
  //HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
  ai_err = ai_sine_model_create(&sine_model, AI_SINE_MODEL_DATA_CONFIG);

  // проверка на ошибку
  if (ai_err.type != AI_ERROR_NONE)
  {
	  buf_len = sprintf(buf, "Error: could not create NN instance\r\n");
	  //HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	  while(1);
  }

  if (!ai_sine_model_init(sine_model, &ai_params))
  {
	  buf_len = sprintf(buf, "Error: could not initialize NN\r\n");
	  //HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	  while(1);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (flagMeasure)
	  {
	  /*in_data[0] = (ai_float)0.785f;
	  in_data[1] = (ai_float)1.571f;
	  in_data[2] = (ai_float)2.356f;
	  in_data[3] = (ai_float)3.142f;
	  in_data[4] = (ai_float)3.927f;
	  in_data[5] = (ai_float)4.712f;
	  in_data[6] = (ai_float)5.498f;
	  in_data[7] = (ai_float)6.283f;*/
	  // присваиваем значение элементам массива, в данном случае только один элемент массива
	  for(uint32_t i = 0; i < AI_SINE_MODEL_IN_1_SIZE; i++)
	  {
		  // Присваиваем каждому элементу массива in_data значение 2.0
		  ((ai_float *)in_data)[i] = (ai_float)sum;
		  //in_data[i] = (ai_float)2.0f;
		  //in_data[i] = (ai_float)
	  }

	  // Сохраняем текущее значение счетчика таймера в переменной timestamp
	  timestamp = htim11.Instance->CNT;

	  // Запускаем модель с входными данными ai_input и получаем выходные данные в ai_output
	  nbatch = ai_sine_model_run(sine_model, &ai_input[0], &ai_output[0]);

	  // Проверяем, успешно ли выполнен запуск модели
	  if (nbatch != 1)
	  {
	      // Если запуск не удался, формируем сообщение об ошибке
	      buf_len = sprintf(buf, "Error: could not run interface\r\n");
	      // Передаем сообщение по UART (закомментировано)
	      // HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	  }

	  // Извлекаем первое значение из выходных данных out_data
	  y_val = ((float*) out_data)[0];
	  int i = y_val * 1000;
	  tx_buffer[0] =  i / 100 + '0';
	  tx_buffer[1] = ( i / 10) % 10 + '0';
	  tx_buffer[2] =  i % 10 + '0';
	  buf_len = sprintf(buf, "Output: %f | Duration: %lu\r\n", y_val, htim11.Instance->CNT - timestamp);
	  HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	  // HAL_UART_Transmit_DMA(&huart2, (uint8_t)tx_buffer, 3);
	  flagMeasure = false;
	  }
	  // Формируем строку с результатом и временем выполнения
	  //buf_len = sprintf(buf, "Output: %f | Duration: %lu\r\n", y_val, htim11.Instance->CNT - timestamp);

	  // Передаем строку с результатом по UART (закомментировано)
	  // HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);

	  // Задержка на 500 миллисекунд
	  //HAL_Delay(500);
	//  }



	  /*timestamp = htim11.Instance->CNT;

	  nbatch = ai_sine_model_run(sine_model, &ai_input[0], &ai_output[0]);
	  if (nbatch != 1)
	  {
		  buf_len = sprintf(buf, "Error: could not run interfance\r\n");
		  //HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	  }
	  y_val = ((float*) out_data)[0];

	  buf_len = sprintf(buf, "Output: %f | Duration: %lu\r\n", y_val, htim11.Instance->CNT - timestamp);
	  //HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	  HAL_Delay(500);*/
    /* USER CODE END WHILE */

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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 80-1;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 65535;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
  {
	if(huart == &huart2)
	{
			//mb_tx_cmplt = true;
		}
  }

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART2)
	{

		long long all = 0; // Для целой части
		            double half = 0.0; // Для дробной части
		            int divisor = 1; // Делитель для дробной части
		            bool flagHalf = true; // Флаг для определения, в какой части находимся

		            for (int i = 0; Size - 2 > i; i++) {
		                if (rx_buffer[i] == '.') {
		                	flagHalf = false; // Переключаемся на дробную часть
		                    continue; // Переходим к следующему символу
		                }

		                if (flagHalf) {
		                	all = all * 10 + (rx_buffer[i] - '0'); // Обрабатываем целую часть
		                } else {
		                	half = half * 10 + (rx_buffer[i] - '0'); // Обрабатываем дробную часть
		                    divisor *= 10; // Увеличиваем делитель
		                }
		            }

		            half /= divisor; // Приводим дробную часть к правильному виду
		            sum = (double)all + half; // Используем double для
		            HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rx_buffer, 20);
		            __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
		            flagMeasure = true;
	}
}


void initRX()
{

 	 // Очистка буфера и сброс флагов
 	 UART_ClearBuffer(&huart2, rx_buffer, sizeof(rx_buffer));
 	 UART_ResetErrorFlags(&huart2);

 	 HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rx_buffer, MAX_MODBUS_FRAME_SIZE);
 	 __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
 }




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
