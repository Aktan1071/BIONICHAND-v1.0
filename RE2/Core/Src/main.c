/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Bluetooth modulumuze gelen degerler 8 bitlik degerlerdir ve tipide int 8bit tipindedir ve baslangic degeri 0 alinir. */
uint8_t RX_BUFFER[] = {0};
/* row ve col iic modullu ekran kontrolu icin satur sutun baslangicidir.*/
int row=0;
int col=0;
/* Buffer degeri bluetooth port degeri olarak sabit degisken tanimlanmistir.*/
#define BUFFER_LEN  1
/* iic modulunun kutuphanesi tanimlanmistir.*/
#include "i2c-lcd.h"
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* 0 ve 180 derece arasinda servo kontrolunu kisitlamak amaci ile fonksiyon yazilmistir. 45 degeri ise 500 ms dolu olan bir pwm sinyali olusturur ve oda 0 dereceye tekabul eder.*/
/* Servot1 tim1 uzerindeki pwm sinyal kontrol fonksiyonudur*/
/* Servot2 tim uzerindeki pwm sinyallerinin kontrol fonksiyonudur*/
void Servot1(int angle, uint8_t channel)
{
	if(angle<0)
		angle = 0;
	if(angle>180)
		angle = 180;
	angle = angle + 45;

	__HAL_TIM_SET_COMPARE(&htim1, channel, angle);
}

void Servot2(int angle, uint8_t channel)
{
	if(angle<0)
		angle = 0;
	if(angle>180)
		angle = 180;
	angle = angle + 45;

	__HAL_TIM_SET_COMPARE(&htim2, channel, angle);
}

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
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  /* Pwm sinyalleri baslatilmistir.*/
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  
  /* Bluetooth modulu uart uzerinden veri alimi baslatir.*/
  HAL_UART_Receive_IT(&huart1, RX_BUFFER, BUFFER_LEN);
  /* Lcd init lcd ekrani calistirir ve string ile string deger yazdirir.*/
  lcd_init ();
  lcd_send_string("BIONIC HAND v1.0");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* Bu kisimda pythondan veya btterminalden gonderilen char degeri cozumlenir ve gerekli servo elemanina aci degeri olarak iletilir ve ekrana matrisi yazdirilir.*/
  while (1)
  {
    /* USER CODE END WHILE */
	  lcd_put_cur(1, 0);
	      /* USER CODE END WHILE */
	  if(RX_BUFFER[0] == '0'){lcd_send_string("[0, 0, 0, 0, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == '1'){lcd_send_string("[1, 1, 1, 1, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}

	  //////////////////////////////

	  else if(RX_BUFFER[0] == 'q'){lcd_send_string("[1, 0, 0, 0, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'w'){lcd_send_string("[0, 1, 0, 0, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == '6'){lcd_send_string("[0, 0, 1, 0, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'r'){lcd_send_string("[0, 0, 0, 1, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 't'){lcd_send_string("[0, 0, 0, 0, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}

	  //////////////////////////////

	  else if(RX_BUFFER[0] == 'y'){lcd_send_string("[0, 1, 1, 1, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'u'){lcd_send_string("[1, 0, 1, 1, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'i'){lcd_send_string("[1, 1, 0, 1, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'o'){lcd_send_string("[1, 1, 1, 0, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'p'){lcd_send_string("[1, 1, 1, 1, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}

	  //////////////////////////////

	  else if(RX_BUFFER[0] == 'a'){lcd_send_string("[1, 1, 0, 0, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 's'){lcd_send_string("[0, 1, 1, 0, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'd'){lcd_send_string("[0, 0, 1, 1, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'f'){lcd_send_string("[0, 0, 0, 1, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'g'){lcd_send_string("[1, 0, 0, 0, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'h'){lcd_send_string("[1, 0, 0, 1, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'j'){lcd_send_string("[1, 0, 1, 0, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'k'){lcd_send_string("[0, 1, 0, 1, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'l'){lcd_send_string("[0, 1, 0, 0, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'z'){lcd_send_string("[0, 0, 1, 0, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}

	  //////////////////////////////

	  else if(RX_BUFFER[0] == 'x'){lcd_send_string("[0, 0, 1, 1, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'c'){lcd_send_string("[1, 0, 0, 1, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'v'){lcd_send_string("[1, 1, 0, 0, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'b'){lcd_send_string("[1, 1, 1, 0, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'n'){lcd_send_string("[0, 1, 1, 1, 0]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == 'm'){lcd_send_string("[0, 1, 1, 0, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == '2'){lcd_send_string("[0, 1, 0, 1, 1]");Servot1(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == '3'){lcd_send_string("[1, 0, 1, 0, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(0, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == '4'){lcd_send_string("[1, 0, 1, 1, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}
	  else if(RX_BUFFER[0] == '5'){lcd_send_string("[1, 1, 0, 1, 0]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(0, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(0, TIM_CHANNEL_4);}

	  //////////////////////////////
	  else{lcd_send_string("[1, 1, 1, 1, 1]");Servot1(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_1);Servot2(90, TIM_CHANNEL_2);Servot2(90, TIM_CHANNEL_3);Servot2(90, TIM_CHANNEL_4);continue;}
	  //else{continue;}
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 355;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1799;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* Bluetooth uart fonksiyonu baslatilmistir ve anlik olarak veri cekilir. RX_BUFFER degiskenine yazilir.*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart1.Instance)
    {
    HAL_UART_Receive_IT(&huart1, RX_BUFFER, BUFFER_LEN);
    }
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

