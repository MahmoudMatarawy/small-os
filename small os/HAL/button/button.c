/*
 * button.c
 *
 * Created: 5/30/2023 2:38:59 AM
 *  Author: Mahmoud Sarhan
 */ 

#include "button.h"
#include "../../MCAL/dio/dio.h"
#include "button_pre_linking_cfg.h"

extern const st_btnConfig_t arr_st_gc_btnConfig[INVALID_BUTTON_ID];
static st_btnConfig_t st_gs_strBtnInfo[INVALID_BUTTON_ID];



/******************************************************************************/
/*********************** Private Functions Declaration ************************/
/******************************************************************************/
static void vidUpdateBtnState(en_btnId_t en_a_BtnId);
static void vidPrePushState(en_btnId_t en_a_BtnId);
static void vidPushState(en_btnId_t en_a_BtnId);
static void vidPreHoldState(en_btnId_t en_a_BtnId);
static void vidHoldState(en_btnId_t en_a_BtnId);
static void vidPreReleaseState(en_btnId_t en_a_BtnId);
static void vidReleaseState(en_btnId_t en_a_BtnId);





/******************************************************************************/
/*********************** Public Functions Implementation **********************/
/******************************************************************************/



void BUTTON_mainTask(void)
{
	uint8_t u8Index;
	
	
	for(u8Index=0;u8Index<INVALID_BUTTON_ID; u8Index++)
	{
		vidUpdateBtnState((en_btnId_t)u8Index);
	}
}
en_btnState_t BUTTON_init(en_btnId_t en_btnId)
{
	uint8_t u8_RetVal = BT_PRE_PUSH;
	if (INVALID_BUTTON_ID <= en_btnId)
	{
		u8_RetVal = BT_UNDEFINED;
	}
	else
	{
		// Set button pin as input
		u8_RetVal = DIO_init(arr_st_gc_btnConfig[en_btnId].u8_a_port, arr_st_gc_btnConfig[en_btnId].u8_a_pin , STD_INPUT);
		// Enable PULLUP
		u8_RetVal = DIO_writePIN(arr_st_gc_btnConfig[en_btnId].u8_a_port, arr_st_gc_btnConfig[en_btnId].u8_a_pin, STD_HIGH);
		st_gs_strBtnInfo[en_btnId].u8_a_btnState     = BT_PRE_PUSH;
		st_gs_strBtnInfo[en_btnId].u8_a_debounceThreshold  = ((uint8_t)0U);
		st_gs_strBtnInfo[en_btnId].u8_a_holdThreshold      = ((uint8_t)0U);
		st_gs_strBtnInfo[en_btnId].u8_a_port = arr_st_gc_btnConfig[en_btnId].u8_a_port;
		st_gs_strBtnInfo[en_btnId].u8_a_pin = arr_st_gc_btnConfig[en_btnId].u8_a_pin;
		if (DIO_E_OK == u8_RetVal)
		{
			//do nothing
		}
		else
		{
			u8_RetVal = BT_UNDEFINED;
		}
	}
	return u8_RetVal;
}
en_btnState_t BUTTON_getState(en_btnId_t en_btnId)
{
	en_btnState_t enuReturn;
	
	if(INVALID_BUTTON_ID > en_btnId)
	{
		enuReturn = st_gs_strBtnInfo[en_btnId].u8_a_btnState ;
	}
	else
	{
		enuReturn = BT_UNDEFINED;
	}
	
	return (enuReturn);
}



/******************************************************************************/
/*********************** Private Functions Implementation *********************/
/******************************************************************************/
static void vidUpdateBtnState(en_btnId_t en_a_BtnId)
{
	switch(st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState)
	{
		case BT_PRE_PUSH:
		vidPrePushState(en_a_BtnId);
		break;
		
		case BT_PUSHED:
		vidPushState(en_a_BtnId);
		break;
		
		case BT_PRE_HOLD:
		vidPreHoldState(en_a_BtnId);
		break;
		
		case BT_HOLD:
		vidHoldState(en_a_BtnId);
		break;
		
		case BT_PRE_RELEASE:
		vidPreReleaseState(en_a_BtnId);
		break;
		
		case BT_RELEASED:
		vidReleaseState(en_a_BtnId);
		break;
		
		default:
		break;
	}
}
static void vidPrePushState(en_btnId_t en_a_BtnId)
{
	uint8_t u8BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].u8_a_port), (st_gs_strBtnInfo[en_a_BtnId].u8_a_pin),&u8BtnValue);
	
	if(u8BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PUSHED;
	}
	else
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_PUSH;
	}
}
static void vidPushState(en_btnId_t en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].u8_a_port), (st_gs_strBtnInfo[en_a_BtnId].u8_a_pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState = BT_PRE_HOLD;
	}
	else
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState = BT_RELEASED;
	}
}
static void vidPreHoldState(en_btnId_t en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].u8_a_port), (st_gs_strBtnInfo[en_a_BtnId].u8_a_pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState   = BT_HOLD;
	}
	else
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_RELEASED;
	}
}
static void vidHoldState(en_btnId_t en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].u8_a_port), (st_gs_strBtnInfo[en_a_BtnId].u8_a_pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold++;
		if(st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold >= arr_st_gc_btnConfig[en_a_BtnId].u8_a_debounceThreshold)
		{
			st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold = ((uint8_t)0);
			st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_RELEASE;
		}
		else
		{
			/* Do Nothing */
		}
		
	}
	else
	{
		// do nothing
	}
}
static void vidPreReleaseState(en_btnId_t en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].u8_a_port), (st_gs_strBtnInfo[en_a_BtnId].u8_a_pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold++;
	}
	else
	{
		if(st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold >= arr_st_gc_btnConfig[en_a_BtnId].u8_a_debounceThreshold)
		{
			st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState = BT_RELEASED;
		}
		else
		{
			st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_PUSH;
		}
		st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold = ((uint8_t)0);
	}
}
static void vidReleaseState(en_btnId_t en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].u8_a_port), (st_gs_strBtnInfo[en_a_BtnId].u8_a_pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_PUSH_LEVEL)
	{
		//strBtnInfo[enuBtnId].u8DebounceThreshold = ((uint8_t)0);
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_PUSH;
	}
	else
	{
		/* Do nothing */
	}
}
