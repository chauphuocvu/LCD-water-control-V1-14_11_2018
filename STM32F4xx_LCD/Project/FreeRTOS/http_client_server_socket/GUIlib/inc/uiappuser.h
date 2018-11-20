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
typedef enum {StartStart, StartStop,
							StopStart,  StopStop} DosingTest;
extern DosingTest Dosingtest_Flag ;
/* Exported constants ----------------------------------------------------------*/
/* Exported macros -------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
 
/* Control command*/
/*Start Screen */
void StartScreen_Setting(void);
/*Settings Screen */
void SettingsScreen_Language(void);
void SettingsScreen_BackToStart(void);
void SettingsScreen_Parameters(void);
void SettingsScreen_Calibration(void);
void SettingsScreen_DosingTest(void);
void SettingsScreen_TypeOfProbe(void);
							
							
							
/*DosingTestStartStart Screen */
void DosingTestStartStartScreen_Back(void);
void DosingTestStartStartScreen_BackToStart(void);
void DosingTestStartStartScreen_StartDisinf(void);
void DosingTestStartStartScreen_StartPh(void);



/*DosingTestStopStart Screen */
void DosingTestStopStartScreen_Back(void);
void DosingTestStopStartScreen_BackToStart(void);
void DosingTestStopStartScreen_StopDisinf(void);
void DosingTestStopStartScreen_StartPh(void);



/*DosingTestStopStop Screen */
void DosingTestStopStopScreen_Back(void);
void DosingTestStopStopScreen_BackToStart(void);
void DosingTestStopStopScreen_StopDisinf(void);
void DosingTestStopStopScreen_StopPh(void);



/*DosingTestStartStop Screen */
void DosingTestStartStopScreen_Back(void);
void DosingTestStartStopScreen_BackToStart(void);
void DosingTestStartStopScreen_StartDisinf(void);
void DosingTestStartStopScreen_StopPh(void);



/*Parameters Screen */
void ParametersScreen_Back(void);
void ParametersScreen_BackToStart(void);
void ParametersScreen_Pool(void);
void ParametersScreen_Water(void);



/*ParametersVolumePool Screen */
void ParametersPoolVolumeScreen_Back(void);
void ParametersPoolVolumeScreen_BackToStart(void);
void ParametersPoolVolumeScreen_inc(void);
void ParametersPoolVolumeScreen_dec(void);
void ParametersPoolVolumeScreen_OK(void);
void ParametersPoolVolumeScreen_FiltrationPeriod(void);

/*ParametersFitrationPeriod Screen */
void ParametersFitrationPeriodScreen_Back(void);
void ParametersFitrationPeriodScreen_BackToStart(void);
void ParametersFitrationPeriodScreen_inc(void);
void ParametersFitrationPeriodScreen_dec(void);
void ParametersFitrationPeriodScreen_OK(void);
void ParametersFitrationPeriodScreen_PoolVolume(void);

#ifdef __cplusplus
}
#endif

#endif /*__UIAPPUSER_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

