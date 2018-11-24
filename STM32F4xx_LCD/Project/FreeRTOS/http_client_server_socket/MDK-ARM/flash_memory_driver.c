/*
			CHAU PHUOC VU
*/



#include "flash_memory_driver.h"



#define	FLASH_USER_START_ADDR_DATA			ADDR_FLASH_SECTOR_8
#define	FLASH_USER_END_ADDR_DATA				ADDR_FLASH_SECTOR_9
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	


uint16_t	SaveHalfWordDataToFlash(uint32_t Address, uint16_t data)
{
	uint16_t i = 0;
	
	 FLASH_Unlock();
	 /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	if (FLASH_ProgramHalfWord(Address,data) != FLASH_COMPLETE)	
		return 1;
		FLASH_Lock(); 	
	return	0;	
}

uint16_t	ReadDataFromFlash(uint32_t Address)
{
	uint16_t data = 0;
	data = *(__IO uint32_t*)Address;
	return data;
}
