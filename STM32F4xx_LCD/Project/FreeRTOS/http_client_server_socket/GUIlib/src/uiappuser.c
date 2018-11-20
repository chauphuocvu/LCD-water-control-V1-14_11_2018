/*******************************************************************************
* @file		: uiappuser.c
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
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
DosingTest DosingTest_Flag = StartStart;
/* External variables ----------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private defines -------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/
/*Start Screen */
void StartScreen_Setting(void)
{
	Show_SettingsScreen();
	DestroyPage(&StartScreen);
}
/*Settings Screen */
void SettingsScreen_Language(void)
{
}
////////////////////////////////////////////////////////////
void SettingsScreen_BackToStart(void)
{
	Show_StartScreen();
	DestroyPage(&SettingsScreen);
}
//////////////////////////////////////////////////////////////
void SettingsScreen_Parameters(void)
{
	Show_ParametersScreen();
	DestroyPage(&SettingsScreen);
}
//////////////////////////////////////////////////////////////
void SettingsScreen_Calibration(void)
{
}
//////////////////////////////////////////////////////////////
void SettingsScreen_DosingTest(void)
{
	switch (DosingTest_Flag)
	{
		case StartStart:
			Show_DosingTestStartStartScreen();	
			DestroyPage(&SettingsScreen);		
		break;
		case StartStop:
			Show_DosingTestStartStopScreen();		
			DestroyPage(&SettingsScreen);
		break;
		case StopStart:			
			Show_DosingTestStopStartScreen();	
			DestroyPage(&SettingsScreen);
		break;
		case StopStop :
			Show_DosingTestStopStopScreen();	
			DestroyPage(&SettingsScreen);
		break;
	}	
}
//////////////////////////////////////////////////////////////
void SettingsScreen_TypeOfProbe(void)
{
}





/*DosingTest Screen */
void DosingTestStartStartScreen_Back(void)
{
	
	Show_SettingsScreen();
	DosingTest_Flag = StartStart;
	DestroyPage(&DosingTestStartStartScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStartStartScreen_BackToStart(void)
{
	
	Show_StartScreen();
	DosingTest_Flag = StartStart;
	DestroyPage(&DosingTestStartStartScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStartStartScreen_StartDisinf(void)
{
	Show_DosingTestStopStartScreen();
	DestroyPage(&DosingTestStartStartScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStartStartScreen_StartPh(void)
{	
	Show_DosingTestStartStopScreen();
	DestroyPage(&DosingTestStartStartScreen);
}
/*DosingTestStopStart Screen */
void DosingTestStopStartScreen_Back(void)
{
	Show_SettingsScreen();
	DosingTest_Flag = StopStart;
	DestroyPage(&DosingTestStopStartScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStopStartScreen_BackToStart(void)
{	
	Show_StartScreen();
	DosingTest_Flag = StartStart;
	DestroyPage(&DosingTestStopStartScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStopStartScreen_StopDisinf(void)
{
	Show_DosingTestStartStartScreen();
	DestroyPage(&DosingTestStopStartScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStopStartScreen_StartPh(void)
{
	Show_DosingTestStopStopScreen();
	DestroyPage(&DosingTestStopStartScreen);
}
/*DosingTestStopStop Screen */
void DosingTestStopStopScreen_Back(void)
{
	Show_SettingsScreen();
	DosingTest_Flag = StopStop;
	DestroyPage(&DosingTestStopStopScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStopStopScreen_BackToStart(void)
{
	Show_StartScreen();
	DosingTest_Flag = StartStart;
	DestroyPage(&DosingTestStopStopScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStopStopScreen_StopDisinf(void)
{
	Show_DosingTestStartStopScreen();
	DestroyPage(&DosingTestStopStopScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStopStopScreen_StopPh(void)
{
	Show_DosingTestStopStartScreen();
	DestroyPage(&DosingTestStopStopScreen);
}
/*DosingTestStartStop Screen */
void DosingTestStartStopScreen_Back(void)
{
	Show_SettingsScreen();
	DosingTest_Flag = StartStop;
	DestroyPage(&DosingTestStartStopScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStartStopScreen_BackToStart(void)
{
	Show_StartScreen();
	DosingTest_Flag = StartStart;
	DestroyPage(&DosingTestStartStopScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStartStopScreen_StartDisinf(void)
{
	Show_DosingTestStopStartScreen();
	DestroyPage(&DosingTestStartStopScreen);
}
//////////////////////////////////////////////////////////////
void DosingTestStartStopScreen_StopPh(void)
{
	Show_DosingTestStartStartScreen();
	DestroyPage(&DosingTestStartStopScreen);
}








/*Parameters Screen */
void ParametersScreen_Back(void)
{
	Show_SettingsScreen();
	DestroyPage(&ParametersScreen);
}
////////////////////////////////////////////////////////////
void ParametersScreen_BackToStart(void)
{
	Show_StartScreen();
	DestroyPage(&ParametersScreen);
}
//////////////////////////////////////////////////////////////
void ParametersScreen_Pool(void)
{
	Show_ParametersPoolVolumeScreen();
	DestroyPage(&ParametersScreen);
}
//////////////////////////////////////////////////////////////
void ParametersScreen_Water(void)
{
}




/*ParametersPoolVolumePool Screen */
void ParametersPoolVolumeScreen_Back(void)
{
	Show_ParametersScreen();
	DestroyPage(&ParametersPoolVolumeScreen);
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_BackToStart(void)
{
	Show_StartScreen();
	DestroyPage(&ParametersPoolVolumeScreen);
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_inc(void)
{
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_dec(void)
{
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_OK(void)
{
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_FiltrationPeriod(void)
{
}



/*ParametersFitrationPeriod Screen */
void ParametersFitrationPeriodScreen_Back(void)
{
	Show_ParametersScreen();
	DestroyPage(&ParametersFitrationPeriodScreen);
}
///////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_BackToStart(void)
{
	Show_StartScreen();
	DestroyPage(&ParametersFitrationPeriodScreen);
}
//////////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_inc(void)
{}
	///////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_dec(void)
{}
	//////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_OK(void)
{}
	//////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_PoolVolume(void)
{}