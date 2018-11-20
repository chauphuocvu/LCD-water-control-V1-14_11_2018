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
GL_Page_TypeDef screen1;
GL_Page_TypeDef screen2;
/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/
/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_screen1() 
{ 
	GL_RadioButtonGrp_TypeDef* Group01=NewRadioButtonGrp(1);

	GL_PageControls_TypeDef* DesignLabel01= NewLabel(2,"THIS IS SCREEN 1",GL_HORIZONTAL,GL_FONT_BIG,DesignLabel01Color);
	GL_PageControls_TypeDef* DesignButton01= NewButton(3,"NEXT BUTTON",screen1_DesignButton01_Click);
	GL_PageControls_TypeDef* DesignOptionButton01 = RADIO_BUTTON_ADD(Group01,"Opt1",screen1_DesignOptionButton01_Selected);
	GL_PageControls_TypeDef* DesignOptionButton02 = RADIO_BUTTON_ADD(Group01,"Opt2",screen1_DesignOptionButton02_Selected);
	GL_PageControls_TypeDef* cb1= NewCheckbox(4,"CHECK BOX",screen1_cb1_CheckChanged);
	Create_PageObj( &screen1 ); 
	AddPageControlObj(100,10,DesignLabel01,&screen1);
	AddPageControlObj(10,100,DesignOptionButton01,&screen1);
	AddPageControlObj(10,150,DesignOptionButton02,&screen1);
	AddPageControlObj(10,50,DesignButton01,&screen1);
	AddPageControlObj(200,100,cb1,&screen1);
}


/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_screen2() 
{ 

	GL_PageControls_TypeDef* DesignLabel02= NewLabel(5,"SCREEN 2 HAS SMALLER TEXT",GL_HORIZONTAL,GL_FONT_BIG,DesignLabel02Color);
	GL_PageControls_TypeDef* DesignButton02= NewButton(6,"BACK BUTTON",screen2_DesignButton02_Click);
	Create_PageObj( &screen2 ); 
	AddPageControlObj(100,30,DesignLabel02,&screen2);
	AddPageControlObj(200,150,DesignButton02,&screen2);
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_screen1()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	GL_Clear(BROWN);
	GL_SetTextColor(65535);
	screen1.ShowPage(&screen1, GL_TRUE);
	CurrentScreen=&screen1; 
} 

/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_screen2()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	GL_Clear(0);
	GL_SetTextColor(65535);
	screen2.ShowPage(&screen2, GL_TRUE);
	CurrentScreen=&screen2; 
} 

/**
  * @brief Controls home screen
  * @param None
  * @retval None
  */
void Show_HomeScreen()
{
	Create_screen1();
	Create_screen2();
	CurrentScreen = &screen1;
	GL_Clear(0xC816);
	GL_SetTextColor(65535);
	screen1.ShowPage(&screen1,GL_TRUE);
}

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

