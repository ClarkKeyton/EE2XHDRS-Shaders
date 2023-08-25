//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbNativeTribesDefs.h 1     5/04/05 10:49a Dsproul $
//
// DESCRIPTION:		Dataclasses for Native Tribes stuff
//
// AUTHOR:			Daniel Sproul
//
//===========================================================================

#ifndef DBNATIVETRIBESDEFS_H
#define DBNATIVETRIBESDEFS_H
#pragma once


#include "HdrMacros.h"

// name of the native tribes power set
extern const char *kszNativeTribesPowerSet;


DATACLASS(DbNativeTribeDef)

	// display name to use
	DBINDEX(DbText)				m_DisplayName;

	// civ this tribe is based on
	enum ePlayerCivilization	m_Civ;

	// climates this tribe may appear in (if empty, then any climate is okay)
	LSizedArray< DBINDEX(DbClimate) > m_Climates;

	// powers this tribe may grant 
	// (only those present in "TheNativeTribesPowerSet" will be used)
	// (if empty, any power in "TheNativeTribesPowerSet" will be chosen)
	LSizedArray< DBINDEX(DbAreaEffects) > m_Powers;

	// starting forces
	enum eQuickStartEmpireType	m_StartingForcesEmpireType;
	enum eQuickStartForceComp	m_StartingForcesComposition;

	// resource mods for tribe assimilation
	float	m_NeutralResourceMod;
	float	m_HostileResourceMod;

ENDCLASS


// a single tribe-granted power
DATACLASS(DbNativeTribesPowerDef)

	// the power
	DBINDEX(DbAreaEffects)	m_Power;

	// cost modifier to assimilate (1.0 if not specified)
	float	m_AssimilationCostMod;

ENDCLASS

// the set of native tribes powers
// (single instance in misc-sim db kszNativeTribesPowerSet)
DATACLASS(DbNativeTribesPowerSetDef)

	// array of powers
	LSizedArray< DC(DbNativeTribesPowerDef) * > m_Powers;

ENDCLASS


#endif // DBNATIVETRIBESDEFS_H
