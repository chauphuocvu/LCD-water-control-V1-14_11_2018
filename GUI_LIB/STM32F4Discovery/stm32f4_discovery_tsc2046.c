#include "stm32f4_discovery_tsc2046.h"
#include "stm32f4_discovery_LCD_SSD1963.h"
#include "stm32f4xx_flash.h"

int32_t A2 = 0, B2 = 0, C2 = 0, D2 = 0, E2 = 0, F2 = 0;
//__IO uint8_t touch_done;
__IO uint16_t XCoordinate, YCoordinate;
extern __IO uint32_t u32_TSXCoordinate;
extern __IO uint32_t u32_TSYCoordinate;
uint32_t	tmp;

union	data
{
	uint32_t intdata;
	float	floatdata;
}mydata;

#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_6   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_7   /* End @ of user Flash area */

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define CalibrationDone_Offset  ((uint8_t)0 * sizeof(uint32_t))
#define An_Offset               ((uint8_t)1 * sizeof(uint32_t))
#define Bn_Offset               ((uint8_t)2 * sizeof(uint32_t))
#define Cn_Offset               ((uint8_t)3 * sizeof(uint32_t))
#define Dn_Offset               ((uint8_t)4 * sizeof(uint32_t))
#define En_Offset               ((uint8_t)5 * sizeof(uint32_t))
#define Fn_Offset               ((uint8_t)6 * sizeof(uint32_t)) 
#define Divider_Offset          ((uint8_t)7 * sizeof(uint32_t)) 
/* Private macros ------------------------------------------------------------*/
#define TS_ReadCalibrationVaraible(offset)  (*(__IO uint32_t*)(CalibrationAddr + offset))
/* Private variables ---------------------------------------------------------*/

Matrix matrix ;
Coordinate  display ;

static void DelayUS(vu32 cnt)
{
  uint16_t i;
  for(i = 0;i<cnt;i++)
  {
     uint8_t us = 12; /* 设置值为12，大约延1微秒 */    
     while (us--)     /* 延1微秒	*/
     {
       ;   
     }
  }
}
void WR_CMD(uint8_t cmd)  
{ 
  /* Wait for SPI2 Tx buffer empty */ 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 
  /* Send SPI2 data */ 
  SPI_I2S_SendData(SPI2,cmd); 
  /* Wait for SPI1 data reception */ 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); 
  /* Read SPI2 received data */ 
  SPI_I2S_ReceiveData(SPI2); 
} 



static void TSC2046_SPI_Init(uint16_t SPISpeed) 
{ 
  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  // enable the SPI peripheral clock
  SPI_PORT_CLOCK_INIT(SPI_PORT_CLOCK, ENABLE);
	 // enable the peripheral GPIO port clocks
  RCC_AHB1PeriphClockCmd(SPI_SCK_GPIO_CLK | SPI_MOSI_GPIO_CLK | SPI_MISO_GPIO_CLK, ENABLE);
	
	// Connect SPI pins to AF5 - see section 3, Table 6 in the device datasheet

	GPIO_PinAFConfig(SPI_SCK_GPIO_PORT, SPI_SCK_SOURCE, SPI_SCK_AF);
  GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT, SPI_MOSI_SOURCE, SPI_MOSI_AF);
	GPIO_PinAFConfig(SPI_MISO_GPIO_PORT, SPI_MISO_SOURCE, SPI_MISO_AF);
	
	// now configure the pins themselves
  // they are all going to be fast push-pull outputs
  // but the SPI pins use the alternate function
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN;
  GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN;
  GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
  GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  SPI_I2S_DeInit(SPI_PORT);
  SPI_StructInit(&SPI_InitStructure);
  /* SPI2 Config -------------------------------------------------------------*/ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPISpeed; 
//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
  SPI_InitStructure.SPI_CRCPolynomial = 7; 
  SPI_Init(SPI_PORT, &SPI_InitStructure);
  /* Enable SPI2 */ 
  SPI_Cmd(SPI_PORT, ENABLE); 
} 
void TP_Init(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);

  /* TP_CS */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /* TP_IRQ */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  On(TP_CS); 
  TSC2046_SPI_Init(SPI_BaudRatePrescaler_256);
	DelayUS(1000);
	WR_CMD(REFOFF); 
		
} 

static int RD_AD(void)  
{ 
  unsigned short buf,temp; 
  /* Wait for SPI2 Tx buffer empty */ 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 
  /* Send SPI2 data */ 
  SPI_I2S_SendData(SPI2,0x0000); 
  /* Wait for SPI2 data reception */ 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); 
  /* Read SPI2 received data */ 
  temp=SPI_I2S_ReceiveData(SPI2); 
  buf=temp<<8; 
  DelayUS(1); 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 
  /* Send SPI2 data */ 
  SPI_I2S_SendData(SPI2,0x0000); 
  /* Wait for SPI2 data reception */ 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); 
  /* Read SPI2 received data */ 
  temp=SPI_I2S_ReceiveData(SPI2); 
  buf |= temp; 
  buf>>=3; 
  buf&=0xfff; 
  return buf; 
} 

int Read_X(void)  
{  
  int i; 
  Off(TP_CS); 
  DelayUS(1); 
  WR_CMD(CHX); 
  DelayUS(1); 
  i=RD_AD(); 
  On(TP_CS);
  return i;    
} 

int Read_Y(void)  
{  
  int i; 
  Off(TP_CS); 
  DelayUS(1); 
  WR_CMD(CHY); 
  DelayUS(1); 
  i=RD_AD(); 
  On(TP_CS); 
  return i;     
} 
void TP_GetAdXY(int *x,int *y)  
{ 
  int adx,ady; 
  adx=Read_X(); 
  DelayUS(2); 
  ady=Read_Y(); 
  *x=adx; 
  *y=ady; 
} 

Coordinate *Read_tsc2046(void)
{
  static Coordinate  screen;
  int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
  uint8_t count=0;
  int buffer[2][9]={{0},{0}};  
//  TSC2046_SPI_Init(); 		
  do					      
  {		   
  TP_GetAdXY(TP_X,TP_Y);  
	buffer[0][count]=TP_X[0];  
	buffer[1][count]=TP_Y[0];
	count++;  
  }
//	while(TP_INT_IN && (count<9)); 
  while(!TP_INT_IN && (count<9));  
  if(count==9)   
  {  
    
  temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
	temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
	temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;
	
	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];
	
	m0=m0>0?m0:(-m0);
    m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);
	
	if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;
	
	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.x=(temp[0]+temp[2])/2;
	  else 
	    screen.x=(temp[0]+temp[1])/2;	
	}
	else if(m2<m1) 
	  screen.x=(temp[0]+temp[2])/2;
	else 
	  screen.x=(temp[1]+temp[2])/2;

  temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3;
	temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3;
	temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3;
	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];
	m0=m0>0?m0:(-m0);
	m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);
	if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.y=(temp[0]+temp[2])/2;
	  else 
	    screen.y=(temp[0]+temp[1])/2;	
    }
	else if(m2<m1) 
	   screen.y=(temp[0]+temp[2])/2;
	else
	   screen.y=(temp[1]+temp[2])/2;

	return &screen;
  }  
 return 0;
}

//void DrawCross(uint16_t Xpos,uint16_t Ypos)
//{
//  LCD_DrawUniLine(Xpos-15,Ypos,Xpos-2,Ypos);
//  LCD_DrawUniLine(Xpos+2,Ypos,Xpos+15,Ypos);
//  LCD_DrawUniLine(Xpos,Ypos-15,Xpos,Ypos-2);
//  LCD_DrawUniLine(Xpos,Ypos+2,Xpos,Ypos+15);
//  
//  LCD_DrawUniLine(Xpos-15,Ypos+15,Xpos-7,Ypos+15);
//  LCD_DrawUniLine(Xpos-15,Ypos+7,Xpos-15,Ypos+15);

//  LCD_DrawUniLine(Xpos-15,Ypos-15,Xpos-7,Ypos-15);
//  LCD_DrawUniLine(Xpos-15,Ypos-7,Xpos-15,Ypos-15);

//  LCD_DrawUniLine(Xpos+7,Ypos+15,Xpos+15,Ypos+15);
//  LCD_DrawUniLine(Xpos+15,Ypos+7,Xpos+15,Ypos+15);

//  LCD_DrawUniLine(Xpos+7,Ypos-15,Xpos+15,Ypos-15);
//  LCD_DrawUniLine(Xpos+15,Ypos-15,Xpos+15,Ypos-7);	  	
//}	
//void GL_Cross(uint16_t Xpos,uint16_t Ypos)
//{
//  	DrawCross(Xpos,Ypos);
//}	



uint32_t	getTouchPoint()
{
	//if previous touch has not processed, return;

	Coordinate * Ptr;
	if (touch_done) return 0;
	Ptr=Read_tsc2046();
	if	(Ptr == (void*)0) return 0;
	/* XD = AX+BY+C */        
    XCoordinate = ( (matrix.An * Ptr->x) + (matrix.Bn * Ptr->y) + matrix.Cn )/ matrix.Divider;
		u32_TSXCoordinate = XCoordinate;
	/* YD = DX+EY+F */        
    YCoordinate = ( (matrix.Dn * Ptr->x) + (matrix.En * Ptr->y) + matrix.Fn )/ matrix.Divider;
		u32_TSYCoordinate = YCoordinate;
	touch_done = 1;
	return 1;
}

static void waitPenRelease()
{
	Coordinate * Ptr;
	int i= 0;
	 do
   {
   Ptr=Read_tsc2046();
		 if (Ptr == (void*)0)	i++;
		 else i=0;
   }
   while( i < 1000);
}

void TouchPanel_Calibrate(void)
{

Coordinate * Ptr;
	 uint32_t coordinate_X1a = 0, coordinate_X2a = 0, coordinate_X3a = 0, coordinate_X4a = 0, coordinate_X5a = 0;
  uint32_t coordinate_Y1a = 0, coordinate_Y2a = 0, coordinate_Y3a = 0, coordinate_Y4a = 0, coordinate_Y5a = 0;
  uint32_t coordinate_X1b = 0, coordinate_X2b = 0, coordinate_X3b = 0, coordinate_X4b = 0, coordinate_X5b = 0;
  uint32_t coordinate_Y1b = 0, coordinate_Y2b = 0, coordinate_Y3b = 0, coordinate_Y4b = 0, coordinate_Y5b = 0;
  uint32_t coordinate_X1 = 0, coordinate_X2 = 0, coordinate_X3 = 0, coordinate_X4 = 0, coordinate_X5 = 0;
  uint32_t coordinate_Y1 = 0, coordinate_Y2 = 0, coordinate_Y3 = 0, coordinate_Y4 = 0, coordinate_Y5 = 0;
  uint16_t Xd1 = (LCD_Width / 2), Xd2 = 1 * (LCD_Width / 10), Xd3 = 9 * (LCD_Width / 10), Xd4 = 9 * (LCD_Width / 10), Xd5 = 1 * (LCD_Width / 10);
  uint16_t Yd1 = (LCD_Height / 2), Yd2 = 1 * (LCD_Height / 10), Yd3 = 1 * (LCD_Height / 10), Yd4 = 9 * (LCD_Height / 10), Yd5 = 9 * (LCD_Height / 10);
 
  double d = 0.0, dx1 = 0.0, dx2 = 0.0, dx3 = 0.0, dy1 = 0.0, dy2 = 0.0, dy3 = 0.0;
  uint32_t X2_1 = 0, X2_2 = 0, X2_3 = 0, X2_4 = 0, X2_5 = 0;
  uint32_t Y2_1 = 0, Y2_2 = 0, Y2_3 = 0, Y2_4 = 0, Y2_5 = 0;
  uint32_t XxY_1 = 0, XxY_2 = 0, XxY_3 = 0, XxY_4 = 0, XxY_5 = 0;
  uint32_t XxXd_1 = 0, XxXd_2 = 0, XxXd_3 = 0, XxXd_4 = 0, XxXd_5 = 0;
  uint32_t YxXd_1 = 0, YxXd_2 = 0, YxXd_3 = 0, YxXd_4 = 0, YxXd_5 = 0;
  uint32_t XxYd_1 = 0, XxYd_2 = 0, XxYd_3 = 0, XxYd_4 = 0, XxYd_5 = 0;
  uint32_t YxYd_1 = 0, YxYd_2 = 0, YxYd_3 = 0, YxYd_4 = 0, YxYd_5 = 0;
  uint32_t alfa = 0, beta = 0, chi = 0, Kx = 0, Ky = 0, Lx = 0, Ly = 0;
  uint32_t epsilon = 0, fi = 0, Mx = 0, My = 0;
	
//	uint32_t	i;
	

	DelayUS(50000);

  LCD_SetBackColor(WHITE);
  LCD_SetTextColor(BLACK);
  LCD_Clear(WHITE);
  LCD_DisplayAdjStringLine(3 * (LCD_Height / 7), LCD_Width - 25, "Run Calibration.", LCD_FALSE);

  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross(  (LCD_Width / 2),(LCD_Height / 2) ); /* Absolute Central Point */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X1a = Ptr->x;
  coordinate_Y1a = Ptr->y;

	DelayUS(50000);
	 
	waitPenRelease();

  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross( 1*(LCD_Width / 10),1*(LCD_Height / 10)); /* Nord-East Corner point */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X2a = Ptr->x;
  coordinate_Y2a = Ptr->y;
	 
DelayUS(50000);
	waitPenRelease();

  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross( 9*(LCD_Width / 10),1*(LCD_Height / 10)); /* Nord-West Corner */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X3a = Ptr->x;
  coordinate_Y3a = Ptr->y;
DelayUS(50000);
		waitPenRelease();

  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross(9*(LCD_Width / 10),9*(LCD_Height / 10)); /* Sud-West Corner */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X4a = Ptr->x;
  coordinate_Y4a = Ptr->y;

DelayUS(50000);
	 	waitPenRelease();
  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross( 1*(LCD_Width / 10),9*(LCD_Height / 10)); /* Sud-East Corner point */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X5a = Ptr->x;
  coordinate_Y5a = Ptr->y;

DelayUS(50000);
	 waitPenRelease();
	 
  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross(  (LCD_Width / 2) ,(LCD_Height / 2)); /* Absolute Central Point */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X1b = Ptr->x;
  coordinate_Y1b = Ptr->y;

  DelayUS(50000);
		waitPenRelease();
  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross( 1*(LCD_Width / 10),1*(LCD_Height / 10)); /* Nord-East Corner point */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X2b = Ptr->x;
  coordinate_Y2b = Ptr->y;

DelayUS(50000);
	 waitPenRelease();
  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross( 9*(LCD_Width / 10),1*(LCD_Height / 10)); /* Nord-West Corner */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X3b = Ptr->x;
  coordinate_Y3b = Ptr->y;
	
DelayUS(50000);
	 waitPenRelease();
  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross(9*(LCD_Width / 10),9*(LCD_Height / 10)); /* Sud-West Corner */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X4b = Ptr->x;
  coordinate_Y4b = Ptr->y;

DelayUS(50000);
	 waitPenRelease();
  touch_done = 0;

  LCD_Clear(WHITE);
  GL_Cross( 1*(LCD_Width / 10),9*(LCD_Height / 10)); /* Sud-East Corner point */
   do
   {
   Ptr=Read_tsc2046();
   }
   while( Ptr == (void*)0 );
  coordinate_X5b = Ptr->x;
  coordinate_Y5b = Ptr->y;

DelayUS(50000);
	waitPenRelease();
  touch_done = 0;

  /* Average between X and Y coupled Touchscreen values */
  coordinate_X1 = (coordinate_X1a + coordinate_X1b) / 2;
  coordinate_X2 = (coordinate_X2a + coordinate_X2b) / 2;
  coordinate_X3 = (coordinate_X3a + coordinate_X3b) / 2;
  coordinate_X4 = (coordinate_X4a + coordinate_X4b) / 2;
  coordinate_X5 = (coordinate_X5a + coordinate_X5b) / 2;

  coordinate_Y1 = (coordinate_Y1a + coordinate_Y1b) / 2;
  coordinate_Y2 = (coordinate_Y2a + coordinate_Y2b) / 2;
  coordinate_Y3 = (coordinate_Y3a + coordinate_Y3b) / 2;
  coordinate_Y4 = (coordinate_Y4a + coordinate_Y4b) / 2;
  coordinate_Y5 = (coordinate_Y5a + coordinate_Y5b) / 2;

  X2_1 = (coordinate_X1 * coordinate_X1);
  X2_2 = (coordinate_X2 * coordinate_X2);
  X2_3 = (coordinate_X3 * coordinate_X3);
  X2_4 = (coordinate_X4 * coordinate_X4);
  X2_5 = (coordinate_X5 * coordinate_X5);

  Y2_1 = (coordinate_Y1 * coordinate_Y1);
  Y2_2 = (coordinate_Y2 * coordinate_Y2);
  Y2_3 = (coordinate_Y3 * coordinate_Y3);
  Y2_4 = (coordinate_Y4 * coordinate_Y4);
  Y2_5 = (coordinate_Y5 * coordinate_Y5);

  XxY_1 = (coordinate_X1 * coordinate_Y1);
  XxY_2 = (coordinate_X2 * coordinate_Y2);
  XxY_3 = (coordinate_X3 * coordinate_Y3);
  XxY_4 = (coordinate_X4 * coordinate_Y4);
  XxY_5 = (coordinate_X5 * coordinate_Y5);

  XxXd_1 = ( coordinate_X1 * Xd1 );
  XxXd_2 = ( coordinate_X2 * Xd2 );
  XxXd_3 = ( coordinate_X3 * Xd3 );
  XxXd_4 = ( coordinate_X4 * Xd4 );
  XxXd_5 = ( coordinate_X5 * Xd5 );

  YxXd_1 = ( coordinate_Y1 * Xd1 );
  YxXd_2 = ( coordinate_Y2 * Xd2 );
  YxXd_3 = ( coordinate_Y3 * Xd3 );
  YxXd_4 = ( coordinate_Y4 * Xd4 );
  YxXd_5 = ( coordinate_Y5 * Xd5 );

  XxYd_1 = ( coordinate_X1 * Yd1 );
  XxYd_2 = ( coordinate_X2 * Yd2 );
  XxYd_3 = ( coordinate_X3 * Yd3 );
  XxYd_4 = ( coordinate_X4 * Yd4 );
  XxYd_5 = ( coordinate_X5 * Yd5 );

  YxYd_1 = ( coordinate_Y1 * Yd1 );
  YxYd_2 = ( coordinate_Y2 * Yd2 );
  YxYd_3 = ( coordinate_Y3 * Yd3 );
  YxYd_4 = ( coordinate_Y4 * Yd4 );
  YxYd_5 = ( coordinate_Y5 * Yd5 );

  alfa = X2_1 + X2_2 + X2_3 + X2_4 + X2_5;
  beta = Y2_1 + Y2_2 + Y2_3 + Y2_4 + Y2_5;
  chi = XxY_1 + XxY_2 + XxY_3 + XxY_4 + XxY_5;
  epsilon = coordinate_X1 + coordinate_X2 + coordinate_X3 + coordinate_X4 + coordinate_X5;
  fi = coordinate_Y1 + coordinate_Y2 + coordinate_Y3 + coordinate_Y4 + coordinate_Y5;
  Kx = XxXd_1 + XxXd_2 + XxXd_3 + XxXd_4 + XxXd_5;
  Ky = XxYd_1 + XxYd_2 + XxYd_3 + XxYd_4 + XxYd_5;
  Lx = YxXd_1 + YxXd_2 + YxXd_3 + YxXd_4 + YxXd_5;
  Ly = YxYd_1 + YxYd_2 + YxYd_3 + YxYd_4 + YxYd_5;
  Mx = Xd1 + Xd2 + Xd3 + Xd4 + Xd5;
  My = Yd1 + Yd2 + Yd3 + Yd4 + Yd5;

  d = 5 * ( ((double)alfa * beta) - ((double)chi * chi) ) + 2 * ((double)chi * epsilon * fi) - ((double)alfa * fi * fi ) - ( (double)beta * epsilon * epsilon );
  dx1 = 5 * ( ((double)Kx * beta) - ((double)Lx * chi) ) + ((double)fi * ( ((double)Lx * epsilon) - ((double)Kx * fi) )) + ((double)Mx * ( ((double)chi * fi) - ((double)beta * epsilon) ));
  dx2 = 5 * ( ((double)Lx * alfa) - ((double)Kx * chi) ) + ((double)epsilon * ( ((double)Kx * fi) - ((double)Lx * epsilon) )) + ((double)Mx * ( ((double)chi * epsilon) - ((double)alfa * fi) ));
  dx3 = ((double)Kx * ( ((double)chi * fi) - ((double)beta * epsilon) )) + ((double)Lx * ( ((double)chi * epsilon) - ((double)alfa * fi) )) + ((double)Mx * ( ((double)alfa * beta) - ((double)chi * chi) ));
  dy1 = 5 * ( ((double)Ky * beta) - ((double)Ly * chi) ) + ((double)fi * ( ((double)Ly * epsilon) - ((double)Ky * fi) )) + ((double)My * ( ((double)chi * fi) - ((double)beta * epsilon) ));
  dy2 = 5 * ( ((double)Ly * alfa) - ((double)Ky * chi) ) + ((double)epsilon * ( ((double)Ky * fi) - ((double)Ly * epsilon) )) + ((double)My * ( ((double)chi * epsilon) - ((double)alfa * fi) ));
  dy3 = ((double)Ky * ( ((double)chi * fi) - ((double)beta * epsilon) )) + ((double)Ly * ( ((double)chi * epsilon) - ((double)alfa * fi) )) + ((double)My * ( ((double)alfa * beta) - ((double)chi * chi) ));



	matrix.An = dx1;
	matrix.Bn = dx2;
	matrix.Cn = dx3;
	matrix.Dn = dy1;
	matrix.En = dy2;
	matrix.Fn = dy3;
	matrix.Divider = d;
  LCD_Clear(WHITE);
	saveCalibrationData();
  LCD_DisplayAdjStringLine(3 * (LCD_Height / 7), 1 * (LCD_Width / 11), "Calibration done!", LCD_FALSE);


	DelayUS(50000);

} 


/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }

  return sector;
}


uint32_t	saveCalibrationData()
{
	uint32_t i = 0;
	uint32_t StartSector = 0, EndSector = 0, Address = 0 ;
	
	 FLASH_Unlock();
	 /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	StartSector = GetSector(FLASH_USER_START_ADDR);
  EndSector = GetSector(FLASH_USER_END_ADDR);
	
	  for (i = StartSector; i < EndSector; i += 8)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE)
    { 
      /* Error occurred while sector erase. 
         User can add here some code to deal with this error  */
      return	1;
    }
  }
	
	Address = FLASH_USER_START_ADDR;
	     
	if (FLASH_ProgramWord(Address, 0x55555555) != FLASH_COMPLETE)	return 1;
	Address = Address + 4;
	mydata.floatdata = matrix.An;
	if (FLASH_ProgramWord(Address, mydata.intdata) != FLASH_COMPLETE)	return 1;
	Address = Address + 4;
	mydata.floatdata = matrix.Bn;
	if (FLASH_ProgramWord(Address, mydata.intdata) != FLASH_COMPLETE)	return 1;
 	Address = Address + 4;
	mydata.floatdata = matrix.Cn;
	if (FLASH_ProgramWord(Address, mydata.intdata) != FLASH_COMPLETE)	return 1;
  	Address = Address + 4;
	mydata.floatdata = matrix.Dn;
	if (FLASH_ProgramWord(Address, mydata.intdata) != FLASH_COMPLETE)	return 1; 
	Address = Address + 4;
	mydata.floatdata = matrix.En;
	if (FLASH_ProgramWord(Address, mydata.intdata) != FLASH_COMPLETE)	return 1;	
		Address = Address + 4;
	mydata.floatdata = matrix.Fn;
	if (FLASH_ProgramWord(Address, mydata.intdata) != FLASH_COMPLETE)	return 1;
		Address = Address + 4;
	mydata.floatdata = matrix.Divider;
	if (FLASH_ProgramWord(Address, mydata.intdata) != FLASH_COMPLETE)	return 1;
		FLASH_Lock(); 	
	return	0;
	
}

uint32_t	readCalibrationValue()
{
	uint32_t	i = 0;
	uint32_t	CalibrationAddr;
	Coordinate * Ptr;
	CalibrationAddr = FLASH_USER_START_ADDR;
	LCD_Clear(WHITE);
	 if ((TS_ReadCalibrationVaraible(CalibrationDone_Offset)  != 0x55555555))
  {
    TouchPanel_Calibrate();
		return 0;
  }
	else
	{
		LCD_DisplayAdjStringLine(3 * (LCD_Height / 7), 1 * (LCD_Width / 11), "Touch screen to ", LCD_TRUE);
		LCD_DisplayAdjStringLine(5 * (LCD_Height / 7), 1 * (LCD_Width / 11), "start calibrating!", LCD_TRUE);
		while (i < 10000)
		{
			Ptr=Read_tsc2046();
			i++;

			if ( Ptr != (void*)0 ) break;
		}
	}
		
	if (i < 10000)
	{
		TouchPanel_Calibrate();
		return 0;
	}
		
				mydata.intdata = TS_ReadCalibrationVaraible(An_Offset);
			matrix.An = mydata.floatdata;
				mydata.intdata = TS_ReadCalibrationVaraible(Bn_Offset);
			matrix.Bn = mydata.floatdata;
				mydata.intdata = TS_ReadCalibrationVaraible(Cn_Offset);
			matrix.Cn = mydata.floatdata;
				mydata.intdata = TS_ReadCalibrationVaraible(Dn_Offset);
			matrix.Dn = mydata.floatdata;
				mydata.intdata = TS_ReadCalibrationVaraible(En_Offset);
			matrix.En = mydata.floatdata;
				mydata.intdata = TS_ReadCalibrationVaraible(Fn_Offset);
			matrix.Fn = mydata.floatdata;
				mydata.intdata = TS_ReadCalibrationVaraible(Divider_Offset);
			matrix.Divider = mydata.floatdata;

	return 0;
}

