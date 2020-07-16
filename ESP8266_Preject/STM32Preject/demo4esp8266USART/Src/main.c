/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t flagchar;

uint8_t LED_HELLO[]="HELLO\r\n";

uint8_t buffdata;												//�洢���ڽ��յ����ַ�

uint8_t buffdatas[50];									//�洢���ڽ����ַ���

char buffdatas1[50];										//�������ƽ�� ��ֹ��û�н��������� �ͱ���������

uint8_t buffcount = 0;									//����ѭ������



char  deng_open[]="deng_open";					//����ָ��

char  deng_close[]="deng_close";				//�ص�ָ��

uint16_t flag = 5;											//���Ʊ�־λ
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED1_Close() HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
#define LED1_Open() HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
extern unsigned char BMP1[];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/***************ѡ����Ʊ�־λ***************/
void switch_flag()
{
				
							if(strstr(buffdatas1,deng_open) != NULL)  //deng_open ��  ��   ��־λ
						{
							flag =0;
							
						}
							else	if(strstr(buffdatas1,deng_close) != NULL)//deng_close ��  ��   ��־λ	
						{
							flag = 1;
							
						}

}

/***************�Զ��巢�ͺ���***************/
void SenData(uint8_t  * str)
{
	LED1_Open();  //����
	HAL_UART_Transmit(&huart1,str,strlen((const char *)str),2000); //��������
	LED1_Close(); //�ص�
}
/****************����ͼƬ****************/
void OLED_BMP()
{
	OLED_Clear(); 							//�����ʾ��
	OLED_DrawBMP(0,0,128,8,BMP1);	//xΪ0 yΪ0  ��128������   �� 8 ������            OLED12864
}
/****************�����ַ�****************/
void OLED_String()
{
	OLED_Clear();
	OLED_ShowString(10,0,(uint8_t *)"xiaotangstudio");
	OLED_ShowCHinese(27,3,0);
	HAL_Delay(500);
	OLED_ShowCHinese(42,3,1);
	HAL_Delay(500);
	OLED_ShowCHinese(57,3,2);
	HAL_Delay(500);
	OLED_ShowCHinese(72,3,3);
	HAL_Delay(500);
	OLED_ShowCHinese(87,3,4);
	OLED_ShowString(30,6,(uint8_t *)"2020-6-21");
}
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
	
	//OLED_Init(); //��ʼ��OLED
	
	//OLED_BMP();		//����ͼ|Ƭ

	//HAL_Delay(500);
	
	//OLED_String();	//��ʾ����

		SenData(LED_HELLO);
	HAL_UART_Receive_IT(&huart1,(uint8_t * )&buffdata,1);//���ý����ж�
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
			
			/*			switch(flag)
						{
					
							
								case 0: //��  ��
								LED1_Open();
								break;
								
								case 1: //��  ��
								LED1_Close();
								break;
						}*/
		
		
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

  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		if(huart->Instance == USART1)
			{
				if(buffcount >=50)
				{
					buffcount = 0;
					 memset(buffdatas,0,sizeof(buffdatas));
				//	SenData((uint8_t *)&buffdata);
				}
				else
				{
					
					if(flagchar== '#'||buffdata== '#') //�ж�ͷ�ǲ���  # ��
					{
						if(buffcount==0) //ֻ����һ��
						{
								flagchar= buffdata;  //��ͷ��#��������־λ
						}
						
						
						if( buffdata=='*') //�ж�β�ǲ� * ��
						{
							
							
							SenData(buffdatas);  //�����յ�������
							
							while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
							strcpy(buffdatas1,(char *)buffdatas);
							
							
							switch_flag();
							
							
							flagchar = '0';  // ���ͷ
							buffcount = 0; //������ݼ���
							memset(buffdatas,0x00,sizeof(buffdatas)); //�������
						
							HAL_UART_Receive_IT(&huart1,(uint8_t *)&buffdata,1); //�ٴ��������ڽ���
							return;
						}
						//��һ�ν��� ��Ϊ��һ�� # �� ���Բ�����
							if(buffcount>0) //�ж��ǲ��ǵڶ��ν���
							{
									buffdatas[buffcount-1] = buffdata; //������
						
							}
							buffcount++;//������++
					}	
				
					
				}
				
				HAL_UART_Receive_IT(&huart1,(uint8_t *)&buffdata,1);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
