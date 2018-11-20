/*******************************************************************************
* @file		: uiappuser.h
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
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
  * @brief Option button selected event handler
  * @note This function gets called when user selects option DesignOptionButton01
  * @param None
  * @retval None
  */
void screen1_DesignOptionButton01_Selected(void);


/**
  * @brief Option button selected event handler
  * @note This function gets called when user selects option DesignOptionButton02
  * @param None
  * @retval None
  */
void screen1_DesignOptionButton02_Selected(void);


/**
  * @brief Button click event handler
  * @note This function gets called when user clicks  DesignButton01.
  * @param None
  * @retval None
  */
void screen1_DesignButton01_Click(void);



 

/**
  * @brief Button click event handler
  * @note This function gets called when user clicks  DesignButton02.
  * @param None
  * @retval None
  */
void screen2_DesignButton02_Click(void);

void screen1_cb1_CheckChanged(void);


#ifdef __cplusplus
}
#endif

#endif /*__UIAPPUSER_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

