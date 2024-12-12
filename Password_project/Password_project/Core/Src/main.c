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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "liquidcrystal_i2c.h"
#include "stdio.h"
#include "string.h"
#include "flash.h"
//#include "rc522.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define ADDRESS_DATA_STORAGE 0x800FC00
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint8_t pass_def[4] = {'1','1','2','1'};
uint8_t arr3[4]={'*','0','7','#'};
uint8_t arr2[4]={'0','0','0','0'};

uint8_t input[4]={};//initialize input buffer
unsigned char i=0;
int  count=0;
int check_R1();
int check_R2();
int check_R3();
int check_R4();
int key_Detect();
void checkKeypad();
int Hide_pass();
int pass_change();
int checkcode();
//uint8_t status;
//uint8_t str[MAX_LEN]; // Max_LEN = 16
//uint8_t sNum[5];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	HD44780_Init(2);
//	MFRC522_Init();
//	Flash_Erase(ADDRESS_DATA_STORAGE);

//	Flash_Write_Array(ADDRESS_DATA_STORAGE, pass_def, 4);
	unsigned char x[4]= {'0','0','0','0'};
	Flash_Read_Array(ADDRESS_DATA_STORAGE,arr2,4);
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintSpecialChar(arr2[0]);
	HD44780_PrintSpecialChar(arr2[1]);
	HD44780_PrintSpecialChar(arr2[2]);
	HD44780_PrintSpecialChar(arr2[3]);
	

//	Flash_Write_Array(ADDRESS_DATA_STORAGE, arr3, 4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//		Flash_Read_Array(ADDRESS_DATA_STORAGE,x,4);

////	HD44780_SetCursor(0,0);
//	HD44780_PrintSpecialChar(x[0]);
//	HD44780_PrintSpecialChar(x[1]);
//	HD44780_PrintSpecialChar(x[2]);
//	HD44780_PrintSpecialChar(x[3]);
	checkKeypad();
//		int y = key_Detect();
//		HD44780_PrintSpecialChar(y);
//		status = MFRC522_Request(PICC_REQIDL, str);
//		status = MFRC522_Anticoll(str);
//		memcpy(sNum, str, 5);
//		HAL_Delay(100);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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

GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA4 PA5 PA6
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int check_R1(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '1';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '2';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '3';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'A';
		}
	else return '\0';
}
int check_R2(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '4';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '5';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '6';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'B';
		}
	else return '\0';
}
int check_R3(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '7';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '8';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '9';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'C';
		}
	else return '\0';
}
int check_R4(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		   return '*';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '0';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '#';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'D';
		}
	else return '\0';
}

int key_Detect(){

//	GPIOB->ODR&=0x00000000;
//	GPIOB->ODR|=0x1000;//PB12-PB15 row pins
	GPIOB->ODR = 0x1000;
    if(check_R1()!='\0'){
   return check_R1();

    }HAL_Delay(10);

//    GPIOB->ODR&=0x0000;
//    GPIOB->ODR|=0x2000;
		GPIOB->ODR = 0x2000;
    if(check_R2()!='\0'){
    	 return check_R2();

        }HAL_Delay(10);

//    GPIOB->ODR&=0x0000;
//    GPIOB->ODR|=0x4000;
			GPIOB->ODR = 0x4000;
     if(check_R3()!='\0'){
    	 return check_R3();

            }HAL_Delay(10);

//     GPIOB->ODR&=0x0000;
//     GPIOB->ODR|=0x8000;
			GPIOB->ODR = 0x8000;
       if(check_R4()!='\0'){
    	    return check_R4();

            }HAL_Delay(10);
return 'E';
}

void checkKeypad(){
	char temp;
	HD44780_SetCursor(0,0);
	repeat:
	HD44780_PrintStr("Enter Password:");
	HD44780_SetCursor(0,1);
	while(key_Detect()!='E'){
		while(i<4){
										if(key_Detect()!='E'){
										input[i]=key_Detect();
										Hide_pass();
										HAL_Delay(500);
										i++;
										}
		}


		if(i>3){
			 if(checkcode()){
				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
				 HAL_Delay(2000);
				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
							HD44780_SetCursor(0,1);
							HD44780_PrintStr("Access Granted");
							HAL_Delay(3000);
							HD44780_Clear();
							for(char cnt =0; cnt < 10; cnt++){
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
							HAL_Delay(1);
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
							HAL_Delay(20);
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
							HAL_Delay(100);
							}

						

							i=0;//Reset input Buffer index
						memset(input,0,4);
						}
			 else if (pass_change()){
				HD44780_SetCursor(0,0);
				HAL_Delay(1000);
				HD44780_PrintStr("Enter old Pass:");
				HAL_Delay(2000);
				HD44780_Clear();
				memset(input,0,4);
				i=0;
				while(i<4){
				if(key_Detect()!='E'){
				input[i]=key_Detect();
				Hide_pass();
				HAL_Delay(700);
				i++;
				}
				}
				for(i=0;i<4;i++){
						 if(input[i]!=arr2[i]){
							HAL_Delay(100);
							HD44780_Clear();
							HD44780_SetCursor(0,1);
							HD44780_PrintStr("Wrong Password");
							HAL_Delay(2000);
							HD44780_Clear();
							goto repeat;
						}
						}
				HAL_Delay(100);
				HD44780_Clear();
				HD44780_SetCursor(0,0);
				HD44780_PrintStr(".................");
				HAL_Delay(1000);
				HD44780_Clear();
				HD44780_PrintStr("Enter New Pass:");
				memset(input,0,4);
				memset(arr2,0,4);
								i=0;
								HD44780_SetCursor(0,1);
								while(i<4){
								if(key_Detect()!='E'){
								input[i]=key_Detect();
								Hide_pass();
								HAL_Delay(500);
								i++;
								}
								}
				for(i=0;i<4;i++){
					temp=input[i];
					arr2[i]=temp;
					HD44780_PrintSpecialChar(arr2[i]);
					HAL_Delay(100);
					}
				HAL_Delay(1000);
				HD44780_Clear();
				HD44780_SetCursor(0,1);
				HD44780_PrintStr("Password Reset!");
				i=0;
				memset(input,0,4);
				HAL_Delay(1000);

				HD44780_Clear();

			}




			else{
				HD44780_SetCursor(0,1);
				HD44780_PrintStr("Access Denied!");
				HAL_Delay(2000);
				HD44780_Clear();
				for(int j=0;j<3;j++){
        //buzzer  going to ring  for 3 times indicating wrong password
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
				 HAL_Delay(1000);
				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
				 HAL_Delay(1000);
				}
				i=0;
				memset(input,0,4);
			}
		}
	}
}
int checkcode(){
	unsigned char i;
	//Flash_Read_Array(ADDRESS_DATA_STORAGE, arr2, 4);
	     for(i=0;i<4;i++){

				if(input[i]!=arr2[i]){
					return 0;
				}
				}
	     return 1;
}
int pass_change(){
	 for(i=0;i<4;i++){
		if(input[i]!=arr3[i]) {
			return 0;
		}

	 }
	 return 1;
}
int Hide_pass(){

	HD44780_PrintSpecialChar('*');
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
