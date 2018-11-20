/*******************************************************************************
* @file		: uiframework.c
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
* @brief	: Screen Code
*******************************************************************************/
/* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
*******************************************************************************
*/ 
/*includes----------------------------------------------------------------------*/
#include "uiframework.h"
#include "uiappuser.h"
#include "float.h"
#include "LcdHal.h"
#include "TscHal.h"
#include "pictures.h"


GL_Page_TypeDef *CurrentScreen;

/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup UI_Framework
  * @brief This file contains functions to configure the screens and controls
  * @{
  */

/* External variables ----------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private defines -------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/

void Show_HomeScreen(void)
{
	Show_StartScreen();
}

/**
  * @}
  */
/*Giao dien tu thiet ke*/
GL_Page_TypeDef StartScreen;
void Create_StartScreen(void)
{
	GL_PageControls_TypeDef* StartScreen_DesignButton02= NewRectControl(1,210,32,StartScreen_Setting);
	Create_PageObj( &StartScreen ); 
	AddPageControlObj(250,240,StartScreen_DesignButton02,&StartScreen);
}
///////////////////////////////
void Show_StartScreen(void)
{
	UARTprintf("Create_StartScreen\r\n");
	Create_StartScreen();
	LCD_Clear(BLACK);
	/*VE CAC NUT DIEU KHIEN*/
	LCD_DrawFullRect(250,240,210,32,WHITE);//ve nut button
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(250,240,210,32,(uint8_t *)"SETTINGS");
	//LCD_SetColors(BLACK,WHITE);
	//LCD_DisplayStringLine(250,300,(uint8_t *)"SETTINGS");
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,130,(uint8_t *)"00:00:01");
	LCD_DisplayStringLine(20,290,(uint8_t *)"CHAU PHUOC VU");
	LCD_DisplayStringLine(250,20,(uint8_t *)"BACH KHOA");
	LCD_DrawFullRect(20,60,210,160,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,160,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(130,100,(uint8_t *)"0.5");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(80,30,(uint8_t *)"CHLORINE");
	LCD_DisplayStringLine(80,170,(uint8_t *)"0.5");	
	LCD_DisplayStringLine(160,175,(uint8_t *)"mg/l");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(130,330,(uint8_t *)"0.5");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(80,260,(uint8_t *)"PH--");
	LCD_DisplayStringLine(80,400,(uint8_t *)"0.5");	
	LCD_DisplayStringLine(175,400,(uint8_t *)"pH");	
	StartScreen.ShowPage(&StartScreen,GL_TRUE);
	CurrentScreen = &StartScreen;
}
/*Giao dien tu thiet ke*/
GL_Page_TypeDef SettingsScreen;
void Create_SettingsScreen(void)
{
	GL_PageControls_TypeDef* SettingsDesignButton01= NewRectControl(1,210,30,SettingsScreen_Language);
	GL_PageControls_TypeDef* SettingsDesignButton02= NewRectControl(2,210,30,SettingsScreen_BackToStart);
	GL_PageControls_TypeDef* SettingsDesignButton03= NewRectControl(3,210,80,SettingsScreen_Parameters);
	GL_PageControls_TypeDef* SettingsDesignButton04= NewRectControl(4,210,80,SettingsScreen_Calibration);
	GL_PageControls_TypeDef* SettingsDesignButton05= NewRectControl(5,210,80,SettingsScreen_DosingTest);
	GL_PageControls_TypeDef* SettingsDesignButton06= NewRectControl(6,210,80,SettingsScreen_TypeOfProbe);
	Create_PageObj( &SettingsScreen ); 
	AddPageControlObj(250,240,SettingsDesignButton01,&SettingsScreen);
	AddPageControlObj(20,240,SettingsDesignButton02,&SettingsScreen);
	AddPageControlObj(20,60,SettingsDesignButton03,&SettingsScreen);
	AddPageControlObj(250,60,SettingsDesignButton04,&SettingsScreen);
	AddPageControlObj(20,150,SettingsDesignButton05,&SettingsScreen);
	AddPageControlObj(250,150,SettingsDesignButton06,&SettingsScreen);
	
}
////////////////////////////////////////
void Show_SettingsScreen(void)
{
	UARTprintf("Create_SettingsScreen\r\n");
	Create_SettingsScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,380,(uint8_t *)"SETTINGS");
	//LCD_DisplayStringLine(250,20,(uint8_t *)"BACH KHOA");
	LCD_DrawRect(20,60,80,210);
	LCD_DrawRect(250,60,80,210);
	LCD_DrawRect(20,150,80,210);
	LCD_DrawRect(250,150,80,210);
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawRect(250,240,30,210);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(20,60,210,80,(uint8_t *)"PARAMETERS");
	LCD_DisplayStringLineInRect(250,60,210,80,(uint8_t *)"CALIBRATION");
	LCD_DisplayStringLineInRect(20,150,210,80,(uint8_t *)"DOSING TEST");
	LCD_DisplayStringLineInRect(250,150,210,80,(uint8_t *)"TYPE OF PROBE");
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"LANGUAGES");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	SettingsScreen.ShowPage(&SettingsScreen,GL_TRUE);
	CurrentScreen = &SettingsScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStartStartScreen;
void Create_DosingTestStartStartScreen(void)
{
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton01= NewRectControl(1,210,30,DosingTestStartStartScreen_Back);
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton02= NewRectControl(2,210,30,DosingTestStartStartScreen_BackToStart);
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton03= NewRectControl(3,210,70,DosingTestStartStartScreen_StartDisinf);
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton04= NewRectControl(4,210,70,DosingTestStartStartScreen_StartPh);
	Create_PageObj( &DosingTestStartStartScreen ); 
	AddPageControlObj(250,240,DosingTestStartStartDesignButton01,&DosingTestStartStartScreen);
	AddPageControlObj(20,240,DosingTestStartStartDesignButton02,&DosingTestStartStartScreen);
	AddPageControlObj(20,170,DosingTestStartStartDesignButton03,&DosingTestStartStartScreen);
	AddPageControlObj(250,170,DosingTestStartStartDesignButton04,&DosingTestStartStartScreen);	
}
////////////////////////////////////////
void Show_DosingTestStartStartScreen(void)
{
	UARTprintf("Create_DosingTestStartStartScreen\r\n");
	Create_DosingTestStartStartScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,100,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_DisplayStringLine(70,165,(uint8_t *)"400ml");	
	LCD_DisplayStringLine(127,155,(uint8_t *)"ml");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,330,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DisplayStringLine(70,400,(uint8_t *)"200ml");	
	LCD_DisplayStringLine(127,385,(uint8_t *)"ml");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"START");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"START");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStartStartScreen.ShowPage(&DosingTestStartStartScreen,GL_TRUE);
	CurrentScreen = &DosingTestStartStartScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStopStartScreen;
void Create_DosingTestStopStartScreen(void)
{	
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton01= NewRectControl(1,210,30,DosingTestStopStartScreen_Back);
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton02= NewRectControl(2,210,30,DosingTestStopStartScreen_BackToStart);
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton03= NewRectControl(3,210,60,DosingTestStopStartScreen_StopDisinf);
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton04= NewRectControl(4,210,60,DosingTestStopStartScreen_StartPh);
	Create_PageObj( &DosingTestStopStartScreen ); 
	AddPageControlObj(250,240,DosingTestStopStartDesignButton01,&DosingTestStopStartScreen);
	AddPageControlObj(20,240,DosingTestStopStartDesignButton02,&DosingTestStopStartScreen);
	AddPageControlObj(20,170,DosingTestStopStartDesignButton03,&DosingTestStopStartScreen);
	AddPageControlObj(250,170,DosingTestStopStartDesignButton04,&DosingTestStopStartScreen);	
}
////////////////////////////////////////
void Show_DosingTestStopStartScreen(void)
{
	UARTprintf("Create_DosingTestStopStartScreen\r\n");
	Create_DosingTestStopStartScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,100,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_DisplayStringLine(70,165,(uint8_t *)"400ml");	
	LCD_DisplayStringLine(127,155,(uint8_t *)"ml");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,330,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DisplayStringLine(70,400,(uint8_t *)"200ml");	
	LCD_DisplayStringLine(127,385,(uint8_t *)"ml");	
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"STOP");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"START");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStopStartScreen.ShowPage(&DosingTestStopStartScreen,GL_TRUE);
	CurrentScreen = &DosingTestStopStartScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStopStopScreen;
void Create_DosingTestStopStopScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,DosingTestStopStopScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,DosingTestStopStopScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,210,60,DosingTestStopStopScreen_StopDisinf);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,210,60,DosingTestStopStopScreen_StopPh);
	Create_PageObj( &DosingTestStopStopScreen ); 
	AddPageControlObj(250,240,DesignButton01,&DosingTestStopStopScreen);
	AddPageControlObj(20,240,DesignButton02,&DosingTestStopStopScreen);
	AddPageControlObj(20,170,DesignButton03,&DosingTestStopStopScreen);
	AddPageControlObj(250,170,DesignButton04,&DosingTestStopStopScreen);	
}
////////////////////////////////////////
void Show_DosingTestStopStopScreen(void)
{
	UARTprintf("Create_DosingTestStopStopScreen\r\n");
	Create_DosingTestStopStopScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,100,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_DisplayStringLine(70,165,(uint8_t *)"400ml");	
	LCD_DisplayStringLine(127,155,(uint8_t *)"ml");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,330,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DisplayStringLine(70,400,(uint8_t *)"200ml");	
	LCD_DisplayStringLine(127,385,(uint8_t *)"ml");	
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"STOP");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"STOP");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStopStopScreen.ShowPage(&DosingTestStopStopScreen,GL_TRUE);
	CurrentScreen = &DosingTestStopStopScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStartStopScreen;
void Create_DosingTestStartStopScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,DosingTestStartStopScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,DosingTestStartStopScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,210,60,DosingTestStartStopScreen_StartDisinf);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,210,60,DosingTestStartStopScreen_StopPh);
	Create_PageObj( &DosingTestStartStopScreen ); 
	AddPageControlObj(250,240,DesignButton01,&DosingTestStartStopScreen);
	AddPageControlObj(20,240,DesignButton02,&DosingTestStartStopScreen);
	AddPageControlObj(20,170,DesignButton03,&DosingTestStartStopScreen);
	AddPageControlObj(250,170,DesignButton04,&DosingTestStartStopScreen);
	
}
////////////////////////////////////////
void Show_DosingTestStartStopScreen(void)
{
	UARTprintf("Create_DosingTestStartStopScreen\r\n");
	Create_DosingTestStartStopScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,100,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_DisplayStringLine(70,165,(uint8_t *)"400ml");	
	LCD_DisplayStringLine(127,155,(uint8_t *)"ml");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,330,(uint8_t *)"150");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DisplayStringLine(70,400,(uint8_t *)"200ml");	
	LCD_DisplayStringLine(127,385,(uint8_t *)"ml");	
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"START");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"STOP");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStartStopScreen.ShowPage(&DosingTestStartStopScreen,GL_TRUE);
	CurrentScreen = &DosingTestStartStopScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersScreen;
void Create_ParametersScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,ParametersScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,ParametersScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,210,80,ParametersScreen_Pool);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,210,80,ParametersScreen_Water);
	Create_PageObj( &ParametersScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersScreen);
	AddPageControlObj(20,60,DesignButton03,&ParametersScreen);
	AddPageControlObj(250,60,DesignButton04,&ParametersScreen);
	
}
////////////////////////////////////////
void Show_ParametersScreen(void)
{
	UARTprintf("Create_ParametersScreen\r\n");
	Create_ParametersScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,355,(uint8_t *)"PARAMETERS");
	LCD_DrawRect(20,60,80,210);
	LCD_DrawRect(250,60,80,210);
	LCD_DrawFullRect(20,150,210,80,VU_YELLOW);
	LCD_DrawFullRect(250,150,210,80,VU_BLUE);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_DisplayStringLineInRect(20,150,210,80,(uint8_t *)"DISINFECTION");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_DisplayStringLineInRect(250,150,210,80,(uint8_t *)"pH");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,60,210,80,(uint8_t *)"POOL");
	LCD_DisplayStringLineInRect(250,60,210,80,(uint8_t *)"WATER");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	LCD_SetColors(BLACK,WHITE);
	ParametersScreen.ShowPage(&ParametersScreen,GL_TRUE);
	CurrentScreen = &ParametersScreen;
}




/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersPoolVolumeScreen;
void Create_ParametersPoolVolumeScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,ParametersPoolVolumeScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,ParametersPoolVolumeScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,ParametersPoolVolumeScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,ParametersPoolVolumeScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,ParametersPoolVolumeScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,ParametersPoolVolumeScreen_FiltrationPeriod);
	Create_PageObj( &ParametersPoolVolumeScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersPoolVolumeScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersPoolVolumeScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersPoolVolumeScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersPoolVolumeScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersPoolVolumeScreen);
	AddPageControlObj(250,60,DesignButton06,&ParametersPoolVolumeScreen);	
}
////////////////////////////////////////
void Show_ParametersPoolVolumeScreen(void)
{
	UARTprintf("Create_ParametersVolumeScreen\r\n");
	Create_ParametersPoolVolumeScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"POOL PARAMETERS");
	LCD_DrawFullRect(20,60,210,100,VU_ORANGE);
	LCD_DrawFullRect(250,60,210,100,VU_GRAY);
	LCD_SetColors(WHITE,VU_ORANGE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,100,(uint8_t *)"15");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"POOL VOLUME");
	LCD_DisplayStringLine(127,155,(uint8_t *)"m3");
	LCD_SetColors(WHITE,VU_GRAY);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(120,330,(uint8_t *)"06");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,255,(uint8_t *)"FILTRATION PERIOD");
	LCD_DisplayStringLine(127,385,(uint8_t *)"h");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(20,170,60,100);
	LCD_DrawRect(130,170,60,100);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,100,60,(uint8_t *)"+");
	LCD_DisplayStringLineInRect(130,170,100,60,(uint8_t *)"-");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"OK");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(BLACK,WHITE);
	ParametersPoolVolumeScreen.ShowPage(&ParametersPoolVolumeScreen,GL_TRUE);
	CurrentScreen = &ParametersPoolVolumeScreen;
}
/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 
/*Added by chau phuoc vu 14/11/2018*/
void DelayScreen_Decrement(void)
{
	if (delayscreen != 0)
		delayscreen--;
	else ;
}
void DelayScreen(uint16_t time)
{
delayscreen = time;
	while(delayscreen != 0);
}