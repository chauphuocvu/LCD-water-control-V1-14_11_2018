/*******************************************************************************
* @file		: uiframework.h
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
* @brief	: Screen Declarations
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
#ifndef __UIFRAMEWORK_H
#define __UIFRAMEWORK_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "graphicObjectTypes.h"
#include "graphicObject.h"

/* Exported types --------------------------------------------------------------*/
extern GL_Page_TypeDef *CurrentScreen;
extern GL_Page_TypeDef StartScreen;
extern GL_Page_TypeDef SettingsScreen;
extern GL_Page_TypeDef DosingTestStartStartScreen;
extern GL_Page_TypeDef DosingTestStopStartScreen;
extern GL_Page_TypeDef DosingTestStopStopScreen;
extern GL_Page_TypeDef DosingTestStartStopScreen;
extern GL_Page_TypeDef ParametersScreen;
extern GL_Page_TypeDef ParametersPoolScreen;
extern GL_Page_TypeDef ParametersPoolVolumeScreen;
/*Added by chau phuoc vu 14/11/2018*/
void DelayScreen_Decrement(void);
void DelayScreen(uint16_t time);
static uint16_t delayscreen = 0;
/* Exported constants ----------------------------------------------------------*/

#define DesignLabel01Color 					65535
#define DesignLabel02Color 					65535
/* Exported macros -------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
/*Create Screen*/
void Create_StartScreen(void);
void Create_SettingsScreen(void);
/*Create DosingTest Screen*/
void Create_DosingTestStartStartScreen(void);
void Create_DosingTestStopStartScreen(void);
void Create_DosingTestStopStopScreen(void);
void Create_DosingTestStartStopScreen(void);
void Create_ParametersPoolScreen(void);


/*Show Screen*/
void Show_HomeScreen(void);
void Show_StartScreen(void);
void Show_SettingsScreen(void);
/*Show DosingTest Screen*/
void Show_DosingTestStartStartScreen(void);
void Show_DosingTestStopStartScreen(void);
void Show_DosingTestStopStopScreen(void);
void Show_DosingTestStartStopScreen(void);
void Show_ParametersScreen(void);
void Show_ParametersPoolVolumeScreen(void);

#ifdef __cplusplus
}
#endif

#endif /*__UIFRAMEWORK_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

