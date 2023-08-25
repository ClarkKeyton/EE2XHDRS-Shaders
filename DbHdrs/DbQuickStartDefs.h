//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbQuickStartDefs.h 9     7/19/05 2:27p Tteich $
//
// DESCRIPTION:   
//
// AUTHOR:        Daniel Sproul
//
//===========================================================================

#ifndef DBQUICKSTARTDEFS_H
#define DBQUICKSTARTDEFS_H
#pragma once

#include "hdrmacros.h"


//////////////////////////////////////
//
// quick start enumerations

//
// quick start army sizes
//
ENUM eQuickStartArmySize {
	kQuickStartArmySize_Advanced,
	kQuickStartArmySize_Large,
	kQuickStartArmySize_Huge,
	kNumQuickStartArmySizes,
};


// custom quick start setting
// value for edit all
const int kCustomQSSize_EditAll = -1;

//
// quick start empire types
//
ENUM eQuickStartEmpireType {
	kQuickStartEmpireType_Balanced,
	kQuickStartEmpireType_Military,
	kQuickStartEmpireType_Imperial,
	kQuickStartEmpireType_Economic,
	kNumQuickStartEmpireTypes,
};

// custom quick start empire type value
// this isn't in the enum because I don't want to mess with all the UI
// the uses it
const int kQuickStartEmpireType_Custom = -1;

//
// quick start force compositions
//
ENUM eQuickStartForceComp {
	kQuickStartForceComp_Standard,
	kQuickStartForceComp_Aggressive,
	kQuickStartForceComp_Defensive,
	kNumQuickStartForceCompositions,
};

//
// quick start entry classes
// (these mostly resolve some special case problems)
//
ENUM eQuickStartEntryClass {
	kQuickStartEntryClass_Standard,
	kQuickStartEntryClass_NotPlains,
	kQuickStartEntryClass_InAirport,
	kNumQuickStartEntryClasses,
};

ENUM eCustomQSFilter {
	kCustomQSFilter_Land,
	kCustomQSFilter_Naval,
	kCustomQSFilter_Air,

	kCustomQSFilter_All,
};

// the number of DIFFERENT filters (all doesn't count)
const int kNumCustomQSFilters = 3;




/////////////////////////////////////////
//
// quick start families

//
// single entry for a unit type family
// pairs unit type with weight
//
DATACLASS(DbQuickStartFamilyEntry)
	DBINDEX(DbUnit)	m_unitType;
	float			m_weight;		// weight in the family
	int				m_startEpoch;	// epoch to start using at
ENDCLASS

//
// a unit type family is just a list of unit type / weight pairs
//
DATACLASS(DbQuickStartFamily)
	LSizedArray<DC(DbQuickStartFamilyEntry)*> m_unitTypes;

ENDVARS
	// get array index of the best family member for the specified epoch
	// (implementation is in DbQuickStartFamilies.cpp)
	int FindBestForEpoch(int in_iEpoch) const;

ENDCLASS


//////////////////////////////////////
//
// primary quick start dataclass

//
// in the main quick start database
//
DATACLASS(DbQuickStartEntry)

	// unit type (if specified, family is ignored)
	DBINDEX(DbUnit) m_unitType;

	// family (for when a single unit type isn't good enough)
	DBINDEX(DbQuickStartFamilies) m_family;

	// class for this entry
	enum eQuickStartEntryClass m_class;

	// the amounts...
	// ideally we would have here an array of arrays of arrays of ints, but instead
	// we have several arrays just indexed by army size
	// (use GetAmount() for convenient access)
	
	// balanced
	int m_aBalancedStandardAmounts[3];
	int m_aBalancedAggressiveAmounts[3];
	int m_aBalancedDefensiveAmounts[3];
	
	// military
	int m_aMilitaryStandardAmounts[3];
	int m_aMilitaryAggressiveAmounts[3];
	int m_aMilitaryDefensiveAmounts[3];
	
	// imperial
	int m_aImperialStandardAmounts[3];
	int m_aImperialAggressiveAmounts[3];
	int m_aImperialDefensiveAmounts[3];
	
	// economic
	int m_aEconomicStandardAmounts[3];
	int m_aEconomicAggressiveAmounts[3];
	int m_aEconomicDefensiveAmounts[3];

ENDVARS

	// utility method to address the fact that this data (sadly) isn't sorted into arrays of arrays...
	// (implementation is in DbQuickStart.cpp)
	int GetAmount(	eQuickStartArmySize in_eArmySize, 
					eQuickStartEmpireType in_eEmpireType, 
					eQuickStartForceComp in_eForceComposition ) const;

	// get best unit type (as index into DbUnit) and corresponding amount for a particular epoch
	// (implementation is in DbQuickStart.cpp)
	bool GetUnitTypeAndAmountForEpoch(
		eQuickStartArmySize in_eArmySize,			// army size
		eQuickStartEmpireType in_eEmpireType,		// empire type
		eQuickStartForceComp in_eForceComposition,	// force composition
		int in_iEpoch,								// epoch
		int *out_pUnitTypeDbIndex,					// output -- unit type db index
		int *out_pAmount							// output -- amount
	) const;
	
	// just get the unittype
	bool GetUnitTypeForEpoch(int in_iEpoch, int* out_pUnitTypeDbIndex, float* out_pWeight = NULL) const;

ENDCLASS





#endif // DBQUICKSTARTDEFS_H
