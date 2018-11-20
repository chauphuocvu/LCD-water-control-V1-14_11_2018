/*******************************************************************************
* @file		: uiappuser.c
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 11-Apr-2017
* @brief	: Event Handlers
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
#include "LcdHal.h"
/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup User_Functions
  * @brief Contains event handlers for controls to execute the user code
  * @{
  */

/* External variables ----------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private defines -------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/

/**
  * @brief Button click event handler
  * @note This function gets called when user clicks  bt1.
  * @param None
  * @retval None
  */
void home_bt1_Click()
{
	//Show_home();
}
/**
  * @brief Checkbox check event handler
  * @note This function gets called when user clicks cb1
  * @param None
  * @retval None
  */
void home_cb1_CheckChanged()
{
}
/**
  * @brief Option button selected event handler
  * @note This function gets called when user selects option obt1
  * @param None
  * @retval None
  */
void home_obt1_Selected()
{
}
/**
  * @brief Switch toggle event handler
  * @note This function is called when user toggles the switch sw1
  * @param None
  * @retval None
  */
void home_sw1_Toggle()
{
	Toggle(BZ);
}
/**
  * @brief Slidebar dragged event handler
  * @note This function is called when user drags the slideBar sb1.
  * @param None
  * @retval None
  */
void home_sb1_ValueChanged()
{
}

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

