/*******************************************************************************
* @file		: uiframework.c
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 11-Apr-2017
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
GL_Page_TypeDef home;
/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/
/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_home() 
{ 
	GL_RadioButtonGrp_TypeDef* Group01=NewRadioButtonGrp(1);


	GL_PageControls_TypeDef* txt1= NewLabel(2,"THIS IS A TEXT LABEL.",GL_HORIZONTAL,GL_FONT_BIG,txt1Color);
	GL_PageControls_TypeDef* bt1= NewButton(3,"BUTTON",home_bt1_Click);
	GL_PageControls_TypeDef* cb1= NewCheckbox(4,"CHECK BOX",home_cb1_CheckChanged);
	GL_PageControls_TypeDef* sw1= NewSwitch(5,"SWITCH","",home_sw1_Toggle);
	GL_PageControls_TypeDef* cbox1= NewComboBoxGrp(6);
	GL_PageControls_TypeDef* sb1= NewSlidebar(7,"SLIDE BAR",GL_HORIZONTAL,home_sb1_ValueChanged);
	GL_PageControls_TypeDef* obt1 = RADIO_BUTTON_ADD(Group01,"OPT BUTTON",home_obt1_Selected);
	Create_PageObj( &home ); 
//	AddPageControlObj(479,0,txt1,&home);
//	AddPageControlObj(479,50,bt1,&home);
//	AddPageControlObj(479,100,cb1,&home);
//	AddPageControlObj(479,150,obt1,&home);
//	AddPageControlObj(479,200,sw1,&home);
//	AddPageControlObj( 229,50,cbox1,&home);
//	AddPageControlObj(229,100,sb1,&home);
	
	AddPageControlObj(0,0,txt1,&home);
	AddPageControlObj(200,50,bt1,&home);
	AddPageControlObj(50,100,cb1,&home);
	AddPageControlObj(50,150,obt1,&home);
	AddPageControlObj(150,200,sw1,&home);
	AddPageControlObj(400,50,cbox1,&home);
	AddPageControlObj(400,100,sb1,&home);
}




/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_home()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	GL_Clear(45029);
	GL_SetTextColor(63488);
	home.ShowPage(&home, GL_TRUE);
	CurrentScreen=&home; 
} 

/**
  * @brief Controls home screen
  * @param None
  * @retval None
  */
void Show_HomeScreen()
{
	Create_home();
	CurrentScreen = &home;
	GL_Clear(45029);
	GL_SetTextColor(63488);
	home.ShowPage(&home,GL_TRUE);
}

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

