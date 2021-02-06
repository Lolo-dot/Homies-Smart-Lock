#include "main.h"           //Main Header File
#include "stm32f1xx_hal.h"  //Hal drivers included for stm32f103c8t
void SystemClock_Config(void);  //System clock Configuration
void Error_Handler(void);       //Error HAndler  
static void MX_GPIO_Init(void); //GPIO Initialization

int main(void)             //Main function
{
  //MCU Configuration
  //Reset of all peripherals, Initializes the Flash interface and the Systick
  HAL_Init();              

  //Configure the system clock 
  SystemClock_Config();     

  //Initialize all configured peripherals 
  MX_GPIO_Init();

  while (1)
  {
	if(HAL_GPIO_ReadPin(Ibutton_GPIO_Port, Ibutton_Pin)==GPIO_PIN_RESET)  //Check if button pressed
	HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin,GPIO_PIN_SET);          //If pressed Led Switch On
	else
	HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin,GPIO_PIN_RESET);	      //Else Led Switch Off
  }
}

void SystemClock_Config(void)           // System Clock Configuration
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;      //HSI oscillator used
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
   
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_GPIO_Init(void)                  //GPIO Initialization
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : Led_Pin */
  GPIO_InitStruct.Pin = Led_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;      //Led as Output
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(Led_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Ibutton_Pin */
  GPIO_InitStruct.Pin = Ibutton_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;         //Button as input
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Ibutton_GPIO_Port, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  while(1) 
  {
  } 
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
}
#endif
