//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DBCivilizationDefs.h 3     8/01/05 10:35a Mcorthell $
//
// DESCRIPTION:		dataclasses for the civilizations databases (built-in and custom)
//
// AUTHOR:			Daniel Sproul
//
//===========================================================================

#ifndef DBCIVILIZATIONDEFS_H
#define DBCIVILIZATIONDEFS_H
#pragma once


#include "HdrMacros.h"


////////////////////////////////
//
// helper Civ dataclasses

/////////////////////////////////////////////
// base DC for leader names
DATACLASS(DbLeaderNameDefBase)
	// crown type
	enum eCrownType	m_Crown;

	// epoch range
	int	m_StartEpoch;
	int	m_EndEpoch;
ENDCLASS

/////////////////////////////////////////////
// DC for localized leader names
DATACLASS_INHERIT(DbLeaderNameDef, DbLeaderNameDefBase)
	// localized name
	DBINDEX(DBText)	m_Name;
ENDCLASS

/////////////////////////////////////////////
// DC for non-localized leader names
DATACLASS_INHERIT(DbCustomLeaderNameDef, DbLeaderNameDefBase)
	// name
	char *m_Name;
ENDCLASS

/////////////////////////////////////////////
// DC for auto-researched techs in a given epoch
DATACLASS(DbEpochTechSetDef)
	// epoch
	int m_Epoch;

	// techs
	LSizedArray< DBINDEX(DbTechTreeBaseNode) > m_Techs;
ENDCLASS


////////////////////////////////
//
// Civ dataclasses

/////////////////////////////////////////////
// base DC for built-in civs and custom civs
DATACLASS(DbCivDefBase)
	// civ attributes
	LSizedArray< DBINDEX(DbTechTreeBaseNode) > m_CivAttributes;

	// unique units
	LSizedArray< DBINDEX(DbTechTreeBaseNode) > m_UniqueUnits;

	// auto-researched techs
	LSizedArray< DC(DbEpochTechSetDef) * > m_AutoResearchedTechs;
ENDCLASS

/////////////////////////////////////////////
// DC for built-in civs
DATACLASS_INHERIT(DbCivDef, DbCivDefBase)
	// localized name
	// filled in at run-time based on tx_enum_ePlayerCivilization_*
	USER int m_Name;

	// localized city names
	LSizedArray< DBINDEX(DbText) > m_CityNames;

	// localized territory names
	LSizedArray< DBINDEX(DbText) > m_TerritoryNames;

	// localized player names
	LSizedArray< DBINDEX(DbText) > m_PlayerNames;

	// localized leader names
	LSizedArray< DC(DbLeaderNameDef) * > m_LeaderNames;

	// at run-time, the auto-researched tech set is sorted into here by epoch
	// (the epoch 0 and 15 slots will always be NULL, as will any unspecified epochs)
	// @NOTE I really wanted this to be an LDynArray of LSizedArray<int> *, but the parser can't handle that...)
	USER LDynArray< DC(DbEpochTechSetDef) * > m_SortedAutoResearchedTechs;
ENDCLASS

/////////////////////////////////////////////
// DC for custom civs
DATACLASS_INHERIT(DbCustomCivDef, DbCivDefBase)
	// name
	char *m_Name;

	// region
	enum eCivilizationRegion m_Region;

	// city names
	LSizedArray< char * > m_CityNames;

	// territory names
	LSizedArray< char * > m_TerritoryNames;

	// leader names
	LSizedArray< DC(DbCustomLeaderNameDef) * > m_LeaderNames;

	// we flag whether or not each custom civ is valid for actual use
	// (if a user hand-edits their custom civ files, they can create illegal custom civs)
	USER bool m_bIsValid;
ENDCLASS

// Defines a set of civilization attributes that are mutually exclusive.  That is,
// if a civilization has one attribute in this set, it may not have any others.
DATACLASS(DbCivAttributeExclusiveSet)
	LSizedArray<DBINDEX(DbTechTreeBaseNode)>	m_civAtts;
ENDCLASS

// Collects one or more sets of mutually exclusive civ attributes.
DATACLASS(DbCivAttributeExclusive)
	LSizedArray<DC(DbCivAttributeExclusiveSet) * >	m_sets;
ENDCLASS

#endif // DBCIVILIZATIONDEFS_H
