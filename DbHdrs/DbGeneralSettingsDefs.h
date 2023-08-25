//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbGeneralSettingsDefs.h 17    9/06/05 4:06p Dsproul $
//
// DESCRIPTION:   DbGeneralSettingsDefs.h holds general user settings.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBGENERALSETTINGSDEFS_H
#define DBGENERALSETTINGSDEFS_H
#pragma once

#include "hdrmacros.h"
#include "GDbTooltipDefs.h"

ENUM eChatMsgFilter {
	kChatMsgFilter_On,
	kChatMsgFilter_Off,
	kChatMsgFilter_AlliesOnly,
};

//	IMPORTANT NOTE:  THE USE OF THIS DATACLASS IN AUDIOSETTINGS.H PRECLUDES
//	YOU FROM PUTTING ANY POINTERS OR SUCH THINGS INTO IT.  LIMIT THIS TO
//	BOOLS, INTEGERS, FLOATS, ENUMS, AND EMBEDDED ARRAYS OF THESE PRIMITIVES.
//	NO STRINGS, EMBEDDED DATACLASS OBJECTS, OR SIZED ARRAYS.  IF THIS RESTRICTION
//	IS TOO LIMITING, THE AUDIOSETTINGS OBJECT MUST BE MODIFIED TO USE A POINTER
//	TO AN OBJECT OF THIS DATACLASS INSTEAD OF AN ACTUAL INSTANCE OF ONE, AND
//	MUST USE LDATACLASS METHODS TO MANAGE THE PTRS PROPERLY.

DATACLASS(DbGeneralSettingsDef)

	////////////////////////////
	//
	// settings exposed to the general settings panel
	//

	// autosave settings
	int					m_fAutosaveFrequency;// time [seconds] btwn autosaves
	int					m_numAutosaves;		// number of autosaves to store on HDD
	
	// mouse settings
	bool				m_bLeftMouse;		// left/right mouse?
	float				m_fMouseSensitivity;	// mouse sensitivity
	float				m_fDoubleClickTime;	// time allowed between double clicks

	// miscellaneous settings
	enum eTooltipsMode	m_eTooltipsMode;	// tooltips mode
	enum eHotkeysMode	m_eHotkeysMode;		// hotkeys mode (simple or advanced)
	float				m_fScrollSpeed;		// map scrolling speed
	enum eChatMsgFilter	m_eChatMsgFilter;	// type of chat messages allowed/disallowed
	bool				m_bChatProfanityFilterOn;	// chat profanity filter on/off
	bool				m_bSystemMsgsOn;	// system messages on or off?
	bool				m_bRecordGame;		// auto record games?
	bool				m_bAllowUnitsInMultGroups;		// allow units in multiple ctrl groups?
	bool				m_bSingleClickToSelectGroup;	// should a single click select an entire group?
	bool				m_bInstantTooltips;	// are tooltips instant?
	bool				m_bAdvancedUser;	// am I an advanced user?

	////////////////////////////
	//
	// ui state
	// these are not exposed to options panels, but the state is remembered all the same
	//
	
	// top banner:
	bool				m_showControlGroupsFlyout;
	bool				m_showButtonsFlyout;
	
	// clock and calendar:
	bool				m_showClock;
	bool				m_showCalendar;

	// minimap:
	bool				m_minimapTerritories;
	bool				m_minimapWarplans;

	// fullmap:
	bool				m_fullmapMobileUnits;
	bool				m_fullmapBuildings;
	bool				m_fullmapRoadsAndBridges;
	bool				m_fullmapResources;
	bool				m_fullmapAmbients;
	bool				m_fullmapBattles;
	bool				m_fullmapTerritories;
	bool				m_fullmapCityNames;
	bool				m_fullmapTerritoryNames;
	// @EE2X - Josh - 04/05/05 - Flag System
	bool				m_fullmapFlags;
	// @EE2X @MRC Control Group warplans
	bool				m_fullmapControlGroups;

ENDCLASS

#endif // DBGENERALSETTINGSDEFS_H
