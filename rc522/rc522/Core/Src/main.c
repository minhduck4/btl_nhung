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
#include "rc522.h"
#include "string.h"
#include "stdio.h"
#include "liquidcrystal_i2c.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define buzer_Pin GPIO_PIN_13
#define buzer_GPIO_Port GPIOB
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
uint8_t status;
//uint8_t str[MAX_LEN]; // Max_LEN = 16
uint8_t sNum[5];
uint8_t okunan_ham[MFRC522_MAX_LEN] ;
uint8_t kart_no[5] ;
uint8_t kayitli_id1[5] ={0x91,0xF3,0xB2,0x1D,0} ; //ALI
uint8_t kayitli_id2[5] ={108,101,174,219,124} ; //SALIH
uint8_t kayitli_id3[5] ={131,4,24,173,50} ;   //SAKINE
uint8_t kayitli_id4[5] ={83,117,183,29,140} ;  //VELI
uint8_t text1[16];
uint8_t durum ;
char buffer[4];
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
void Servo_Angle(int angle);
void ana_erkan();
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_I2C1_Init(void);
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
  MX_SPI1_Init();
  MX_TIM1_Init();
	MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	HD44780_Init(2);
	HD44780_SetCursor(0,0);
	HD44780_PrintStr("Hi");
  MFRC522_Init();
	 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	 char status_str[4];
  /* USER CODE END 2 */

  /* Infinite loop */
		/* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // Kéo NSS xu?ng
		status = MFRC522_Request(PICC_REQIDL, okunan_ham);
		HAL_Delay(5000);
if (status == MI_OK) {
    HD44780_SetCursor(0, 0);
    HD44780_PrintStr("The da phat hien");
} else if(status != MI_OK){
    HD44780_SetCursor(0, 0);
    HD44780_PrintStr("Khong thay the");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);   // Kéo NSS lên
}

    /* USER CODE END WHILE */
//		status = MFRC522_Request(PICC_REQIDL,okunan_ham );
//		sprintf(status_str, "%d", status);
//		HD44780_SetCursor(0,0);
//		HD44780_PrintSpecialChar(status_str[0]);
//		HAL_Delay(1000);
//	  if( MFRC522_Request(PICC_REQIDL,okunan_ham) ) //Hàm REQUEST liên t?c ki?m tra xem có th? RFID hay không.
//	  	 {

//			HD44780_SetCursor(0,0);
//			HD44780_PrintStr("Found");
//				 }
////	  	      if(! MFRC522_Anticoll(okunan_ham)) //Khi phát hi?n b?t k? th? nào, nó s? không d?c th? th? hai.
////	  	      {
////	  	        for(int a = 0 ; a<5; a++) //huy?n d? li?u thô dã d?c vào KART NO.
////	  	        {
////	  	          kart_no[a] = okunan_ham[a];

////	  	        }
////							text1[0] = '\0';
////							for (int i = 0; i < 5; i++) { 
////								sprintf(buffer, "%d", kart_no[i]); // Chuy?n d?i s? thành chu?i 
////								strcat((char*)text1, buffer); // N?i chu?i vào text1 
////								}
////	  	                 
////	  	       	         		 HD44780_Clear();
////	  	       	         		 HD44780_SetCursor(0,0);
////							HD44780_PrintStr("KART OKUNDU");
////													HD44780_SetCursor(0,1);
////							for(uint8_t i=0;i<15;i++)
////							{
////								HD44780_PrintSpecialChar(text1[i]);
////								
////							}
////	  	       	         		
////	  	       	         		 HAL_GPIO_WritePin(buzer_GPIO_Port, buzer_Pin,GPIO_PIN_SET);
////	  	       	         		 HAL_Delay(250);
////	  	       	         	     HAL_GPIO_WritePin(buzer_GPIO_Port, buzer_Pin,GPIO_PIN_RESET);
////	  	       	         		 HAL_Delay(2000) ;



////	  	 if( (MFRC522_Compare(kart_no, kayitli_id1) == MI_OK )) //Hàm COMPARE th?c hi?n so sánh, n?u dúng thì s? vào l?nh if.
////	  	 {
////	  		HD44780_Clear();
////	  		HD44780_SetCursor(0,0);
////				 HD44780_PrintStr("    MERHABA");
////	  		HD44780_SetCursor(0,1);
////				 HD44780_PrintStr("      ALi");
////	  		HAL_Delay(1500);
////	  		 durum = 1 ;

////	  	 }
////	  	 else if((MFRC522_Compare(kart_no, kayitli_id2) == MI_OK )) //Hàm COMPARE th?c hi?n so sánh, n?u dúng thì s? vào l?nh if.
////	  	 {
////	  		HD44780_Clear();
////	  		HD44780_SetCursor(0,0);
////				 HD44780_PrintStr("    MERHABA");
////	  	    HD44780_SetCursor(0,1);
////				 HD44780_PrintStr("     SALiH");
////	  	    HAL_Delay(1500);
////	  	    durum = 1 ;
////	  	 }
////	  	 else if((MFRC522_Compare(kart_no, kayitli_id3) == MI_OK )) //Hàm COMPARE th?c hi?n so sánh, n?u dúng thì s? vào l?nh if.
////	  		  	 {
////	  		  		HD44780_Clear();
////	  		  		HD44780_SetCursor(0,0);
////							 HD44780_PrintStr("    MERHABA");
////	  		  		HD44780_SetCursor(0,1);
////							 HD44780_PrintStr("     SAKiNE");
////	  		  	    HAL_Delay(1500);
////	  		  	    durum = 1 ;
////	  		  	 }
////	  	 else if((MFRC522_Compare(kart_no, kayitli_id4) == MI_OK )) //Hàm COMPARE th?c hi?n so sánh, n?u dúng thì s? vào l?nh if.
////	  		  	 {
////	  		  		HD44780_Clear();
////	  		  		HD44780_SetCursor(0,1);
////							 HD44780_PrintStr("    MERHABA");
////	  		  	    HD44780_SetCursor(0,1); 
////							 HD44780_PrintStr("      VELi");
////	  		  	    HAL_Delay(1500);
////	  		  	    durum = 1 ;
////	  		  	 }


////	  	 else
////	  	 {
////	  		 durum = 0 ;

////	  		 HD44780_Clear();
////	  	     HD44780_SetCursor(0,0); 
////				 HD44780_PrintStr("    KAYITSIZ");
////	  	     HD44780_SetCursor(0,1);
////				 HD44780_PrintStr("      KiSi");
////	  	     for(int d=0; d<6; d++) //Buzzer s? kêu 3 l?n, di?u này s? d?n d?n vi?c chuy?n d?i 6 l?n trong vòng l?p, vì v?y nó s? d?m d?n 6.
////	  	     {
////	  	    	 HAL_GPIO_TogglePin(buzer_GPIO_Port, buzer_Pin);
////	  	    	 HAL_Delay(500);
////	  	     }
////	  	     HAL_GPIO_WritePin(buzer_GPIO_Port, buzer_Pin, GPIO_PIN_RESET);

////	  		 for(int b=0 ; b<5 ; b++) //Buzzer s? kêu 3 l?n, di?u này s? d?n d?n vi?c chuy?n d?i 6 l?n trong vòng l?p, vì v?y nó s? d?m d?n 6.
////	  		 {
////	  			kart_no[b]= 0 ;
////	  		 }
////	  		 for(int c=0 ; c<16 ; c++) // khi không có ngu?i dang ký, n?i dung c?a m?ng d? li?u thô dã d?c du?c s? du?c d?t v? 0
////	  		 {
////	  		 okunan_ham[c]= 0 ;
////	  		 }
////              ana_erkan();
////	  	 }

////	  	      }
////	  	 }

////	  	  ////////////////////////////////////////////////////////////////////////////////

////	  	 if(durum==1)
////	  	 {	

////	  	HD44780_SetCursor(0,0);
////				 HD44780_PrintStr("KAPI ACILIYOR:)");
////	  	HD44780_SetCursor(0,1); 
////				 HD44780_PrintStr("  HOSGELDINIZ");
////	  	//int i=0;
////	  	  for(int i=0;i<=180;i++) // Servo quay t? 0 d?n 180 d? v?i kho?ng th?i gian 10 ms t?ng chút m?t.
////	  	  	  {
////	  	  	    Servo_Angle(i);
////	  	  		HAL_Delay(10);
////	  	  	  }
////	  	  HAL_Delay(5000);
////	  	  HD44780_Clear();
////	  	  HD44780_SetCursor(0,0); 
////						HD44780_PrintStr("KAPI KAPANIYOR:)");
////	  	  HD44780_SetCursor(0,1);
////						HD44780_PrintStr("   GULE GULE");
////	  	  for(int i=180;i>=0;i--) //Servo quay t? 0 d?n 180 d? v?i kho?ng th?i gian 10 ms t?ng chút m?t.
////	  	  	  {
////	  	  	    Servo_Angle(i);
////	  	  	  	HAL_Delay(10);
////	  	  	  }
////	  	 // HAL_Delay(2000);
////	  	  for(int c=0 ; c<16 ; c++) //khi có ngu?i dang ký, n?i dung c?a m?ng KART NO du?c d?t v? 0
////	  	 		 {
////	  	 			 okunan_ham[c]= 0 ;
////	  	 		 }
////	  	for(int e=0 ; e<5 ; e++) //khi có ngu?i dang ký, n?i dung c?a m?ng KART NO du?c d?t v? 0
////	  		  		 {
////	  		  			kart_no[e]= 0 ;
////	  		  		 }
////	  	   durum = 0 ;
////	  	   ana_erkan();
////	  	 }
//		else 
//		{	
//		HD44780_SetCursor(0,0);
//			HD44780_PrintStr("No id");
//			}
	  	  MFRC522_Halt(); // Hàm làm s?ch RFID sau khi d?c th? cu?i cùng

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
  * @brief SPI1 Initialization Function
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
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 355;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1799;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
	HAL_TIM_MspPostInit(&htim1);
}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspPostInit 0 */
 
  /* USER CODE END TIM1_MspPostInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PA8     ------> TIM1_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspPostInit 1 */

  /* USER CODE END TIM1_MspPostInit 1 */
  }

}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
}
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, buzer_Pin|GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = buzer_Pin|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Servo_Angle(int angle) //SERVO KÜTÜPHANESI
  {
  	if(angle<0)
  		angle=0;
  	if(angle>180)
  		angle=180;
  	angle=angle+45;

  	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,angle);

  }
void ana_erkan()// BU KART OKUTULMADIKÇA EKRANDA YAZACAK FONKSIYON WHILE DÖNGÜSÜNÜN IÇINDE KULLANDIK.
  {
	  HD44780_Clear();
		HD44780_SetCursor(0,0);
	  HD44780_PrintStr("   TEKNOLOJI    ");
		HD44780_SetCursor(0,1);
	  HD44780_PrintStr("   FAKULTESI    ");
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
