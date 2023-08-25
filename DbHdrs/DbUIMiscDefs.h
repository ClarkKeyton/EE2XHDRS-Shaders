//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbUIMiscDefs.h 3     10/25/04 11:51a Rbradford $
//
// DESCRIPTION:	
//
// AUTHOR:      Daniel Sproul
//
//===========================================================================

#ifndef DB_UIMISCDEFS_H
#define DB_UIMISCDEFS_H
#pragma once

#include "HdrMacros.h"


//
// numerical formatting types for amounts, bonuses, etc
//
ENUM eUIFormatType {
	kUIFormatType_Unspecified,

	kUIFormatType_Amount,
	kUIFormatType_AmountMod,

	kUIFormatType_CurrentMax,
	kUIFormatType_CurrentMaxMod,

	kUIFormatType_Percent,
	kUIFormatType_PercentBonus,
};


//
// data class for unit info bonuses
//
DATACLASS(DbUIBonusDef)

	// icon for the bonus
	DBINDEX(DbSprite)	m_icon;

	// tooltips
	DBINDEX(DbText)		m_tooltip;
	DBINDEX(DbText)		m_tooltipWithMod;
	DBINDEX(DbText)		m_verboseTooltip;
	DBINDEX(DbText)		m_verboseTooltipWithMod;

	// numerical formatting types
	enum eUIFormatType	m_format;
	enum eUIFormatType	m_tooltipFormat;		// if unspecified, uses m_format
	enum eUIFormatType	m_tooltipModFormat;

ENDCLASS


//
// inherited data class for unit info meters
//
DATACLASS_INHERIT(DbUIMeterDef, DbUIBonusDef)

	// spectrum of colors (from empty to full)
	LSizedArray<DBINDEX(DbColor)>	m_colors;

ENDCLASS

//
// audio samples available for testing in settings screen
//
DATACLASS(DbNamedAudioSample)
	DBINDEX(DbText) m_dbNameIndex;			// index of display name of audio sample in text db
	DBINDEX(DbSound) m_dbSoundIndex;		// index of sound in sound db
ENDCLASS

DATACLASS(DbNamedAudioSampleSet)
	LSizedArray<DC(DbNamedAudioSample)*> m_namedAudioSamples;	// array of named audio samples
ENDCLASS

#endif // DB_UIMISCDEFS_H
