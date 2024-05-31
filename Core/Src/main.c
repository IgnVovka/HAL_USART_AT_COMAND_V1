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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
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
volatile uint8_t UartReady=RESET;//флаг для чтения;
char readBuf[20];//буфер, где будут помещаться принятые байты
char writeBuf[20];
uint8_t rxbyte;//переменная для приёма по одному байту
uint8_t i=0;//инкремент для readBuf 
const char str_array[12][20]={
		"SPD",
		"LNOPEN",
		"LNHLOPEN",
        "CURERRLOCK1",
        "CURERRLOCK2", 
        "CURERRDRIVE1", 
        "CURERRDRIVE2", 
        "CURERRDRIVE3", 
        "CURERRDRIVE4", 
        "CURERRTIME",
        "STOTIMELOCK", 
        "STOTIMEDRIVE" 
    };//словарь
//int number;
int val_array[12]={1,2,3,4,5,6,7,8,9,10,11,12};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
char* readUserInput(void);
int check (void);
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
  /* USER CODE BEGIN 2 */
  /* Разрешение прерываний от USART1 */
   HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //UartReady=RESET;
  HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
  while (1)
  {
       if (UartReady==SET)
       {
           switch (check())
           {
               case 0:
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                    //if(readBuf[6]=='\r')
                       // sprintf(writeBuf, "%s\r\n", "Ok");
                    if(readBuf[6]!='=' && readBuf[6]!='?')
                        //if(readBuf[6]!='?')
                        sprintf(writeBuf, "%s", "Error\r\n");//передаём в массив writeBuf
                    if (readBuf[6]=='?'&& readBuf[7]=='\r')
                        //Выдать описание команды
                        //if(readBuf[7]=='\r') 
                        sprintf(writeBuf, "%s\r\n", "Connection speed");
                    else
                        sprintf(writeBuf, "%s\r\n", "Error");
                    if (readBuf[6]=='=')
                    {
                        if (readBuf[7]=='?')
                        {
                            //=?
                            //выдать текущее значение параметра
                            sprintf(writeBuf, "%d\r\n",val_array[0]);//передаём в массив writeBuf
                        }
                        else
                        {
                            //=
                            //присвоить новое значение
                            sscanf(&readBuf[7],"%d",&val_array[0]);
                            if(isdigit(readBuf[7]))                            
                                sprintf(writeBuf, "%d\r\n", val_array[0]);
                            else
                                 sprintf(writeBuf, "%s\r\n", "Error");
                        }
                    }
               break;
               case 1:  
                   /*sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                     if(readBuf[9]!='=' && readBuf[9]!='?')
                        //if(readBuf[6]!='?')
                        sprintf(writeBuf, "%s", "Error\r\n");//передаём в массив writeBuf
                    if (readBuf[9]=='?'&& readBuf[10]=='\r')
                        //Выдать описание команды
                        //if(readBuf[7]=='\r') 
                        sprintf(writeBuf, "%s\r\n", "Full opening distance");
                    else
                        sprintf(writeBuf, "%s\r\n", "Error");
                    if (readBuf[9]=='=')
                    {
                        if (readBuf[10]=='?')
                        {
                            //=?
                            //выдать текущее значение параметра
                            sprintf(writeBuf, "%d\r\n",val_array[1]);//передаём в массив writeBuf
                        }
                        else
                        {
                            //=
                            //присвоить новое значение
                            sscanf(&readBuf[10],"%d",&val_array[1]);
                            if(isdigit(readBuf[10]))                            
                                sprintf(writeBuf, "%d\r\n", val_array[1]);
                            else
                                 sprintf(writeBuf, "%s\r\n", "Error");
                        }
                    }*/
                    
               break;
               case 2:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 3:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 4:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 5:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 6:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 7:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 8:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 9:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 10:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               case 11:  
                   //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
               break;
               default: 
                   sprintf(writeBuf, "%s", "Error\r\n");//передаём в массив writeBuf
               break;
               
           }
           /*HAL_UART_Transmit_IT(&huart1, (uint8_t*)writeBuf, strlen(writeBuf));
           while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX ||
            HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX_RX);*/
           UartReady=RESET;//сбрасываем флаг 
           HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
           HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
       }
       
      /*
      if (UartReady==SET)//если флаг установлен
      {
          if(readBuf[0]=='A' && readBuf[1]=='T' && readBuf[2]=='+')
          {
                      for(int j=0;j<12;j++)
                      {
                        if((strstr(readBuf,str_array[j]))!=NULL)
                        {
                      //strstr(readBuf,str_array[0]);
                            sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                            HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
                        }                        
                      }
          }
          else
          {
              sprintf(writeBuf, "%s", "Error\r\n");//передаём в массив writeBuf
              HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
          }
          UartReady=RESET;//сбрасываем флаг 
          HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
      }
      
      */
      
    /* USER CODE END WHILE */
    
	//opt=readUserInput();
    //if(opt>0)
    //{
        //sprintf(msg, "%d", opt);
       // sprintf(writeBuf, "%s", opt);
        //UartReady = RESET;
       // HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
    //}
    /* USER CODE BEGIN 3 */
	
  /* USER CODE END 3 */
  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
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
}


/* USER CODE BEGIN 4 */

int check (void)
{
    if(readBuf[0] !='A' || readBuf[1]!='T' || readBuf[2]!='+') return (-1);
    for(int j=0;j<12;j++)
    {
        if((strstr(readBuf,str_array[j]))!=NULL)
            return (j);
    }
    return (-1);
}


char* readUserInput(void) 
{
    //int8_t retVal = -1;
    if(UartReady == SET) 
    {
        UartReady = RESET;    
        //while(i<sizeof(readBuf))
        //{
            //p=&readBuf[i];
            //HAL_UART_Receive_IT(&huart1, (uint8_t*)p, 1);     
            //if(readBuf[0]=='A')
                //if(readBuf[1]=='T')
                    //if(readBuf[2]=='+')
                        //break;
            //return p;
            //if(p=='OD') 
            //i++;           
        //}
    }
  //retVal = atoi(readBuf);//функция atoi преобразует строковые  числа в целые
    return 0;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) 
{
/* Установить флаг передачи: передача завершена */
   // UartReady = SET;
    readBuf[i++]=rxbyte;//принимаем побайтно
    if (i >= 20) //если буфер переполнился 
        i=0;//сбрасываем счётчик
    if (rxbyte=='\n') //если принятый байт символ перевода каретки
    {
        readBuf[i++] = '\0';//добавляем символ конца строки
        UartReady = SET; //устанавливаем флаг
        i=0;//сбрасываем счётчик        
        //HAL_UART_AbortReceive(&huart1);//прекращение приёма из UART
    }
    else 
        HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
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
