//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbAutoBalanceDefs.h 7     9/13/04 2:39p Jdunlop $
//
// DESCRIPTION:	DbAutoBalanceDefs.h contains database header info for autobalancing
//
// AUTHOR:		Jason Dunlop
//
//===========================================================================

#ifndef DBAUTOBALANCEDEFS_H
#define DBAUTOBALANCEDEFS_H
#pragma once

#include "HdrMacros.h"
#include "DbPlayerDefs.h"
#include "DbTechTreeDefs.h"

// information used for a run
DATACLASS(DbAutoBalanceInfo)
	int							m_iResAmtA;		// amount of resources to spend on units
	enum ePlayerCivilization	m_eCivA;		// civilization of unit type A
	int							m_iEpochA;		// epoch of type A
	DBINDEX(DbFormation)		m_iFormationA;	// formation for A units
	int							m_iResAmtB;		// amount of resources to spend on units
	enum ePlayerCivilization	m_eCivB;		// civilization of unit type B
	int							m_iEpochB;		// epoch of unit type B
	DBINDEX(DbFormation)		m_iFormationB;	// formation for B units
	int							m_iMonth;		// month this takes place during
	int							m_iTimeout;		// timeout value in case battle doesn't finish
	int							m_iNumTests;	// the number of times to run this test
	float						m_fDamageModifer;	// total damage dealt modifier
	float						m_fDeltaEpochDamageMod;	// delta damage change over epochs
ENDCLASS

// list of units used in an autobalance run
DATACLASS(DbAutoBalanceUnitList)
	char*						m_szUnitType;	// name of unit type
	char*						m_szUnitUpgrade;	// upgrade to apply to the unit type
ENDCLASS

// an AB run is composed of two unit lists and a series of run info.
DATACLASS(DbAutoBalanceRun)
	char*						m_szUnitsA;
	char*						m_szUnitsB;
	char*						m_szRunInfo;
ENDCLASS

#endif // DBAUTOBALANCEDEFS_H
