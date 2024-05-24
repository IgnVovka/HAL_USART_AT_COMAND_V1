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
#include "stdio.h"
#include "string.h"
//#include <iostream>
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
//const char string[]={"AT+SPD"};
//char *str_array[]={"AT+SPD","AT+SPD=?","AT+SPD="};
const char str_array[12][20]={
		"AT+SPD",
		"AT+LNOPEN",
		"AT+LNHLOPEN",
        "AT+CURERRLOCK1",
        "AT+CURERRLOCK2", 
        "AT+CURERRDRIVE1", 
        "AT+CURERRDRIVE2", 
        "AT+CURERRDRIVE3", 
        "AT+CURERRDRIVE4", 
        "AT+CURERRTIME",
        "AT+STOTIMELOCK", 
        "AT+STOTIMEDRIVE" 
    };
const char str_array1[12][20]={
		"AT+SPD=?",
		"AT+LNOPEN=?",
		"AT+LNHLOPEN=?",
        "AT+CURERRLOCK1=?",
        "AT+CURERRLOCK2=?", 
        "AT+CURERRDRIVE1=?", 
        "AT+CURERRDRIVE2=?", 
        "AT+CURERRDRIVE3=?", 
        "AT+CURERRDRIVE4=?", 
        "AT+CURERRTIME=?",
        "AT+STOTIMELOCK=?", 
        "AT+STOTIMEDRIVE=?" 
    };
const char str_array2[12][20]={
		"AT+SPD?",
		"AT+LNOPEN?",
		"AT+LNHLOPEN?",
        "AT+CURERRLOCK1?",
        "AT+CURERRLOCK2?", 
        "AT+CURERRDRIVE1?", 
        "AT+CURERRDRIVE2?", 
        "AT+CURERRDRIVE3?", 
        "AT+CURERRDRIVE4?", 
        "AT+CURERRTIME?",
        "AT+STOTIMELOCK?", 
        "AT+STOTIMEDRIVE?" 
    };
const char str_array3[12][20]={
		"AT+SPD=",
		"AT+LNOPEN=",
		"AT+LNHLOPEN=",
        "AT+CURERRLOCK1=",
        "AT+CURERRLOCK2=", 
        "AT+CURERRDRIVE1=", 
        "AT+CURERRDRIVE2=", 
        "AT+CURERRDRIVE3=", 
        "AT+CURERRDRIVE4=", 
        "AT+CURERRTIME=",
        "AT+STOTIMELOCK=", 
        "AT+STOTIMEDRIVE=" 
    };
int t;
char str[20];//для сканирования строк
char p[]={""};//параметры, которые может принимать команда
char v[]={""};//текущее значение и для записи
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void parametrs(char*,int);
void current_value(char*);
void new_value(char*);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY);
	return ch;
}
int fgetc(FILE *f)
{
	uint8_t ch;
	HAL_UART_Receive( &huart1,(uint8_t*)&ch,1, HAL_MAX_DELAY );
	return ch;
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  printf("Enter AT command\r\n");
  while (1)
  {
    /* USER CODE END WHILE */
    scanf("%s",str);
    printf("You enter AT command: %s\r\n",str);
    for(int i=0;i<12;i++)
    {
      //if(strcmp(str,str_array[i])==0)// '\0'
       // t=strcmp(str,str_array[i]);
        if(!strcmp(str,str_array[i]))
        {
            //printf("t=%d, i=%d\r\n",t,i);
            printf("OK\r\n");
        }
      /*if(strchr(str,'?')!=0)//если строка содержит символ
            printf("String keep symbol %c\n",'?');
      if(strchr(str,'=')!=0)//если строка содержит символ
            printf("String keep symbol %c\n",'=');*/
    }
    for(int j=0;j<12;j++)
    {
      if(strcmp(str,str_array1[j])==0)// "=?"
          parametrs(str,j);  
    }
    for(int k=0;k<12;k++)
    {
      if(strcmp(str,str_array2[k])==0)//'?'
          current_value(str);  
    }
    for(int l=0;l<12;l++)
    {
      if(strcmp(str, str_array3[l])==0)//'='
          new_value(str);  
    }
    printf("Enter AT command\r\n");
      /*if(strchr(str,'?')!=0)//если строка содержит символ
          printf("String keep symbol %c\n",'?');
      if(strchr(str,'=')!=0)//если строка содержит символ
          printf("String keep symbol %c\n",'=');*/
      //if((strchr(str,'=')&&strchr(str,'?'))!=0)//если строка содержит символ
      //{
         //if(strchr(str,'?')!=0)//если строка содержит символ
            // printf("String keep symbol %c %c\n",'=','?');
      //}
   }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */

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
void parametrs(char *s,int j)
{
    s+=2;//удаляем первые два символа
    s[strlen(s)-2]='\0';//удаляем последние два символа
    printf("%s: ",s);
    switch(j)
    {
        case 0: 
            printf("(1 2 3 4)\r\n");
            break;
        case 1: 
            printf("(5 6 7 8)\r\n");
            break;
        case 2: 
            printf("(9 10 11 12)\r\n");
            break;
        case 3: 
            printf("(13 14 15 16)\r\n");
            break;
        case 4: 
            printf("(17 18 19 20)\r\n");
            break;
        case 5: 
            printf("(21 22 23 24)\r\n");
            break;
        case 6: 
           printf("(25 26 27 28)\r\n");
            break;
        case 7: 
            printf("(29 30 31 32)\r\n");
            break;
        case 8: 
            printf("(33 34 35 36)\r\n");
            break;
        case 9: 
            printf("(37 38 39 40)\r\n");
            break;
        case 10: 
            printf("(41 42 43 44)\r\n");
            break;
        case 11: 
            printf("(45 46 47 48)\r\n");
            break;    
        default: 
            printf("default\r\n");
            break;
    }
    //char *pos,*pos1;
    //pos=strchr(s,'?');//ищем символ '?' в строке
    //pos1=strchr(s,'=');//ищем символ '=' в строке
    //printf("%s%s",pos,pos1);
    //for(int i=*pos;i<strlen(s);++i)
    //s[i]=s[i+1];//мы не можем удалить символ, но можем заменить на следующий
}
void current_value(char *s)
{
	s+=2;//удаляем первые два символа
    s[strlen(s)-1]='\0';//удаляем последний  символ
    printf("%s: %s\r\n",s,v);
}
void new_value(char *s)
{
    printf("Enter new value\r\n");
    scanf("%s",v);
    printf("Value=%s\r\n",v);	
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
