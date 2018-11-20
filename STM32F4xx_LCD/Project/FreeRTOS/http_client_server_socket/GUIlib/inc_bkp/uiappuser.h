/*******************************************************************************
* @file		: uiappuser.h
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 11-Apr-2017
* @brief	: Event HandlerDeclarations
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
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __UIAPPUSER_H
#define __UIAPPUSER_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types --------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------*/
/* Exported macros -------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
 

/**
  * @brief Button click event handler
  * @note This function gets called when user clicks  bt1.
  * @param None
  * @retval None
  */
void home_bt1_Click(void);


/**
  * @brief Checkbox check event handler
  * @note This function gets called when user clicks cb1
  * @param None
  * @retval None
  */
void home_cb1_CheckChanged(void);


/**
  * @brief Option button selected event handler
  * @note This function gets called when user selects option obt1
  * @param None
  * @retval None
  */
void home_obt1_Selected(void);


/**
  * @brief Switch toggle event handler
  * @note This function is called when user toggles the switch sw1
  * @param None
  * @retval None
  */
void home_sw1_Toggle(void);




/**
  * @brief Slidebar dragged event handler
  * @note This function is called when user drags the slideBar sb1.
  * @param None
  * @retval None
  */
void home_sb1_ValueChanged(void);



#ifdef __cplusplus
}
#endif

#endif /*__UIAPPUSER_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

