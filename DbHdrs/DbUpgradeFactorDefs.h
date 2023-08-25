//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbUpgradeFactorDefs.h 7     4/25/05 11:04a Mcorthell $
//
// DESCRIPTION:	defines upgrade factors enum and auxiliary data class for the upgrade factors
//				used by DbUpgradeFactors
//
// AUTHOR:      Daniel Sproul
//
//===========================================================================

#ifndef DB_UPGRADEFACTORDEFS_H
#define DB_UPGRADEFACTORDEFS_H
#pragma once

#include "HdrMacros.h"


ENUM eDbUpgradeUnitTypeFactor {
	// This None fator should be listed first.  This way, if anyone creates
	// an UpgradeUnitTypeFactor without supplying which factor they wish to
	// upgrade, we'll be able to catch that case and handle it appropriately.
	kDbUpgradeUnitTypeFactor_None,	

	kDbUpgradeUnitTypeFactor_BuildingCaptureTime,
	kDbUpgradeUnitTypeFactor_CaptureResistance,
	kDbUpgradeUnitTypeFactor_ConversionResistance,
	kDbUpgradeUnitTypeFactor_ConversionRange,
	kDbUpgradeUnitTypeFactor_ConvertTimeModifier,
	kDbUpgradeUnitTypeFactor_Damage,
	kDbUpgradeUnitTypeFactor_AreaDamageRadius,
	kDbUpgradeUnitTypeFactor_GarrisonSlots,		// number of slots for garrisoning
	kDbUpgradeUnitTypeFactor_GarrisonHealRate,	// rate of healing units garrisoned in this unit
	kDbUpgradeUnitTypeFactor_GatherFoodFarming,
	kDbUpgradeUnitTypeFactor_GatherFood,
	kDbUpgradeUnitTypeFactor_GatherFoodForageTree,	// rate of gathering food from "forage trees"
	kDbUpgradeUnitTypeFactor_GatherFoodAnimal,		// rate of gathering food from dead animals
	kDbUpgradeUnitTypeFactor_GatherWood,
	kDbUpgradeUnitTypeFactor_GatherStone,
	kDbUpgradeUnitTypeFactor_GatherGold,
	kDbUpgradeUnitTypeFactor_GatherTin,
	kDbUpgradeUnitTypeFactor_GatherIron,
	kDbUpgradeUnitTypeFactor_GatherSaltpeter,
	kDbUpgradeUnitTypeFactor_GatherOil,
	kDbUpgradeUnitTypeFactor_GatherUranium,
	kDbUpgradeUnitTypeFactor_GatherTech,
	kDbUpgradeUnitTypeFactor_HealingRate,
	kDbUpgradeUnitTypeFactor_HealingRadius,
	kDbUpgradeUnitTypeFactor_HitPoints,
	kDbUpgradeUnitTypeFactor_LOS,
	kDbUpgradeUnitTypeFactor_PopCap,
	kDbUpgradeUnitTypeFactor_PowerRechargeTime,
	kDbUpgradeUnitTypeFactor_Range,
	kDbUpgradeUnitTypeFactor_ReloadTime,
	kDbUpgradeUnitTypeFactor_Speed,
	kDbUpgradeUnitTypeFactor_TradeRouteDrop,
	kDbUpgradeUnitTypeFactor_TradeLoadTime,				// Upgrade the time it takes to load trade units at a building.
	kDbUpgradeUnitTypeFactor_ICBMTargetingProbability,	// turn ability to target/shoot down ICBMs
	kDbUpgradeUnitTypeFactor_LatentAttackAbility,		// toggle latent state of attack ability on/off
	kDbUpgradeUnitTypeFactor_TechOnGatherIntel,			// amount of tech points awarded when spy gathers intelligence
	kDbUpgradeUnitTypeFactor_ParatrooperPlaneCapacity,
	kDbUpgradeUnitTypeFactor_SpeedAffectedByWeather,	// toggle speed modification due to weather
	// @EE2X @MRC Bonus resources given when they're dropped at this building
	kDbUpgradeUnitTypeFactor_DropoffBonusFood,				
	kDbUpgradeUnitTypeFactor_DropoffBonusWood,				
	kDbUpgradeUnitTypeFactor_DropoffBonusStone,				
	kDbUpgradeUnitTypeFactor_DropoffBonusGold,				
	kDbUpgradeUnitTypeFactor_DropoffBonusTin,				
	kDbUpgradeUnitTypeFactor_DropoffBonusIron,				
	kDbUpgradeUnitTypeFactor_DropoffBonusSaltpeter,				

	// city related upgradable value
	kDbUpgradeUnitTypeFactor_CityRadius,
	kDbUpgradeUnitTypeFactor_CityHealRate,
	kDbUpgradeUnitTypeFactor_CityCaptureResistance,
	
	// Techtree upgrades
	kDbUpgradeUnitTypeFactor_BuildTime,
	kDbUpgradeUnitTypeFactor_Cost,			// cost of all resources (except tech pts)
	kDbUpgradeUnitTypeFactor_CostBasic,		// cost of all basic resources
	kDbUpgradeUnitTypeFactor_CostSpecial,	// cost of all special resources
	kDbUpgradeUnitTypeFactor_CostFood,
	kDbUpgradeUnitTypeFactor_CostWood,
	kDbUpgradeUnitTypeFactor_CostStone,
	kDbUpgradeUnitTypeFactor_CostGold,
	kDbUpgradeUnitTypeFactor_CostTin,
	kDbUpgradeUnitTypeFactor_CostIron,
	kDbUpgradeUnitTypeFactor_CostSaltpeter,
	kDbUpgradeUnitTypeFactor_CostOil,
	kDbUpgradeUnitTypeFactor_CostUranium,
	kDbUpgradeUnitTypeFactor_CostTech,
	// The last upgrade factor that requires a UnitType.
	kDbUpgradeUnitTypeFactor_LastUnitRelatedUpgrade = kDbUpgradeUnitTypeFactor_CostTech,
	
	//Player Upgrades
	kDbUpgradeUnitTypeFactor_TributeTax,	//modify the tribute tax
	kDbUpgradeUnitTypeFactor_RegionalPowerRechargeTime,
	kDbUpgradeUnitTypeFactor_RegionalPowerDuration,

	// territory related upgradable values
	kDbUpgradeUnitTypeFactor_TerritoryMoraleBonus,
	kDbUpgradeUnitTypeFactor_TerritoryFervorBonus,
	kDbUpgradeUnitTypeFactor_TerritoryMaxMoraleFervorBonus,

	kDbUpgradeUnitTypeFactor_TerritoryFoodBonus,
	kDbUpgradeUnitTypeFactor_TerritoryGoldBonus,
	kDbUpgradeUnitTypeFactor_TerritoryStoneBonus,
	kDbUpgradeUnitTypeFactor_TerritoryWoodBonus,
	kDbUpgradeUnitTypeFactor_TerritoryGeneralResourceBonus,	// any other resource
	kDbUpgradeUnitTypeFactor_TerritoryMaxResourceBonus,

	kNumDbUpgradeUnitTypeFactors,			// number of such upgrade types
};


DATACLASS(DbUpgradeFactorDef)
	// the factor we upgrade (leave as _None to make a dummy factor for tooltip/icon purposes)
	enum eDbUpgradeUnitTypeFactor	m_factorType;

	// text string for tooltip (this will typically look like "%VALUE% Hit Points" or whatever)
	// (leave unspecified (0 or -1) for no tooltip)
	DBINDEX(DbText)					m_tooltip;

	// short numeric format string for use in graphical "tooltips"
	DBINDEX(DbText)					m_numericFormat;

	// icon to use for graphical 'tooltip' in the UI
	// (leave unspecified (0 or -1) for no icon)
	DBINDEX(DbSprite)				m_icon;
ENDCLASS



#endif // DB_UPGRADEFACTORDEFS_H
