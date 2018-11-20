#include "stm32f4_discovery_LCD_SSD1963.h"
#include "fonts.h"
#include "SSD1963_CMD.h"
#include "SSD1963_Configuration.h"


/** @defgroup STM324xG_EVAL_LCD_Private_Defines
  * @{
  */

#define MAX_POLY_CORNERS   200
#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_LCD_Private_Macros
  * @{
  */
#define ABS(X)  ((X) > 0 ? (X) : -(X))     
/**
  * @}
  */ 
    
/** @defgroup STM324xG_EVAL_LCD_Private_Variables
  * @{
  */ 
	
static sFONT *LCD_Currentfonts;
/* Global variables to set the written text color */
static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;
  
/**
  * @}
  */ 


/** @defgroup STM324xG_EVAL_LCD_Private_FunctionPrototypes
  * @{
  */ 
#ifndef USE_Delay
static void delay(__IO uint32_t nCount);
#endif /* USE_Delay*/

static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed);


/**
  * @}
  */ 


/** @defgroup STM324xG_EVAL_LCD_Private_Functions
  * @{
  */ 



/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */
void STM324xG_LCD_Init(void)
{ 
/* Configure the LCD Control pins --------------------------------------------*/
  LCD_CtrlLinesConfig();

/* Configure the FSMC Parallel interface -------------------------------------*/
  LCD_FSMCConfig();

/* Reset LCD */
	STM324xG_LCD_Reset();
	
/* turn on Backlight */	
	On(LCD_BL);
}

/**
  * @brief  Configures LCD Control lines (FSMC Pins) in alternate function mode.
  * @param  None
  * @retval None
  */

void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);


	/*-- GPIO Configuration ------------------------------------------------------*/
  /* SRAM Data lines,  NOE(/RD) and NWE(/WR) configuration */
  /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_7 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 |GPIO_Pin_14 | GPIO_Pin_15; */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |GPIO_Pin_14 | GPIO_Pin_15 | 
																GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource0,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource1,  GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource5,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
// GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
//                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
//                                GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

// GPIO_PinAFConfig(GPIOE, GPIO_PinSource4 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 ,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 ,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 ,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);
	
	/* SRAM Address lines configuration (/RS)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOE, &GPIO_InitStructure);  
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_FSMC);    
	
	/* NE1 configuration (/CS)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);

  /* PE6 is connected to RST , configured as output */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6; 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOE, &GPIO_InitStructure);

/* PC10 is connected to RST , configured as output */
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_13; 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// PD13 - Backlight Control
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13; 
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* PE3 is connected to TE , configured as input */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
//	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1; 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/**
  * @brief  Configures the Parallel interface (FSMC) for LCD(Parallel mode)
  * @param  None
  * @retval None
  */
void LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  
	/* Enable FSMC clock */
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

/*-- FSMC Configuration ------------------------------------------------------*/
/*----------------------- SRAM Bank1 ----------------------------------------*/
  /* FSMC_Bank1_NORSRAM1 configuration */
  p.FSMC_AddressSetupTime = 15;
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime = 15;
  p.FSMC_BusTurnAroundDuration = 0;
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;
  /* Color LCD configuration ------------------------------------
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = NOR
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = Disable */

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   

  /* Enable FSMC NOR/SRAM Bank1 */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void STM324xG_LCD_Reset(void)
{
	On(LCD_RST);		
	delay(1);
	Off(LCD_RST);
	delay(100);
	On(LCD_RST);
	delay(100);
	
// 	LCD_WriteCmd(CMD_SOFT_RESET);				// Soft reset
// 	delay(5);

	LCD_WriteCmd(CMD_SET_PLL_MN);
	LCD_WriteRAM(0x23);
	LCD_WriteRAM(0x02);				// Divider M = 2, PLL = 360/(M+1) = 120MHz
	LCD_WriteRAM(0x04);				// Validate M and N values
	LCD_WriteCmd(CMD_PLL_START);				// Start PLL command
	LCD_WriteRAM(0x01);
	delay(1);
	LCD_WriteCmd(CMD_PLL_START);				// Start PLL command again
	LCD_WriteRAM(0x03);				// now, use PLL output as system clock	
	LCD_WriteCmd(CMD_SOFT_RESET);				// Soft reset
	delay(10);
	
	LCD_WriteCmd(CMD_SET_PCLK);
	LCD_WriteRAM(0x01);
//	LCD_WriteRAM(0x48);
//	LCD_WriteRAM(0x9E);
	LCD_WriteRAM(0x33);
	LCD_WriteRAM(0x33);
	
	LCD_WriteCmd(CMD_SET_PANEL_MODE);
	
	LCD_WriteRAM(0x20);				// set 24-bit mode
	LCD_WriteRAM(0x00);				// set TTL mode
	LCD_WriteRAM((HDP>>8)&0X00FF); //Set panel size
	LCD_WriteRAM(HDP&0X00FF);
	LCD_WriteRAM((VDP>>8)&0X00FF);
	LCD_WriteRAM(VDP&0X00FF);
	LCD_WriteRAM(0x00);				//RGB sequence	
	//delay(5);
	
	
	LCD_WriteCmd(CMD_SET_HOR_PERIOD);
	LCD_WriteRAM((HT>>8)&0X00FF);	
	LCD_WriteRAM(HT&0X00FF);
	LCD_WriteRAM((HPS>>8)&0X00FF);
	LCD_WriteRAM(HPS&0X00FF);
	LCD_WriteRAM(HPW);
	LCD_WriteRAM((LPS>>8)&0X00FF);
	LCD_WriteRAM(LPS&0X00FF);
	LCD_WriteRAM(0x0000);	
// 	LCD_WriteRAM((HT-1)>>8);	
// 	LCD_WriteRAM(HT-1);

// 	LCD_WriteRAM((HPS-1)>>8);
// 	LCD_WriteRAM(HPS-1);
// 	LCD_WriteRAM(DISP_HOR_PULSE_WIDTH-1);
// 	LCD_WriteRAM(0x00);
// 	LCD_WriteRAM(0x00);
// 	LCD_WriteRAM(0x00);
	
	LCD_WriteCmd(CMD_SET_VER_PERIOD);
	LCD_WriteRAM((VT>>8)&0X00FF);
	LCD_WriteRAM(VT&0X00FF);
	LCD_WriteRAM((VPS>>8)&0X00FF);
	LCD_WriteRAM(VPS&0X00FF);
	LCD_WriteRAM(VPW);
	LCD_WriteRAM((FPS>>8)&0X00FF);
	LCD_WriteRAM(FPS&0X00FF);
// 	LCD_WriteRAM((VT-1)>>8);
// 	LCD_WriteRAM(VT-1);
// 	
// 	LCD_WriteRAM((VSP-1)>>8);
// 	LCD_WriteRAM(VSP-1);
// 	LCD_WriteRAM(DISP_VER_PULSE_WIDTH-1);
// 	LCD_WriteRAM(0x00);
// 	LCD_WriteRAM(0x00);

	//--------------------------------
	LCD_WriteCmd(CMD_SET_GPIO_CONF);
	LCD_WriteRAM(0x000F);
	LCD_WriteRAM(0x0001);
	
	LCD_WriteCmd(CMD_SET_GPIO_VAL);
	LCD_WriteRAM(0x0001);
	
	LCD_WriteCmd(CMD_SET_ADDR_MODE);
	LCD_WriteRAM(0x0008);
	//--------------------------------

//	LCD_WriteCmd(CMD_EXIT_SLEEP);
	LCD_WriteCmd(CMD_SET_PIXEL_FORMAT);
//	LCD_WriteRAM(0x55); 				// set 16bpp
	LCD_WriteRAM(0x50); 				// set 16bpp
	
	LCD_WriteCmd(CMD_SET_DATA_INTERFACE);
	LCD_WriteRAM(0x03);				//16-bit(565 format) data for 16bpp PIC32MX only
		
	LCD_WriteCmd(CMD_SET_POST_PROC);
	LCD_WriteRAM(0x40);
	LCD_WriteRAM(0x80);
	LCD_WriteRAM(0x40);
	LCD_WriteRAM(0x01);
	delay(1);
	
	LCD_WriteCmd(CMD_SET_TEAR_ON);
	LCD_WriteRAM(0x00);
	
	LCD_WriteCmd(CMD_ON_DISPLAY);				// Turn on display; show the image on display	
	
}

/**
  * @brief  Displays a pixel.
  * @param  x: pixel x.
  * @param  y: pixel y.  
  * @retval None
  */
void SSD1963_PutPixel(u16 x, u16 y)
{ 	
	LCD_SetArea(x,y,(LCD_PIXEL_WIDTH - 1),(LCD_PIXEL_HEIGHT - 1));
	LCD_WriteCmd(CMD_WR_MEMSTART);
	LCD_WriteRAM(TextColor);
}

/**
  * @brief  Read a pixel.
  * @param  x: pixel x.
  * @param  y: pixel y.  
  * @retval None
  */
uint16_t SSD1963_GetPixel(u16 x, u16 y)
{
	__IO uint16_t tmp = 0;
	LCD_SetArea(x,y,(LCD_PIXEL_WIDTH - 1),(LCD_PIXEL_HEIGHT - 1));
	LCD_WriteCmd(CMD_RD_MEMSTART);
	tmp = LCD_RAM;
	return tmp;
}

/*********************************************************************
* Function:  LCD_SetArea(start_x,start_y,end_x,end_y)
*
* PreCondition: SetActivePage(page)
*
* Input: start_x, end_x	- start column and end column
*		 start_y,end_y 	- start row and end row position (i.e. page address)
*
* Output: none
*
* Side Effects: none
*
* Overview: defines start/end columns and start/end rows for memory access
*			from host to SSD1963
* Note: none
********************************************************************/
void LCD_SetArea(u16 start_x, u16 start_y, u16 end_x, u16 end_y)
{
//	start_y =  start_y;
//	end_y   =  end_y;
	LCD_WriteCmd(CMD_SET_COLUMN);
	LCD_WriteRAM(start_x>>8);
	LCD_WriteRAM(start_x);
	LCD_WriteRAM(end_x>>8);
	LCD_WriteRAM(end_x);

	LCD_WriteCmd(CMD_SET_PAGE);
	LCD_WriteRAM(start_y>>8);
	LCD_WriteRAM(start_y);
	LCD_WriteRAM(end_y>>8);
	LCD_WriteRAM(end_y);
}
void LCD_SetBacklight(u8 intensity)
{
	LCD_WriteCmd(0xBE);			// Set PWM configuration for backlight control
	LCD_WriteRAM(0x0E);			// PWMF[7:0] = 2, PWM base freq = PLL/(256*(1+5))/256 = 
								// 300Hz for a PLL freq = 120MHz
	LCD_WriteRAM(intensity);		// Set duty cycle, from 0x00 (total pull-down) to 0xFF 
								// (99% pull-up , 255/256)
	LCD_WriteRAM(0x01);			// PWM enabled and controlled by host (mcu)
	LCD_WriteRAM(0x00);
	LCD_WriteRAM(0x00);
	LCD_WriteRAM(0x00);
}

/*********************************************************************
* Function:  void  SetTearingCfg(BOOL state, BOOL mode)
*
* Overview: This function enable/disable tearing effect
*
* PreCondition: none
*
* Input: 	BOOL state -	1 to enable
*							0 to disable
*			BOOL mode -		0:  the tearing effect output line consists
*								of V-blanking information only
*							1:	the tearing effect output line consists
*								of both V-blanking and H-blanking info.
* Output: none
*
* Note:
********************************************************************/
void LCD_SetTearingCfg(bool state, bool mode)
{
	if(state == 1)
	{
		LCD_WriteCmd(0x35);
		LCD_WriteRAM(mode&0x01);
	}
	else
	{
		LCD_WriteCmd(0x34);
	}
}

/**
  * @brief  Sets the LCD Text and Background colors.
  * @param  _TextColor: specifies the Text Color.
  * @param  _BackColor: specifies the Background Color.
  * @retval None
  */
void LCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor)
{
  TextColor = _TextColor; 
  BackColor = _BackColor;
}

/**
  * @brief  Gets the LCD Text and Background colors.
  * @param  _TextColor: pointer to the variable that will contain the Text Color.
  * @param  _BackColor: pointer to the variable that will contain the Background Color.
  * @retval None
  */
void LCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}

/**
  * @brief  Sets the Text color.
  * @param  Color: specifies the Text color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetTextColor(__IO uint16_t Color)
{
  TextColor = Color;
}

/**
  * @brief  Sets the Background color.
  * @param  Color: specifies the Background color code RGB(5-6-5).
  * @retval None
  */
void LCD_SetBackColor(__IO uint16_t Color)
{
  BackColor = Color;
}

/**
  * @brief  Sets the Text Font.
  * @param  fonts: specifies the font to be used.
  * @retval None
  */
void LCD_SetFont(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}

/**
  * @brief  Gets the Text Font.
  * @param  None.
  * @retval the used font.
  */
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}

/**
  * @brief  Clears the selected line.
  * @param  Line: the Line to be cleared.
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..n
  * @retval None
  */
void LCD_ClearLine(uint16_t Line)
{
  uint16_t refcolumn = 0;
  /* Send the string character by character on lCD */
  while (((refcolumn + 1)& 0xFFFF) <= (LCD_PIXEL_WIDTH - 1))
  {
    /* Display one character on LCD */
    LCD_DisplayChar(Line, refcolumn, ' ');
    /* Decrement the column position by 16 */
    refcolumn += LCD_Currentfonts->Width;
  }
}

/**
  * @brief  Clears the hole LCD.
  * @param  Color: the color of the background.
  * @retval None
  */
void LCD_Clear(uint16_t Color)
{

	u32 xcounter, ycounter;

	LCD_SetArea(0,0,LCD_PIXEL_WIDTH-1,LCD_PIXEL_HEIGHT-1);

	LCD_WriteCmd(CMD_WR_MEMSTART);
		for(ycounter=0;ycounter<LCD_PIXEL_WIDTH;ycounter++)
	{
		for(xcounter=0;xcounter<LCD_PIXEL_HEIGHT;xcounter++)
		{
			LCD_WriteRAM(Color);
		}
	} 
}

/**
  * @brief  Sets the cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position. 
  * @retval None
  */
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	LCD_SetArea(Xpos,Ypos, (Xpos + LCD_Currentfonts->Width -1), (Ypos + LCD_Currentfonts->Height -1));
}

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint32_t index = 0, i = 0;
  
  LCD_SetArea(Xpos, Ypos,Xpos + LCD_Currentfonts->Width -1,Ypos + LCD_Currentfonts->Height -1);
  LCD_WriteCmd(CMD_WR_MEMSTART); /* Prepare to write GRAM */
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  { 
    for(i = 0; i < LCD_Currentfonts->Width; i++)
    {
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
      {
        LCD_WriteRAM(BackColor);				
      }
      else
      {
        LCD_WriteRAM(TextColor);
      }
    }
  }
}

/**
  * @brief  Draws a transparent character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LCD_DrawCharTransparent(uint16_t Xpos, uint16_t Ypos, const uint16_t *c) /* 16bit char */
{
	  uint32_t index = 0, i = 0;

  for(index = 0; index < LCD_Currentfonts->Height; index++)
  { 
    for(i = 0; i < LCD_Currentfonts->Width; i++)
    {
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
      {			
      }
      else
      {
        SSD1963_PutPixel(Xpos + i,Ypos + index);
      }
    }
  }
}

/**
  * @brief  Draws a vertical character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
	* @param  top_down: vertical direction.
  * @retval None
  */
void LCD_DrawCharVertical(uint16_t Xpos, uint16_t Ypos, const uint16_t *c, uint16_t top_down)
{
  uint32_t index = 0, i = 0;
	
	LCD_WriteCmd(CMD_SET_ADDR_MODE);
 if (top_down == TOPTODOWN) 
 {	 
		LCD_WriteRAM(0x68);	
		LCD_SetArea(Xpos, Ypos,Xpos + LCD_Currentfonts->Height -1,Ypos + LCD_Currentfonts->Width -1);
 }
 else 
 {
	 LCD_WriteRAM(0xA8);	
	 LCD_SetArea(Xpos, Ypos - LCD_Currentfonts->Width + 1,Xpos + LCD_Currentfonts->Height -1,Ypos);
 }
  
  LCD_WriteCmd(CMD_WR_MEMSTART); /* Prepare to write GRAM */
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  { 
    for(i = 0; i < LCD_Currentfonts->Width; i++)
    {
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
      {
        LCD_WriteRAM(BackColor);				
      }
      else
      {
        LCD_WriteRAM(TextColor);
      }
    }
  }
	LCD_WriteCmd(CMD_SET_ADDR_MODE);	
	LCD_WriteRAM(0x08);	
}

/**
  * @brief  Draws a transparent vertical character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
	* @param  top_down: vertical direction.
  * @retval None
  */
void LCD_DrawCharVerticalTransparent(uint16_t Xpos, uint16_t Ypos, const uint16_t *c,uint16_t top_down) /* 16bit char */
{
	  uint32_t index = 0, i = 0;
	
		uint16_t	X,Y;
	
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  { 
    for(i = 0; i < LCD_Currentfonts->Width; i++)
    {
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
      {			
      }
      else
      {
				if ((top_down == TOPTODOWN) ) 
					{ 
						X = Xpos + LCD_Currentfonts->Height -1 - index; 
						Y = Ypos + i;
					}
				else 
					{
						X = Xpos + index; 
						Y = Ypos - i;
					}
        SSD1963_PutPixel(X,Y);			
      }
    }
  }
}

/**
  * @brief  Displays one character (16dots width, 24dots height).
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  Column: start column address.
  * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
  * @retval None
  */
void LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii)
{
  Ascii -= 32;
//  LCD_DrawChar( Column,Line * LCD_Currentfonts->Height, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
	LCD_DrawChar( Column,Line , &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}
void LCD_DisplayCharTransparent(uint16_t Line, uint16_t Column, uint8_t Ascii)
{
  Ascii -= 32;
//  LCD_DrawCharTransparent( Column,Line * LCD_Currentfonts->Height, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
	LCD_DrawCharTransparent( Column,Line, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}

void LCD_DisplayCharVertical(uint16_t Line, uint16_t Column, uint8_t Ascii,uint16_t top_down)
{
  Ascii -= 32;
//  LCD_DrawChar( Column,Line * LCD_Currentfonts->Height, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
	LCD_DrawCharVertical( Column,Line , &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height],top_down);
}
void LCD_DisplayCharVerticalTransparent(uint16_t Line, uint16_t Column, uint8_t Ascii,uint16_t top_down)
{
  Ascii -= 32;
//  LCD_DrawChar( Column,Line * LCD_Currentfonts->Height, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
	LCD_DrawCharVerticalTransparent( Column,Line , &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height],top_down);
}

/**
  * @brief  Displays a maximum of 20 char on the LCD.
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  *ptr: pointer to string to display on LCD.
  * @retval None
  */
void LCD_DisplayStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr)
{
  uint16_t refcolumn = Column;

  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (((refcolumn + 1) & 0xFFFF) <= (LCD_PIXEL_WIDTH - 1)))
  {
    /* Display one character on LCD */
    LCD_DisplayChar(Line, refcolumn,*ptr);
    /* Decrement the column position by 16 */
    refcolumn += LCD_Currentfonts->Width;
    /* Point on the next character */
    ptr++;
  }
}

void LCD_DisplayAdjStringLine(uint16_t Line, uint16_t Column, uint8_t *ptr, LCD_bool Transparent_Flag)
{
  uint32_t index = 0;

	uint16_t	refcolumn = Column;
  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (((refcolumn + 1) & 0xFFFF) <= (LCD_PIXEL_WIDTH - 1)))
  { /* Display one character on LCD */
		if (Transparent_Flag)	LCD_DisplayCharTransparent(Line, Column, *ptr);
		else
		LCD_DisplayChar( Line, Column, *ptr);
    
    /* Decrement the column position by GL_FontWidth */
    if ( *ptr == 'A' || *ptr == 'G' || *ptr == 'M' || *ptr == 'O' || *ptr == 'Q' || *ptr == 'X' || *ptr == 'm')
      Column += (LCD_Currentfonts->Width);
    else 
			if ( *ptr == 'i' || *ptr == 'I' || *ptr == 'l')	
				Column += (LCD_Currentfonts->Width - 5);
			else
      Column += (LCD_Currentfonts->Width - 1);
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    index++;
  }
}

void LCD_DisplayAdjStringLineVertical(uint16_t Line, uint16_t Column, uint8_t *ptr, LCD_bool Transparent_Flag, uint16_t top_down)
{
  uint32_t index = 0;

	uint16_t	refLine = Line;
	

  /* Send the string character by character on lCD */

while ((*ptr != 0))
{ /* Display one character on LCD */
	if (Transparent_Flag)	LCD_DisplayCharVerticalTransparent(refLine, Column,*ptr,top_down);
	else
		LCD_DisplayCharVertical( refLine, Column, *ptr,top_down);
    
	if (top_down == TOPTODOWN)
	{
    if ( *ptr == 'A' || *ptr == 'G' || *ptr == 'M' || *ptr == 'O' || *ptr == 'Q' || *ptr == 'X' || *ptr == 'm')
		{		
		         refLine += (LCD_Currentfonts->Width);
		}
    else 
			if ( *ptr == 'i' || *ptr == 'I' || *ptr == 'l')	
				refLine += (LCD_Currentfonts->Width - 5);
			else
      refLine += (LCD_Currentfonts->Width - 1);
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    index++;
  }
	else
	{
    if ( *ptr == 'A' || *ptr == 'G' || *ptr == 'M' || *ptr == 'O' || *ptr == 'Q' || *ptr == 'X' || *ptr == 'm')
		{		
		         refLine -= (LCD_Currentfonts->Width);
		}
    else 
			if ( *ptr == 'i' || *ptr == 'I' || *ptr == 'l')	
				refLine -= (LCD_Currentfonts->Width - 5);
			else
      refLine -= (LCD_Currentfonts->Width - 1);
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    index++;
  }
		
}
}

/**
  * @brief  Displays a line.
  * @param Xpos: specifies the X position.
  * @param Ypos: specifies the Y position.
  * @param Length: line length.
  * @param Direction: line direction.
  *   This parameter can be one of the following values: Vertical or Horizontal.
  * @retval None
  */
void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction)
{
	uint32_t i = 0;
		LCD_SetArea(Xpos,Ypos,(LCD_PIXEL_WIDTH - 1),(LCD_PIXEL_HEIGHT - 1));

  if(Direction == LCD_DIR_HORIZONTAL)
  {
    LCD_WriteCmd(CMD_WR_MEMSTART); /* Prepare to write GRAM */
    for(i = 0; i < Length; i++)
    {
      LCD_WriteRAM(TextColor);
    }
  }
  else
  {
    for(i = 0; i < Length; i++)
    {
      LCD_WriteCmd(CMD_WR_MEMSTART); /* Prepare to write GRAM */
      LCD_WriteRAM(TextColor);
      Ypos++;
      LCD_SetArea(Xpos,Ypos,(LCD_PIXEL_WIDTH - 1),(LCD_PIXEL_HEIGHT - 1));
    }
  }
}

/**
  * @brief  Displays a rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Height: display rectangle height.
  * @param  Width: display rectangle width.
  * @retval None
  */
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width)
{
  LCD_DrawLine(Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);
  LCD_DrawLine(Xpos, Ypos + Height, Width, LCD_DIR_HORIZONTAL);
  
  LCD_DrawLine(Xpos, Ypos, Height, LCD_DIR_VERTICAL);
  LCD_DrawLine(Xpos + Width - 1, Ypos , Height, LCD_DIR_VERTICAL);
}

/**
  * @brief  Displays a circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;/* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
		SSD1963_PutPixel(Xpos + CurX, Ypos + CurY);
		
		SSD1963_PutPixel(Xpos + CurX, Ypos - CurY);

    SSD1963_PutPixel(Xpos - CurX, Ypos + CurY);

    SSD1963_PutPixel(Xpos - CurX, Ypos - CurY);

    SSD1963_PutPixel(Xpos + CurY, Ypos + CurX);

    SSD1963_PutPixel(Xpos + CurY, Ypos - CurX);

    SSD1963_PutPixel(Xpos - CurY, Ypos + CurX);

    SSD1963_PutPixel(Xpos - CurY, Ypos - CurX);

    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;/* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    LCD_DrawLine(Xpos - CurY, Ypos + CurX, 2*(CurY),LCD_DIR_HORIZONTAL);
		
    LCD_DrawLine(Xpos - CurY, Ypos - CurX, 2*(CurY),LCD_DIR_HORIZONTAL);
		
		LCD_DrawLine(Xpos - CurX, Ypos + CurY, 2*(CurX),LCD_DIR_HORIZONTAL);
		
    LCD_DrawLine(Xpos - CurX, Ypos - CurY, 2*(CurX),LCD_DIR_HORIZONTAL);
		

    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

/**
  * @brief  Displays a mono-color picture.
  * @param  Pict: pointer to the picture array.
  * @retval None
  */
void LCD_DrawMonoBMP(const uint8_t *Pict, uint16_t Xpos_Init, uint16_t Ypos_Init, uint16_t Height, uint16_t Width)
{
  uint32_t index = 0, i = 0;

//	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	
	LCD_SetArea(Xpos_Init,Ypos_Init,Height - 1,Width -1);

	LCD_WriteCmd(CMD_WR_MEMSTART);
  for(index = 0; index < Height*Width/8; index++)
  {
    for(i = 0; i < 8; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        LCD_WriteRAM(BackColor);
      }
      else
      {
        LCD_WriteRAM(TextColor);

      }
    }
  }
}

/**
  * @brief  Copy 2 bytes from bitmap array to 16Bit buffer
  * @param  ptrBitmap - Bitmap pointer
  * @param  ptr16BitBuffer - 16Bit buffer to fill
  * @retval None
  */
void BmpBuffer16BitRead(uint16_t* ptr16BitBuffer, uint8_t* ptrBitmap)
{
  *ptr16BitBuffer = (*ptrBitmap) | ((*(ptrBitmap + 1)) << 8);
}
/**
  * @brief  Copy 4 bytes from bitmap array to 32Bit buffer
  * @param  ptrBitmap - Bitmap pointer
  * @param  ptr32BitBuffer - 32Bit buffer to fill
  * @retval None
  */
void BmpBuffer32BitRead(uint32_t* ptr32BitBuffer, uint8_t* ptrBitmap)
{
  *ptr32BitBuffer = 0;
  *ptr32BitBuffer = (*ptrBitmap);
  *ptr32BitBuffer += (*(ptrBitmap + 1)) << 8;
  *ptr32BitBuffer += (*(ptrBitmap + 2)) << 16;
  *ptr32BitBuffer += (*(ptrBitmap + 3)) << 24;
}


//void LCD_DrawColorBMP(uint8_t* ptrBitmap, uint16_t Xpos_Init, uint16_t Ypos_Init)
//{
//	uint32_t uDataAddr = 0, uBmpSize = 0;
//	uint32_t	width,height;
//  uint16_t uBmpData;
//	uint8_t		*startDataPtr;
//	uint8_t		*DataPtr;
//	int32_t		i,j;
//	
//  BmpBuffer32BitRead(&uBmpSize,  ptrBitmap + 2);
//  BmpBuffer32BitRead(&uDataAddr, ptrBitmap + 10);
//	BmpBuffer32BitRead(&width,  ptrBitmap + 0x12);
//	BmpBuffer32BitRead(&height, ptrBitmap + 0x16);
//	startDataPtr = ptrBitmap + uDataAddr;
//  
//  LCD_SetArea(Xpos_Init,Ypos_Init,Xpos_Init+width - 1,Ypos_Init+height - 1);
//	LCD_WriteCmd(CMD_WR_MEMSTART);
//	for(i=height-1;i>=0;i--)
//	{
//		DataPtr = startDataPtr + 2*i*width;
//		for(j=0;j<width;j++)
//		{
//			uBmpData = (uint16_t)(*(DataPtr)) | (uint16_t)((*(DataPtr + 1)) << 8);
//			LCD_WriteRAM( uBmpData );
//			DataPtr +=2;
//		}
//	}
//}

/**
  * @brief  Displays a full rectangle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * Height: specified in the bitmap file.
  * Width: 	specified in the bitmap file.
  * @retval None
  */
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height,uint16_t color)
{
	int i;
	LCD_SetArea(Xpos,Ypos,Xpos+Width - 1,Ypos+Height - 1);
	LCD_WriteCmd(CMD_WR_MEMSTART);
	for(i=0;i<Width*Height;i++)	LCD_WriteRAM( color );
}

/**
  * @brief  Displays a full circle.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  Radius
  * @retval None
  */
//void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius,uint16_t color)
//{
//   uint32_t n = 2;
//	uint16_t tmp = TextColor;
//  LCD_DrawCircle( Xpos , Ypos , Radius);
//  LCD_DrawCircle( Xpos , Ypos , Radius - 1);
//  LCD_SetTextColor(color);
//  for (; n < Radius; n++)
//  {
//    LCD_DrawCircle( Xpos, Ypos, Radius - n);
//  }
//	 LCD_SetTextColor(tmp);
//}

/**
  * @brief  Displays an uni-line (between two points).
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */
void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    SSD1963_PutPixel(x, y);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}

/**
  * @brief  Displays an poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLine(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0;

  if(PointCount < 2)
  {
    return;
  }

  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    LCD_DrawUniLine(X, Y, Points->X, Points->Y);
  }
}

/**
  * @brief  Displays an relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @param  Closed: specifies if the draw is closed or not.
  *           1: closed, 0 : not closed.
  * @retval None
  */
static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed)
{
  int16_t X = 0, Y = 0;
  pPoint First = Points;

  if(PointCount < 2)
  {
    return;
  }  
  X = Points->X;
  Y = Points->Y;
  while(--PointCount)
  {
    Points++;
    LCD_DrawUniLine(X, Y, X + Points->X, Y + Points->Y);
    X = X + Points->X;
    Y = Y + Points->Y;
  }
  if(Closed)
  {
    LCD_DrawUniLine(First->X, First->Y, X, Y);
  }  
}

/**
  * @brief  Displays a closed poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLine(Points, PointCount);
//  LCD_DrawUniLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
}

/**
  * @brief  Displays a relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLineRelativeClosed(Points, PointCount, 0);
}

/**
  * @brief  Displays a closed relative poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount)
{
  LCD_PolyLineRelativeClosed(Points, PointCount, 1);
}


/**
  * @brief  Displays a  full poly-line (between many points).
  * @param  Points: pointer to the points array.
  * @param  PointCount: Number of points.
  * @retval None
  */
void LCD_FillPolyLine(pPoint Points, uint16_t PointCount)
{
   /*  public-domain code by Darel Rex Finley, 2007 */
  uint16_t  nodes = 0, nodeX[MAX_POLY_CORNERS], pixelX = 0, pixelY = 0, i = 0,
  j = 0, swap = 0;
  uint16_t  IMAGE_LEFT = 0, IMAGE_RIGHT = 0, IMAGE_TOP = 0, IMAGE_BOTTOM = 0;

  IMAGE_LEFT = IMAGE_RIGHT = Points->X;
  IMAGE_TOP= IMAGE_BOTTOM = Points->Y;

  for(i = 1; i < PointCount; i++)
  {
    pixelX = POLY_X(i);
    if(pixelX < IMAGE_LEFT)
    {
      IMAGE_LEFT = pixelX;
    }
    if(pixelX > IMAGE_RIGHT)
    {
      IMAGE_RIGHT = pixelX;
    }
    
    pixelY = POLY_Y(i);
    if(pixelY < IMAGE_TOP)
    { 
      IMAGE_TOP = pixelY;
    }
    if(pixelY > IMAGE_BOTTOM)
    {
      IMAGE_BOTTOM = pixelY;
    }
  }
  
  LCD_SetTextColor(BackColor);  

  /*  Loop through the rows of the image. */
  for (pixelY = IMAGE_TOP; pixelY < IMAGE_BOTTOM; pixelY++) 
  {  
    /* Build a list of nodes. */
    nodes = 0; j = PointCount-1;

    for (i = 0; i < PointCount; i++) 
    {
      if (((POLY_Y(i)<(double) pixelY) && (POLY_Y(j)>=(double) pixelY)) || \
          ((POLY_Y(j)<(double) pixelY) && (POLY_Y(i)>=(double) pixelY)))
      {
        nodeX[nodes++]=(int) (POLY_X(i)+((pixelY-POLY_Y(i))*(POLY_X(j)-POLY_X(i)))/(POLY_Y(j)-POLY_Y(i))); 
      }
      j = i; 
    }
  
    /* Sort the nodes, via a simple "Bubble" sort. */
    i = 0;
    while (i < nodes-1) 
    {
      if (nodeX[i]>nodeX[i+1]) 
      {
        swap = nodeX[i]; 
        nodeX[i] = nodeX[i+1]; 
        nodeX[i+1] = swap; 
        if(i)
        {
          i--; 
        }
      }
      else 
      {
        i++;
      }
    }
  
    /*  Fill the pixels between node pairs. */
    for (i = 0; i < nodes; i+=2) 
    {
      if(nodeX[i] >= IMAGE_RIGHT) 
      {
        break;
      }
      if(nodeX[i+1] > IMAGE_LEFT) 
      {
        if (nodeX[i] < IMAGE_LEFT)
        {
          nodeX[i]=IMAGE_LEFT;
        }
        if(nodeX[i+1] > IMAGE_RIGHT)
        {
          nodeX[i+1] = IMAGE_RIGHT;
        }
        LCD_SetTextColor(BackColor);
        LCD_DrawLine(pixelY, nodeX[i+1], nodeX[i+1] - nodeX[i], LCD_DIR_HORIZONTAL);
        LCD_SetTextColor(TextColor);
        SSD1963_PutPixel(pixelY, nodeX[i+1]);
        SSD1963_PutPixel(pixelY, nodeX[i]);
        /* for (j=nodeX[i]; j<nodeX[i+1]; j++) PutPixel(j,pixelY); */
      }
    }
  } 

  /* draw the edges */
  LCD_SetTextColor(TextColor);
}

#ifndef USE_Delay
/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0; 
  for(index = (10000 * nCount); index != 0; index--)
  {
  }
}
#endif /* USE_Delay*/
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
