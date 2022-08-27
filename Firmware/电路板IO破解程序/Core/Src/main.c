/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "dma.h"
#include "usart.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

    return ch;
}


const uint16_t Gpio_Pin_Array[]=
{
    GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,
    GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7,
    GPIO_PIN_8,GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11,
    GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};

const GPIO_TypeDef * Gpio_Port_Array[]=
{GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF};

void SetIOState(char port,uint8_t pin,uint8_t sta)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    switch(port)
    {
        case 'A':__HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case 'B':__HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case 'C':__HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case 'D':__HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case 'E':__HAL_RCC_GPIOE_CLK_ENABLE();
            break;
        case 'F':__HAL_RCC_GPIOF_CLK_ENABLE();
            break;
        #if 0
        case 'G':__HAL_RCC_GPIOG_CLK_ENABLE();
            break;
        case 'H':__HAL_RCC_GPIOH_CLK_ENABLE();
            break;
        case 'I':__HAL_RCC_GPIOI_CLK_ENABLE();
            break;
        case 'J':__HAL_RCC_GPIOJ_CLK_ENABLE();
            break;
        case 'K':__HAL_RCC_GPIOK_CLK_ENABLE();
            break;
        #endif
    }
    //HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : BEEP_Pin */
    GPIO_InitStruct.Pin = Gpio_Pin_Array[pin];
    if(sta)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        //printf("Set P%c%d Output\r\n",port,pin);
    }
    else
    {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        //printf("Set P%c%d Input\r\n",port,pin);
    }
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    switch(port)
    {
        case 'A':HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
            break;
        case 'B':HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            break;
        case 'C':HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
            break;
        case 'D':HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
            break;
        case 'E':HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
            break;
        case 'F':HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
            break;
        #if 0
        case 'G':HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
            break;
        case 'H':HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
            break;
        case 'I':HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
            break;
        case 'J':HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);
            break;
        case 'K':HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);
            break;
        #endif
    }
}

#define IO_OUT_H HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_SET)
#define IO_OUT_L HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET)
#define IO_READ  ((HAL_GPIO_ReadPin(BEEP_GPIO_Port,BEEP_Pin) == GPIO_PIN_SET) ? 1 : 0)

uint8_t CheckIO(char port,uint8_t pin)
{
    uint8_t res = 0;
    int i;
    SetIOState(port,pin,1);
    for(i=0;i<10;i++)
    {
//        if(i%2)
//        {
//            IO_OUT_H;
//        }
//        else
//        {
//            IO_OUT_L;
//        }
        if(i % 2)
        {
            switch(port)
            {
                case 'A':HAL_GPIO_WritePin(GPIOA, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'B':HAL_GPIO_WritePin(GPIOB, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'C':HAL_GPIO_WritePin(GPIOC, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'D':HAL_GPIO_WritePin(GPIOD, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'E':HAL_GPIO_WritePin(GPIOE, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'F':HAL_GPIO_WritePin(GPIOF, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                #if 0
                case 'G':HAL_GPIO_WritePin(GPIOG, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'H':HAL_GPIO_WritePin(GPIOH, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'I':HAL_GPIO_WritePin(GPIOI, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'J':HAL_GPIO_WritePin(GPIOJ, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                case 'K':HAL_GPIO_WritePin(GPIOK, Gpio_Pin_Array[pin],GPIO_PIN_SET);
                    break;
                #endif
            }
        }
        else
        {
            switch(port)
            {
                case 'A':HAL_GPIO_WritePin(GPIOA, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'B':HAL_GPIO_WritePin(GPIOB, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'C':HAL_GPIO_WritePin(GPIOC, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'D':HAL_GPIO_WritePin(GPIOD, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'E':HAL_GPIO_WritePin(GPIOE, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'F':HAL_GPIO_WritePin(GPIOF, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                #if 0
                case 'G':HAL_GPIO_WritePin(GPIOG, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'H':HAL_GPIO_WritePin(GPIOH, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'I':HAL_GPIO_WritePin(GPIOI, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'J':HAL_GPIO_WritePin(GPIOJ, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                case 'K':HAL_GPIO_WritePin(GPIOK, Gpio_Pin_Array[pin],GPIO_PIN_RESET);
                    break;
                #endif
            }
        }
        HAL_Delay(1);
        //if(HAL_GPIO_ReadPin((GPIO_TypeDef *)&Gpio_Port_Array[port - 'A'],Gpio_Pin_Array[pin]) == (i%2))
        if(IO_READ == (i%2))
        {
            res ++;
        }
    }
    if(res == 10)
        return 1;
    else
        return 0;
}

#define TEST_PORT_NUM 6
#define TEST_PIN_NUM  16

const uint8_t CheckPort[TEST_PORT_NUM][TEST_PIN_NUM]=
{
    {0,1,2,3,4,5,6,7,                   15},//GPIOA
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},//GPIOB
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},//GPIOC
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},//GPIOD
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},//GPIOE
    {    2,3,4,5,6,7,8,9,10,11,12,13,14,15},//GPIOF
};

uint8_t uart_temp;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t data = uart_temp;
    (void)data;
}

char *help_str[19]=
{
    "串口OLED使用帮助",
    "帧头:0xEE",
    "功能码:0x10~0xFF",
    "数据:0~0xFF",
    "帧尾:0xFF0xFC0xFF0xFF",
    "写缓存:0x14",
    "设置复位:0x16",
    "设置亮度:0x17",
    "设置显示方向:0x18",
    "画点:0x1E",
    "画线:0x1F",
    "画矩形:0x20",
    "画圆形:0x22",
    "显示字符串:0x23",
    "清屏:0x24",
    "填充:0x25",
    "版本:0x26",
    "帮助0x27",
    "使用中遇到任何问题请联系QQ:2773128204"
};

uint16_t run_idle_cnt = 0;
uint16_t user_idle_set = 0;
uint8_t sleep_flag = 0;

void test_write_mem(uint8_t x,uint8_t y,uint8_t mem)
{
    uint8_t ch[9];
    ch[0] = 0xEE;
    ch[1] = 0x14;
    ch[2] = x;
    ch[3] = y;
    ch[4] = mem;
    ch[5] = 0xFF;
    ch[6] = 0xFC;
    ch[7] = 0xFF;
    ch[8] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 9, 0xFF);
}

void test_oled_rst(uint8_t t)
{
    //reset time = t+10 ms 奇数清屏
    uint8_t ch[7];
    ch[0] = 0xEE;
    ch[1] = 0x16;
    ch[2] = t;
    ch[3] = 0xFF;
    ch[4] = 0xFC;
    ch[5] = 0xFF;
    ch[6] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 7, 0xFF);
}

void test_set_light(uint8_t l)
{
    uint8_t ch[7];
    ch[0] = 0xEE;
    ch[1] = 0x17;
    ch[2] = l;
    ch[3] = 0xFF;
    ch[4] = 0xFC;
    ch[5] = 0xFF;
    ch[6] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 7, 0xFF);
}

void test_set_dir(uint8_t d)
{
    uint8_t ch[7];
    ch[0] = 0xEE;
    ch[1] = 0x18;
    ch[2] = d%4;
    ch[3] = 0xFF;
    ch[4] = 0xFC;
    ch[5] = 0xFF;
    ch[6] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 7, 0xFF);
}

void test_draw_point(uint8_t x,uint8_t y,uint8_t color)
{
    uint8_t ch[9];
    ch[0] = 0xEE;
    ch[1] = 0x1E;
    ch[2] = x;
    ch[3] = y;
    ch[4] = color;
    ch[5] = 0xFF;
    ch[6] = 0xFC;
    ch[7] = 0xFF;
    ch[8] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 9, 0xFF);
}

void test_draw_line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
    uint8_t ch[11];
    ch[0] = 0xEE;
    ch[1] = 0x1F;
    ch[2] = x1;
    ch[3] = y1;
    ch[4] = x2;
    ch[5] = y2;
    ch[6] = color;
    ch[7] = 0xFF;
    ch[8] = 0xFC;
    ch[9] = 0xFF;
    ch[10] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 11, 0xFF);
}

void test_draw_rect(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
    uint8_t ch[11];
    ch[0] = 0xEE;
    ch[1] = 0x20;
    ch[2] = x1;
    ch[3] = y1;
    ch[4] = x2;
    ch[5] = y2;
    ch[6] = color;
    ch[7] = 0xFF;
    ch[8] = 0xFC;
    ch[9] = 0xFF;
    ch[10] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 11, 0xFF);
}

void test_draw_cicle(uint8_t x1,uint8_t y1,uint8_t r,uint8_t color)
{
    uint8_t ch[10];
    ch[0] = 0xEE;
    ch[1] = 0x22;
    ch[2] = x1;
    ch[3] = y1;
    ch[4] = r;
    ch[5] = color;
    ch[6] = 0xFF;
    ch[7] = 0xFC;
    ch[8] = 0xFF;
    ch[9] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 10, 0xFF);
}

void test_draw_fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
    uint8_t ch[11];
    ch[0] = 0xEE;
    ch[1] = 0x25;
    ch[2] = x1;
    ch[3] = y1;
    ch[4] = x2;
    ch[5] = y2;
    ch[6] = color;
    ch[7] = 0xFF;
    ch[8] = 0xFC;
    ch[9] = 0xFF;
    ch[10] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 11, 0xFF);
}

void test_draw_str(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color,char *str)
{
    uint8_t ch[7];
    ch[0] = 0xEE;
    ch[1] = 0x23;
    ch[2] = x1;
    ch[3] = y1;
    ch[4] = x2;
    ch[5] = y2;
    ch[6] = color;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 7, 0xFF);
    printf("%s",str);
    ch[0] = 0x00;
    ch[1] = 0xFF;
    ch[2] = 0xFC;
    ch[3] = 0xFF;
    ch[4] = 0xFF;
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 5, 0xFF);
}
#define DELAY 10

void CheckBoardIO(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = BEEP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStruct);
    
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<16;j++)
        {
            if((j>0) && (CheckPort[i][j] == 0))
                continue;
            if(CheckIO(i+'A',CheckPort[i][j]) == 1)
            {
                if(0)
                {
                    printf("P%c%d\r\n",i+'A',CheckPort[i][j]);
                }
                else
                {
                    char buf[32];
                    sprintf(buf,"P%c%d  ",i+'A',CheckPort[i][j]);
                    test_draw_str(0,0,100,16,16,buf);
                }
            }
        }
    }
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("init\r\n");
    int i;
    for(i=0; i<100; i++)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
        HAL_Delay(2);
    }
//    int j;
//    for(i=0;i<6;i++)
//    {
//        for(j=0;j<16;j++)
//        {
//            printf("d[%d][%2d]:%2d",i,j,CheckPort[i][j]);
//        }
//        printf("\r\n");
//    }
    
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        CheckBoardIO();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
