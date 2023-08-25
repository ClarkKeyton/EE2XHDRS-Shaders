//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbUpgradeDefs.h 82    9/21/05 3:35p Dsproul $
//
// DESCRIPTION:	DbUpgradeDefs.h is the header which defines data classes
//				used for upgrades.
//
// AUTHOR:      Rex E. Bradford
//
//===========================================================================

#ifndef DBUPGRADEDEFS_H
#define DBUPGRADEDEFS_H
#pragma once

#include "HdrMacros.h"
#include "DbFlagDefs.h"
#include "DbUnitDefs.h"
#include "DbResourceDefs.h"
#include "DbTechTreeDefs.h"
#include "LSizedArray.h"

class LDataObj;		// forward refs
enum eDbUpgradeUnitTypeFactor;

//	IMPORTANT NOTE:  IF YOU ADD NEW UPGRADE TYPES, YOU MUST ADD THEM TO
//	THE s_dcTranslationTable TABLE IN DbUpgrade.cpp!

//	Upgrade set
DATACLASS(DbUpgradeSet)
	LSizedArray<VARDC> m_upgrades;	// set of upgrades, embedded right inline
ENDCLASS

//	Upgrade reference set
DATACLASS(DbUpgradeRefSet)
	LSizedArray<DBINDEX(DbUpgrade)> m_upgrades;	// set of upgrades, referenced by name
ENDCLASS

// Upgrade to new epoch
DATACLASS(DbUpgradeEpoch)
	int m_epoch;					// new epoch number
ENDCLASS

//	Obsolete a techtree node
DATACLASS(DbUpgradeObsoleteTech)
	const char *m_tech;				// name of node to obsolete
ENDCLASS

//	Visual upgrade
DATACLASS(DbUpgradeVisual)
	const char *m_unitType;			// unit to upgrade
	const char *m_newVisual;		// new visual to apply
	const char *m_newUIVisual;		// new visual to use for UI (or NULL)
ENDCLASS

// Upgrade unit type
// @DANIEL 11/01/04 -- I am removing DbUpgradeUnitTypeUpgrade and renaming
// DbUpgradeUnitTypeUpgrade2 to be DbUpgradeUnitTypeUpgrade
DATACLASS(DbUpgradeUnitTypeUpgrade)
	const char *m_unitType;			// unit to upgrade
	const char *m_userUnitCategory;	// IGNORED, Steve wants this for sorting
	int m_userEpoch;				// IGNORED, Steve wants this
	float m_hitPoints;				// new hitpoints value, or 0
	float m_LOS;					// new LOS value, or 0
	float m_damage;					// new attack damage value, or 0
	float m_range;					// new range value, or 0
	float m_reloadTime;				// new reload time value, or 0
	float m_buildTime;				// time to build unit
	int16 m_food;					// new resource costs
	int16 m_wood;
	int16 m_stone;
	int16 m_gold;
	int16 m_tin;
	int16 m_iron;
	int16 m_saltpeter;
	int16 m_oil;
	int16 m_uranium;
	DBINDEX(DbText) m_name;			// new display name
	DBINDEX(DbText) m_namePlural;	// new display name (plural)
	const char *m_newVisual;		// new visual or NULL
	const char *m_newUIVisual;		// new visual to use for UI (or NULL)
	const char *m_icon;				// the sprite to upgrade to or NULL
	LRGBA m_mmColor;				// New minimap color.
	int m_popCapacity;				// New population capacity for this unit.
	DBINDEX(DbSprite) m_fullmapSprite;	// fullmap sprite to upgrade to or NULL		
	DBINDEX(DbText) m_ttIndex;		// new verbose tooltip text index
	LSizedArray<const char *> m_sndSel;			// selection sounds
	LSizedArray<const char *> m_sndCmdMove;		// cmd-move sounds
	LSizedArray<const char *> m_sndCmdAttack;	// cmd-attack sounds
	LSizedArray<const char *> m_sndDeath;		// death sounds
	LSizedArray<DBINDEX(DbUpgrade)> m_upgradeRefs;	// set of other upgrades, referenced by name
	enum eTechTreeCiv m_civ;		//if this node is civ specific
	USER int m_dbIndexSelf;			// what is my index in the upgrade table?
ENDCLASS

// Improve unit type
DATACLASS(DbUpgradeUnitTypeImprove)
	const char *m_unitType;			// unit to upgrade
	DBINDEX(DbText) m_name;			// new modified display name 
									// (this will be constructed using %NAME% as the unmodified name,
									// so if your base name is "Bowman" the name string "Veteran %NAME%" will
									// take you to "Veteran Bowman"
	//LSizedArray<VARDC> m_upgrades;	// set of upgrades, embedded right inline
	LSizedArray<DBINDEX(DbUpgrade)> m_upgradeRefs;	// set of other upgrades, referenced by name
ENDCLASS

//
// DbUpgradeIcon -- upgrade sprite for use with production/selection icons
//
DATACLASS(DbUpgradeIcon)
	const char *m_unitType;	// the unit type to upgrade
	const char *m_icon;		// the sprite to upgrade to
							// this is a char * and not a sprite index because
							// we do some processing to get regional variants...
ENDCLASS

//
// DbUpgradeFullmapOverlay -- upgrade sprite for use as overlay on fullmap
//								@NOTE this is very different from DbUpgradeOverlay
DATACLASS(DbUpgradeFullmapOverlay)
	const char *m_unitType;
	DBINDEX(DbSprite) m_sprite;
ENDCLASS


//	@HACK: upgrade terrain overlay
DATACLASS(DbUpgradeOverlay)
	const char *m_unitType;			// unit type to upgrade
	DBINDEX(DbSprite) m_baseSprite;	// data to upgrade (see ABCD_TerrainOverlay)
ENDCLASS

//	Sound upgrade
DATACLASS(DbUpgradeSound)
	const char *m_unitType;			// unit to upgrade
	DC(DbUnitTypeSounds) *m_sounds;	// new sounds (see DbUnitDefs.h)
ENDCLASS

// Display name change upgrade
DATACLASS(DbUpgradeDisplayName)
	const char *m_unitType;			// unit to upgrade
	DBINDEX(DbText) m_name;				// new display name
	DBINDEX(DbText) m_namePlural;	// new display name (plural)
ENDCLASS

// Verbose tooltip change upgrade
DATACLASS(DbUpgradeVerboseTooltip)
	const char *m_unitType;			// unit to upgrade
	DBINDEX(DbText) m_textIndex;	// new verbose tooltip text index
ENDCLASS

// Movement type change upgrade
DATACLASS(DbUpgradeMoveType)
	const char *m_unitType;			// unit to upgrade
	enum eUnitMoveType m_moveType;	// new movement type
ENDCLASS

DATACLASS(DbUpgradeUnitAttributes)
	const char *m_unitType;									// unit to upgrade
	LSizedArray<enum eUnitTypeAttr> m_attributesToAdd;		// attributes to add
	LSizedArray<enum eUnitTypeAttr> m_attributesToRemove;	// attributes to remove
ENDCLASS


//	Enumerations for method of modifying a factor
ENUM eDbUpgradeUnitTypeFactorSetMethod {
	kDbUpgradeUnitTypeFactorSetMethod_None,	// no upgrade (default)
	kDbUpgradeUnitTypeFactorSetMethod_Set,	// set new value (and clear temporary multiplier)
	kDbUpgradeUnitTypeFactorSetMethod_Add,	// add to value (can't be used with any multipliers)
	kDbUpgradeUnitTypeFactorSetMethod_SetTempMul,	// set the temporary multiplier
	kDbUpgradeUnitTypeFactorSetMethod_AddTempMul,	// add to the temporary multiplier
	kDbUpgradeUnitTypeFactorSetMethod_AddPermMul,	// add to the permanent multiplier
};

inline const char *GetUpgradeUnitTypeFactorMethodName(enum eDbUpgradeUnitTypeFactorSetMethod in_method)
{
	static const char *s_upgradeUnitTypeFactorNames[] = {
		"[None]", "SET", "ADD", "ADDTEMPMUL", "SETTEMPMUL", "ADDPERMMUL"
	};
	ASSERT((in_method >= 0) && (in_method <= kDbUpgradeUnitTypeFactorSetMethod_AddPermMul));
	return s_upgradeUnitTypeFactorNames[int(in_method)];
};

//	Modify a numeric "unit factor" (hp, attack, speed, etc.)
//  NOTE: MULTIPLIER VALUES ARE EXPRESSED AS A PERCENTAGE.  FOR INSTANCE, USE +20
//	TO INCREASE BY 20%, OR -10 TO DECREASE BY 10%.  "SET" AND "ADD" VALUES ARE
//	EXPRESSED AS ABSOLUTE QUANTITIES.
DATACLASS(DbUpgradeUnitTypeFactor)
	const char *m_unitType;				// unit to upgrade (leave NULL if using UTA)
	const char *m_unitTypeAttribute;	// named unit-type-attribute family to upgrade (leave NULL if using unit type)
	DBINDEX(DbText) m_tooltipAffected;	// optional tooltip override for affected units (for the All Buildings type upgrades...)
	bool m_bAlwaysUseTextForAffectedUnits;	// if true, text is used for affected units even in places in the UI which would normally call for icon(s)
	DBINDEX(DbUpgradeFactors) m_factor;	// factor to upgrade (index into DbUpgradeFactors DB)
	enum eDbUpgradeUnitTypeFactorSetMethod m_method; // method for modifying the factor
	float m_value;					// value to use (% if mul, abs value if add)
	bool m_upgradeChildren; // Upgrade UnitTypes that are derrived from the specified UnitType (ignored if using UTA)
	// @EE2X - Josh - 03/29/05 - added m_FlagResearchType
	enum eFlagReqTechType m_FlagResearchType;	// which type of research is this?  (for flag system)
ENDCLASS

// Give a single region power to a player.
DATACLASS(DbUpgradeRegionPower)
	// Which region power does this upgrade enable?
	const char* m_regionPowerName; 
	// Which region is required for the player to receive this power.
	// @TODO fix this to use eCivilizationRegion
	enum ePlayerCivilization m_requiredRegion;  
	// How long to recharge this region power in seconds
	float m_rechargeTime;
	// The duration of this region power.
	float m_duration;
	// The icon to use for this power.
	DBINDEX(DbSprite) m_icon;
	// The tooltip to show for this button.
	DBINDEX(DbText) m_verboseTooltipIndex;
ENDCLASS

// whole sale upgrade of abilities
DATACLASS(DbUpgradeAbilities)
	const char *m_unitType;						// unit to upgrade
	LSizedArray<VARDC> m_upgradedAbilities;		// array of variable abilities
ENDCLASS

// just upgrade attack missile name
DATACLASS(DbUpgradeMissileName)
	const char *m_unitType;
	const char *m_missileName;
ENDCLASS

// Upgrade resources.  This upgrades resource visuals, and also handles some
// cleanup that needs to be done for players.
DATACLASS(DbUpgradeResources)
	DBINDEX(DbUpgrade) m_ResourceUnitTypeUpgrades;		// Upgrade to perform on resource UnitTypes.
ENDCLASS

// upgrade UnitAbilityAreaEffect (add/remove effects)
DATACLASS(DbUpgradeEffects)
	// what unit type is this upgrade for?
	const char *m_unitType;

	// lists of indices into area effect table
	// indicating which powers are to be added, and which are to be removed
	LSizedArray<DBINDEX(DbAreaEffects)> m_effectsToAdd;
	LSizedArray<DBINDEX(DbAreaEffects)> m_effectsToRemove;
ENDCLASS

// upgrade UnitAbilitySpecialPower (add/remove powers)
DATACLASS_INHERIT(DbUpgradePowers, DbUpgradeEffects)
	// nothing more needed, see parent
ENDCLASS


//Civilization and Region Bonuses
ENUM eCivRegBonusAction {
	kCivRegBonusAction_Capture,
	kCivRegBonusAction_BuiltWonder,
	kCivRegBonusAction_Convert,
	kCivRegBonusAction_EpochAdvance,
	kCivRegBonusAction_MarketSales,  //not really done on a action, but we'll piggy-back the upgrade here
	kCivRegBonusAction_CostModification, //also piggy-backed
	kCivRegBonusAction_ExtraBuildings,
};


DATACLASS(DbUpgradeCivRegBonus)
	enum eCivRegBonusAction m_onAction;		//The message to watch for
	LSizedArray<const char *>m_unitTypes;	//What unit types to act on
	enum eResourceType m_resourceType;		//What resource will be changed
	float m_amount;							//amount
	float m_amount2;						//just some more info 	
	const char* m_stringData;				// Some string data
ENDCLASS

// Undoes certain previous types of upgrades
DATACLASS(DbUpgradeUndo)
	const char *m_techNode;			// tech node to undo
	const char *m_upgrade;			// name of upgrade to undo (if missing, undo all)
ENDCLASS

// Upgrade unit size
DATACLASS(DbUpgradeSize)
	const char *m_unitType;	// the unit type to upgrade
	float m_sizeX;			// new size
	float m_sizeY;
ENDCLASS

DATACLASS(DbUpgradeReplacePower)
	const char *m_unitType;	// the unit type to upgrade
	DBINDEX(DbAreaEffects) m_effectToAdd;
	DBINDEX(DbAreaEffects) m_effectToReplace;
ENDCLASS	

#endif // DBUPGRADEDEFS_H
