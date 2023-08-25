//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbCrownDefs.h 11    8/25/05 4:22p Jlandry $
//
// DESCRIPTION:   This holds the enums and DCs related to the crown system.
//
// AUTHOR:        Ben Morse
//
//===========================================================================

#ifndef DBCROWNDEFS_H
#define DBCROWNDEFS_H
#pragma once

#include "HdrMacros.h"
#include "LSizedArray.h"
#include "LDataObj.h"


// the number of technologies pertaining to a specific crown
// that must be researched before being crown eligible
// @NOTE there is nothing in this file dependent on this constant, but this seems like
// a more reasonable place for it to live than in UICrownStatus.h
const int kTechsPerCrown = 4;


//These are the three crown types.
ENUM eCrownType {
	kCrownType_Invalid = -1,

	kCrownType_Military,
	kCrownType_Economic,
	kCrownType_Imperial,

	kNumCrownTypes,
};



//This is a shorthand for what descendant dataclass a CrownFormulaFactor is.
ENUM eCrownFormulaFactor {
	kCrownFormulaFactor_UnitsKilled,
	kCrownFormulaFactor_UnitsProduced,
	kCrownFormulaFactor_UnitsConverted,
	kCrownFormulaFactor_TechsResearched,
	kCrownFormulaFactor_TradeRoutesOperating,
	kCrownFormulaFactor_ResourcesGathered,
	kCrownFormulaFactor_ResourcesTradeRoutesOperating,
	kCrownFormulaFactor_TechsStolen,
	kCrownFormulaFactor_TechPointsStolen,
	kCrownFormulaFactor_UnitsActive,
	kCrownFormulaFactor_ResourcesStolen,
	kCrownFormulaFactor_ClaimedTerritories,
	kCrownFormulaFactor_CostOfWonder,
	kCrownFormulaFactor_HeroesEarned,
	kCrownFormulaFactor_FlagsEarned,
	kCrownFormulaFactor_VassalsEarned,
	kCrownFormulaFactor_TribesAssimilated,
	kNumCrownFormulaFactors,
};

//a CrownFormulaFactor is something that expresses a number that gets
//added into a crown formula.
DATACLASS(CrownFormulaFactor)
	float m_Weight;	//multiplier for how much this should weigh in.
	USER enum eCrownFormulaFactor m_FactorType;	// code caches this for speed later.
ENDCLASS

DATACLASS_INHERIT(FactorUnitsKilled, CrownFormulaFactor)
	DBINDEX(DbUnitTypeAttribute) m_Attribute;	//what attribute to select.
ENDCLASS

DATACLASS_INHERIT(FactorUnitsProduced, CrownFormulaFactor)
	DBINDEX(DbUnitTypeAttribute) m_Attribute;	//what attribute to select.
ENDCLASS

DATACLASS_INHERIT(FactorUnitsConverted, CrownFormulaFactor)
	DBINDEX(DbUnitTypeAttribute) m_Attribute;	//what attribute to select.
ENDCLASS

DATACLASS_INHERIT(FactorTechsResearched, CrownFormulaFactor)
	enum eTechTreeBranch m_Branch;	//which branch we're counting.
ENDCLASS

DATACLASS_INHERIT(FactorTradeRoutesOperating, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorResourcesGathered, CrownFormulaFactor)
	enum eResourceType m_Type;		//what type of resources to respond to.
ENDCLASS

DATACLASS_INHERIT(FactorResourcesTradeRoutesOperating, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorTechsStolen, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorTechPointsStolen, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorUnitsActive, CrownFormulaFactor)
	DBINDEX(DbUnitTypeAttribute) m_Attribute;	//what attribute to select.
ENDCLASS

DATACLASS_INHERIT(FactorResourcesStolen, CrownFormulaFactor)
	enum eResourceType m_Type;		//what type of resources to respond to.
ENDCLASS

// how many territories has a player claimed?
DATACLASS_INHERIT(FactorClaimedTerritories, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorCostOfWonder, CrownFormulaFactor)
	int m_Percent;	//how much ... ??? Something?
ENDCLASS

DATACLASS_INHERIT(FactorHeroesEarned, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorFlagsEarned, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorVassalsEarned, CrownFormulaFactor)
ENDCLASS

DATACLASS_INHERIT(FactorTribesAssimilated, CrownFormulaFactor)
ENDCLASS


DATACLASS(CrownEffect)
	DBINDEX(DbAreaEffects) m_Effect;	// crown effect
	DBINDEX(DbSprite) m_Icon;			// icon for this effect
ENDCLASS


DATACLASS(DbCrownDef)
	LSizedArray<VARDC> m_Formula;	//The list of CrownFormulaFactors that go into this crown's formula.
	LSizedArray<int> m_ScoreTargets;	//the list of score targets by epoch.
	LSizedArray<DC(CrownEffect)*> m_EffectList; // the list of effects user can pick if they have this crown.
ENDCLASS


#endif // DBCROWNDEFS_H
