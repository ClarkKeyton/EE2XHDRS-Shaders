//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbRegionalSettingsDefs.h 11    7/01/05 3:42p Dsproul $
//
// DESCRIPTION:   Regional and civilization specific settings that is specified 
//				  in external db file
//
// AUTHOR:        Xinbo Kan
//
//===========================================================================

#ifndef DBREGIONALSETTINGSDEFS_H
#define DBREGIONALSETTINGSDEFS_H
#pragma once

#include "HdrMacros.h"
#include "LDataObj.h"

DATACLASS(TradeItem)
	DBINDEX(DbText)	m_Name;
	float			m_GoldBonus;	// bonus (percentage) for extra gold when trading this item
ENDCLASS

DATACLASS(RegionalSetting)
	enum eCivilizationRegion  m_Region;
	LSizedArray<VARDC> m_TradeItems;	// array of trade items
ENDCLASS

#endif // DBREGIONALSETTINGSDEFS_H
