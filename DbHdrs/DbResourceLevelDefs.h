//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbResourceLevelDefs.h 5     11/11/04 2:13p Rbradford $
//
// DESCRIPTION:   dataclass for starting resource levels
//
// AUTHOR:        Daniel Sproul (revised by Dan Conti)
//
//===========================================================================

#ifndef DBRESOURCELEVELDEFS_H
#define DBRESOURCELEVELDEFS_H
#pragma once

#include "HdrMacros.h"

// eResourceLevels -------------  
//  Starting resource levels

//@NOTE To add a new resource level type all that need to be done is the new type is added to this enum
//      and a corresponding text entry needs to be added to the enum text database for the 
//      eResourceLevels entries
ENUM eResourceLevels {

	kResourceLevels_Low,
	kResourceLevels_Defensive,
	kResourceLevels_Standard,
	kResourceLevels_High,
	kResourceLevels_DeathMatch,
	kNumResourceLevels,

};

DATACLASS(DbResourceDistributionDef)
	enum eResourceLevels m_level;
	float  m_numFishPerWaterVertex;
	int32 m_numDomesticHerdsPerStartLoc;
	float m_numResourcesPerTerritory;
	float  m_numWildHerdsPerTerritory;
	float  m_numPredatorsPerTerritory;
ENDCLASS

DATACLASS(DbResourceLevel)
	int m_epoch;					//epoch this level belongs to
	enum eResourceLevels m_level;	//resource level type

	uint16 m_amountFood;                // amount (food)
	uint16 m_amountWood;                // amount (wood)
	uint16 m_amountStone;               // amount (stone)
	uint16 m_amountGold;                // amount (gold)
	uint16 m_amountTin;                 // amount (tin)
	uint16 m_amountIron;                // amount (iron)
	uint16 m_amountSaltpeter;           // amount (saltpeter)
	uint16 m_amountOil;                 // amount (oil)
	uint16 m_amountUranium;             // amount (uranium)
	uint16 m_amountTech;                // amount (techpoints)						// if you change eResourceType, you should make sure this is still correct
ENDCLASS



#endif // DBRESOURCELEVELDEFS_H
