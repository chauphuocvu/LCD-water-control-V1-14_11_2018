/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM324xx_LCD_H
#define __STM324xx_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery_user.h"
#include "fonts.h"
#include "SSD1963_Configuration.h"
//#include "graphicObjectTypes.h"
//#include "graphicObject.h"

	 
/** @defgroup STM3210E_EVAL_LCD_Private_TypesDefinitions
  * @{
  */ 
typedef struct 
{
  int16_t X;
  int16_t Y;
} Point, * pPoint;

/** 
  * @brief  LCD_bool enumeration definition  
  */
typedef enum 
{
   LCD_FALSE = 0,
   LCD_TRUE = !LCD_FALSE
} LCD_bool;
/**
  * @}
  */ 
/** @defgroup STM324xG_EVAL_LCD_Private_Defines
  * @{
  */ 
/* LCD /CS is NE1 (HADDR[27:26]=00), /RS is A23 (HADDR[24]=1 for RAM addr) - Bank1 NOR/SRAM 4 */
#define LCD_REG_BASE           ((uint32_t)(0x60000000 ))
#define LCD_RAM_BASE           ((uint32_t)(0x61000000 ))
/* define LCD_Write_Command */
#define LCD_REG               (*((__IO uint16_t *) LCD_REG_BASE))
#define LCD_WriteCmd(Cmd)			LCD_REG = Cmd
/* define LCD_Write_Data */
#define LCD_RAM        				(*((__IO uint16_t *) LCD_RAM_BASE))
#define	LCD_WriteRAM(Data)		LCD_RAM = Data

/** 
  * @brief  LCD color  
  */ 

/*********************************************************************
* Macros: RGB565CONVERT(red, green, blue)
*
* Overview: Converts true color into 5:6:5 RGB format.
*
* PreCondition: none
*
* Input: Red, Green, Blue components.
*
* Output: 5 bits red, 6 bits green, 5 bits blue color.
*
* Side Effects: none
*
********************************************************************/
#define RGB565CONVERT(red, green, blue) (u16) (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3))
    
/*********************************************************************
* Overview: Some basic colors definitions.
*********************************************************************/
#define BLACK               RGB565CONVERT(0,    0,      0)
#define BRIGHTBLUE          RGB565CONVERT(0,    0,      255)
#define BRIGHTGREEN         RGB565CONVERT(0,    255,    0)
#define BRIGHTCYAN          RGB565CONVERT(0,    255,    255)
#define BRIGHTRED           RGB565CONVERT(255,  0,      0)
#define BRIGHTMAGENTA       RGB565CONVERT(255,  0,      255)
#define BRIGHTYELLOW        RGB565CONVERT(255,  255,    0)
#define BLUE                RGB565CONVERT(0,    0,      128)
#define GREEN               RGB565CONVERT(0,    128,    0)
#define CYAN                RGB565CONVERT(0,    128,    128)
#define RED                 RGB565CONVERT(128,  0,      0)
#define MAGENTA             RGB565CONVERT(128,  0,      128)
#define BROWN               RGB565CONVERT(255,  128,    0)
#define LIGHTGRAY           RGB565CONVERT(128,  128,    128)
#define DARKGRAY            RGB565CONVERT(64,   64,     64)
#define LIGHTBLUE           RGB565CONVERT(128,  128,    255)
#define LIGHTGREEN          RGB565CONVERT(128,  255,    128)
#define LIGHTCYAN           RGB565CONVERT(128,  255,    255)
#define LIGHTRED            RGB565CONVERT(255,  128,    128)
#define LIGHTMAGENTA        RGB565CONVERT(255,  128,    255)
#define YELLOW              RGB565CONVERT(255,  255,    128)
#define WHITE               RGB565CONVERT(255,  255,    255)
                            
#define GRAY0       	    	RGB565CONVERT(224,  224,    224)
#define GRAY1         	    RGB565CONVERT(192,  192,    192)   
#define GRAY2               RGB565CONVERT(160,  160,    160)   
#define GRAY3               RGB565CONVERT(128,  128,    128)
#define GRAY4               RGB565CONVERT(96,   96,     96)
#define GRAY5               RGB565CONVERT(64,   64,     64)
#define GRAY6	            	RGB565CONVERT(32,   32,     32)

/** 
  * @brief LCD font 
  */ 
#define LCD_BIG_FONT      		Font16x24
#define LCD_SMALL_FONT				Font8x8

/** 
  * @brief  LCD Vertical Direction 
  */ 
#define	TOPTODOWN								 0x00
#define	DOWNTOTOP								 0x01
/** 
  * @brief  LCD Direction  
  */ 
#define LCD_DIR_HORIZONTAL       0x00
#define LCD_DIR_VERTICAL         0x01

/** 
  * @brief  LCD Size (Width and Height)  480x272
  */ 
#define LCD_PIXEL_WIDTH          0x1E0
#define LCD_PIXEL_HEIGHT         0X110


/**
  * @}
  */ 

void STM324xG_LCD_Init(void);
void STM324xG_LCD_Reset(void);
void LCD_CtrlLinesConfig(void);
void LCD_FSMCConfig(void);

void LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor); 
void LCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor);
void LCD_SetTextColor(__IO uint16_t Color);
void LCD_SetBackColor(__IO uint16_t Color);
void LCD_SetFont(sFONT *fonts);
sFONT *LCD_GetFont(void);

void LCD_SetArea(u16 start_x, u16 start_y, u16 end_x, u16 end_y);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_SetBacklight(u8 intensity);
void LCD_SetTearingCfg(bool state, bool mode);
void     SSD1963_PutPixel(u16 x, u16 y);
uint16_t SSD1963_GetPixel(u16 x, u16 y);
void LCD_ClearLine(uint16_t Line);
void LCD_Clear(uint16_t Color);

void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c);
void LCD_DrawCharTransparent(uint16_t Xpos, uint16_t Ypos, const uint16_t *c); /* 16bit char */
void LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii);
void LCD_DisplayCharVertical(uint16_t Line, uint16_t Column, uint8_t Ascii,uint16_t top_down);
void LCD_DisplayCharVerticalTransparent(uint16_t Line, uint16_t Column, uint8_t Ascii,uint16_t top_down);
void LCD_DisplayCharTransparent(uint16_t Line, uint16_t Column, uint8_t Ascii);
void LCD_DisplayStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr);
void LCD_DisplayAdjStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr, LCD_bool Transparent_Flag);
void LCD_DisplayAdjStringLineVertical(uint16_t Line, uint16_t Column, uint8_t *ptr, LCD_bool Transparent_Flag, uint16_t top_down);

void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction);
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos,  uint16_t Width,uint16_t Height);
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height,uint16_t color);
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
//void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius,uint16_t color);
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void LCD_DrawMonoBMP(const uint8_t *Pict, uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width);
//void LCD_DrawColorBMP(uint8_t* ptrBitmap, uint16_t Xpos_Init, uint16_t Ypos_Init);

void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_PolyLine(pPoint Points, uint16_t PointCount);
void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount);
void LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount);
void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount);
void LCD_FillPolyLine(pPoint Points, uint16_t PointCount);
/**
  * @}
  */ 

//#define Set_RST GPIO_SetBits(GPIOC,GPIO_Pin_10)
//#define Clr_RST GPIO_ResetBits(GPIOC,GPIO_Pin_10)


#ifdef USE_Delay
#include "main.h" 
  #define _delay_     Delay  /* !< User can provide more timing precise _delay_ function
                                   (with 10ms time base), using SysTick for example */
#else
  #define _delay_     delay      /* !< Default _delay_ function with less precise timing */
#endif

#endif /* __STM324xG_EVAL_LCD_H */
