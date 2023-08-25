//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DBTerritoryDefs.h 8     1/18/05 3:13p Aandkjar $
//
// DESCRIPTION:   
//
// AUTHOR:        Andrew Andkjar
//
//===========================================================================

#ifndef DBTERRITORYDEFS_H
#define DBTERRITORYDEFS_H
#pragma once

#include "HdrMacros.h"

// to get the (one and only) territory info data, use this name
static const char *s_pTerritoryInfoName = "TheTerritoryInfo";

// territory related upgradeable factors
DATACLASS(DbUpgradeableTerritoryFactors)
	float m_moraleBonusPerHouse;
	float m_moraleBonusAdditional;
	float m_fervorBonusPerHouse;
	float m_fervorBonusAdditional;
	float m_maxMoraleFervorBonus;

	float m_foodBonus;
	float m_goldBonus;
	float m_stoneBonus;
	float m_woodBonus;
	float m_generalResourceBonus;
	float m_maxResourceBonus;	// the maximum resource bonus
ENDCLASS

DATACLASS(DbTerritoryTypeCount)
	// unit type - count pair
	DBINDEX(DbUnit) m_type;
	int				m_count;
	bool			m_showInUI;		// should we show current/max for this type in the
									// UI info panel when a territory is selected?
	DBINDEX(DbText)	m_nameInUI;		// override display name to show in UI info panel
ENDCLASS


DATACLASS(DbTerritoryReq)
	// array of type - count pairs
	LSizedArray<DC(DbTerritoryTypeCount)*>	m_typeCounts;
ENDCLASS


DATACLASS(DbTerritoryInfo)
	// unit types and their minimum counts
	// to claim adjacent & nonadjacent territories
	DC(DbTerritoryReq)	*m_adjacentReq;
	DC(DbTerritoryReq)	*m_nonAdjacentReq;
	DC(DbTerritoryReq)	*m_parthenonReq;
	DC(DbTerritoryReq)	*m_kingOfTheHillReq;

	// unit types and their minimum counts
	// to keep territory ownership from being labeled "disputed"
	DC(DbTerritoryReq)	*m_undisputedReq;

	// unit types and their maximum count per territory
	DC(DbTerritoryReq)	*m_maximumReq;

	// territory related upgradeable factors
	DC(DbUpgradeableTerritoryFactors) *m_upgradeableFactors;

	// what to scale cost of buildings constructed in unclaimed territory by
	float m_unclaimedCostModifier;
	// what to scale cost of buildings constructed in territory claimed by others
	float m_otherClaimedCostModifier;
ENDCLASS


#endif // DBTERRITORYDEFS_H
