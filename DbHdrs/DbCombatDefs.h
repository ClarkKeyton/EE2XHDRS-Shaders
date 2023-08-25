//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbCombatDefs.h 12    2/17/05 11:37a Bmorse $
//
// DESCRIPTION:	DbCombatDefs.h holds the structure of the combat database rows.
//
// AUTHOR:      Rex E. Bradford
//
//===========================================================================

#ifndef DBCOMBATDEFS_H
#define DBCOMBATDEFS_H
#pragma once

#include "HdrMacros.h"

#include "DbUnitDefEnums.h"	// RPS enums

// We lay these out one-by-one instead of in an array because the parser is very
// sad if it has to read in an array from multiple columns in a spreadsheet.
// But the next thing we do anyway is to pull these db rows into a combat table
// optimized for speed (a 2d array), and then we throw away the db.

// NOTE THAT ROWS ARE DEFENDERS, COLUMNS ARE ATTACKERS!

// NOTE THAT THIS MUST EXACTLY MATCH ENUM eUnitRPS in DbUnitDefEnums.h!

DATACLASS(DbCombatDef)
	uint16 m_null;				// 0th entry is reserved for unused
	uint16 m_lightInfantry;		// each column is an integer which describes the
	uint16 m_heavyInfantry;		// of the row's rps type against this particular
	uint16 m_lightArtillery;	// column.  0 means no attack is possible, 100 is
	uint16 m_antiAircraft;		// the default, and other numbers can be used as
	uint16 m_heavyArtillery;	// modifiers from the default (50 is half the
	uint16 m_lightMounted;		// default damage, 200 is twice the default, etc.)
	uint16 m_heavyMounted;
	uint16 m_citizen;
	uint16 m_priest;
	uint16 m_building;
	uint16 m_landNonCombat;
	uint16 m_Ram;
	uint16 m_herc;
	uint16 m_animal;
	uint16 m_closeAirSupport;		// air units
	uint16 m_airSuperiority;
	uint16 m_bomber;
	uint16 m_atomicBomber;
	uint16 m_Helicopter;
	uint16 m_airNonCombat;
	uint16 m_submarine;				// sea units
	uint16 m_submarineNuclear;
	uint16 m_warGalley;
	uint16 m_fightingSail;
	uint16 m_frigate;
	uint16 m_galleon;
	uint16 m_battleship;
	uint16 m_destroyer;
	uint16 m_carrier;
	uint16 m_transport;
	uint16 m_seaNonCombat;
	uint16 m_coastalDefense;
	uint16 m_BuildingCombat;
	uint16 m_SpecialForces;
ENDCLASS

// This dataclass is used for the "combat unit type adjustment table"
DATACLASS(DbCombatUnitTypeAdjustDef)
	DBINDEX(DbUpgrade) m_attacker;					// unit type variant, as denoted by upgrade index
	LSizedArray<DBINDEX(DbUpgrade)> m_defenders;	// defender variants
	int m_adj;										// 100 = no adjustment
ENDCLASS

#endif // DBCOMBATDEFS_H
