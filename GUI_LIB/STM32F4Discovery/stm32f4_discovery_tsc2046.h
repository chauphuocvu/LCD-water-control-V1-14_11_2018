#ifndef	__TSC2046
#define	__TSC2046
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "graphicObject.h"

#define THRESHOLD 2   
typedef	struct POINT 
{
   uint16_t x;
   uint16_t y;
}Coordinate;


typedef struct Matrix_t 
{						
float 			An,  
            Bn,     
            Cn,   
            Dn,    
            En,    
            Fn,     
            Divider ;
} Matrix ;

/* Private variables ---------------------------------------------------------*/

//extern Matrix matrix ;

extern	__IO uint8_t touch_done;
extern	__IO uint16_t XCoordinate, YCoordinate;
#define SPI_PORT                  SPI2
#define SPI_PORT_CLOCK            RCC_APB1Periph_SPI2
#define SPI_PORT_CLOCK_INIT       RCC_APB1PeriphClockCmd
 
#define SPI_SCK_PIN              GPIO_Pin_10
#define SPI_SCK_GPIO_PORT        GPIOB
#define SPI_SCK_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define SPI_SCK_SOURCE           GPIO_PinSource10
#define SPI_SCK_AF               GPIO_AF_SPI2
 
#define SPI_MOSI_PIN             GPIO_Pin_15
#define SPI_MOSI_GPIO_PORT       GPIOB
#define SPI_MOSI_GPIO_CLK        RCC_AHB1Periph_GPIOB
#define SPI_MOSI_SOURCE          GPIO_PinSource15
#define SPI_MOSI_AF              GPIO_AF_SPI2

#define SPI_MISO_PIN             GPIO_Pin_14
#define SPI_MISO_GPIO_PORT       GPIOB
#define SPI_MISO_GPIO_CLK        RCC_AHB1Periph_GPIOB
#define SPI_MISO_SOURCE          GPIO_PinSource14
#define SPI_MISO_AF              GPIO_AF_SPI2



/* Private define ------------------------------------------------------------*/
/* AD通道选择命令字和工作寄存器 */
#define	CHX 	0x90 	/* 通道Y+的选择控制字 */	
#define	CHY 	0xd0	/* 通道X+的选择控制字 */
#define	REFOFF 	0x82	/* 通道X+的选择控制字 */

//#define TP_CS(a)	if (a)	\
//					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
//					else		\
//					GPIO_ResetBits(GPIOB,GPIO_Pin_12);
					
#define TP_INT_IN   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)
					

//extern Matrix matrix ;
extern uint16_t               LCD_Height;
extern uint16_t               LCD_Width;

void TP_Init(void) ;
void WR_CMD (uint8_t cmd);
Coordinate *Read_tsc2046(void);
void TouchPanel_Calibrate(void);
					
uint32_t	getTouchPoint(void);
//void DrawCross(uint16_t Xpos,uint16_t Ypos);
uint32_t	saveCalibrationData(void);
uint32_t	readCalibrationValue(void);					
#endif
