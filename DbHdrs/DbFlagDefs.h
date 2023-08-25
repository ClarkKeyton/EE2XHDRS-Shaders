//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbFlagDefs.h 2     4/12/05 2:26p Jlandry $
//
// DESCRIPTION:   This holds the enums and DCs related to the flag system.
//
// AUTHOR:        Josh Landry
//
//===========================================================================

#ifndef DBFLAGDEFS_H
#define DBFLAGDEFS_H
#pragma once

#include "HdrMacros.h"
#include "LSizedArray.h"
#include "LDataObj.h"

//These are the flag types.
ENUM eFlagType {
	kFlagType_Invalid = -1,

	kFlagType_Naval,
	kFlagType_Air,
	kFlagType_Infantry,
	kFlagType_Mobile,
	kFlagType_Machine,
	kFlagType_Cultural,
	kFlagType_Religious,
	kFlagType_Financial,

	kNumFlagTypes,
};

//This is a shorthand for what descendant dataclass a FlagFormulaFactor is.
ENUM eFlagReqFactor {
	kFlagReqFactor_UnitsProduced,
	kFlagReqFactor_TechsResearched,
};

ENUM eFlagReqTechType {
	kFlagReqTechType_None = -1,	
	kFlagReqTechType_Naval = 0,
	kFlagReqTechType_Infantry,
	kFlagReqTechType_Mobile,
	kFlagReqTechType_Machine,
	kFlagReqTechType_Spy,
	kFlagReqTechType_University,
	kFlagReqTechType_Priest,
	kFlagReqTechType_Temple,
	kFlagReqTechType_Trade,
	kFlagReqTechType_PriestSpy,
	kFlagReqTechType_TempleUniversity,	
};

const int kNumFlagReqTechTypes = 1 + kFlagReqTechType_Trade - kFlagReqTechType_Naval;

//a FlagRequirementFactor expresses a requirement a player must meet in order to win a flag
DATACLASS(FlagRequirementFactor)
	int m_Required;								//amount required
	enum eFlagReqFactor m_FactorType;		// requirement factor type
	enum eFlagReqTechType m_Type;				//which techs count (only for Techs Researched factor)
ENDCLASS

DATACLASS(FlagRequirementSet)
	LSizedArray<DC(FlagRequirementFactor)*> m_Requirements;	//The list of FlagRequirementFactors that must be met
ENDCLASS


DATACLASS(DbFlagDef)
	LSizedArray<DC(FlagRequirementSet)*> m_RequirementSets;	// the requirement sets for winning this flag (the player must
														// meet all requirements in at least one of the sets to get the flag)
	DBINDEX(DbUnitTypeAttribute) m_ProductionAttribute;	// attribute for units to produce to win the flag
	DBINDEX(DbUnitTypeAttribute) m_Attribute;	// attribute for building that the flag can be placed on
	DBINDEX(DbAreaEffects) m_Effect;			// area effect to apply to building the flag is placed on
ENDCLASS



#endif // DBFLAGDEFS_H
