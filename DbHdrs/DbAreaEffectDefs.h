//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbAreaEffectDefs.h 117   9/29/05 4:26p Dsproul $
//
// DESCRIPTION:	DbAreaEffectDefs.h holds the structure of the special
//				'area effect' abilities.
//
// AUTHOR:      Ben Morse
//
//===========================================================================

#ifndef DBAREAEFFECTDEFS_H
#define DBAREAEFFECTDEFS_H
#pragma once

#include "hdrmacros.h"
#include "LDataObj.h"
#include "LSizedArray.h"
#include "LRgba.h"
#include "DbResourceDefs.h"
#include "DbCrownDefs.h"

// VisualGlow types
ENUM eGlowType {
	kGlowType_Good,
	kGlowType_Bad,
	kGlowType_Mixed,
	kGlowType_Neutral,
	kGlowType_King,
	kGlowType_HeroArmy,
	kGlowType_HeroArmyLeader,
	kGlowType_SupremeLeader,
	kNumGlowTypes,
};

// SuperEffects may specify a selection type 
// (defaults to none) if that effect requires a unit or location
// to be selected by the player
ENUM eSelectionType {
	kSelectionType_None,
	kSelectionType_Unit,
	kSelectionType_Location,
	kSelectionType_Player,	// Player needs to select another player.
	kSelectionType_LeaderOrHero,	// @EE2X @MRC Player must select one of his leaders or heroes.
	kNumSelectionTypes,
};

//If you add a new kAreaEffectRange_, you need to update
//IsUnitAttachedEffect, IsPlayerAttachedEffect, and IsUnitAffectingEffect
//(all in this file).
ENUM eAreaEffectRange {
	//affects just the unit to which it is attached.
	kAreaEffectRange_Unit,

	//affects all units within a radius of the unit to which this effect is attached.
	kAreaEffectRange_RadiusFromUnit,
	
	//affects all units within a radius of the unit to which this effect is attached
	//(excluding the unit to which this effect is attached).
	kAreaEffectRange_RadiusFromUnitExcludingSelf,

	// affects all units within a radius of the targeted location
	kAreaEffectRange_RadiusFromLocation,
	
	// player attached territory ranges
	kAreaEffectRange_SelfClaimedTerritory,					// territories owned by player, not disputed
	kAreaEffectRange_SelfClaimedTerritoryIncludeDisputed,	// territories owned by player, with disputed
	kAreaEffectRange_OtherClaimedTerritory,					// claimed territories owned by other players, not disputed
	kAreaEffectRange_OtherClaimedTerritoryIncludeDisputed,	// claimed territories owned by other players, with disputed
	kAreaEffectRange_UnclaimedTerritory,		// unclaimed territories

	// sheesh:  territories owned by player with at least one temple in them
	kAreaEffectRange_SelfClaimedTerritoryWithTemple,

	// unit attached territory ranges
	kAreaEffectRange_SelfClaimedTerritory_Unit,	// territories owned by attached unit's player 
	kAreaEffectRange_OtherClaimedTerritory_Unit,
	kAreaEffectRange_SelfClaimedTerritoryUnitIsIn,	//affects all units within the territory (owned by the player the effect is attached to) that the unit to which this effect is attached is currently in.

	kAreaEffectRange_CityUnitIsIn,		//affects all units within the footprint of the city that the unit to which this effect is attached is currently in.
	kAreaEffectRange_SelfCityUnitIsIn,	//affects all units within the footprint of the city (owned by the player the effect is attached to) that the unit to which this effect is attached is currently in.
	kAreaEffectRange_AllSelfCities,		//affects all units within all cities owned by the player to which this effect is attached.
	kAreaEffectRange_AllSelfCities_Unit,//affects all units within all cities owned by the player to which the unit to which this effect is attached.
	kAreaEffectRange_AllEnemyCities,	//affects all units within all cities owned by enemies of the player to which this effect is attached.
	kAreaEffectRange_Global,			//affects all units. (filtered by the UTA mask in the ability, of course)
	kAreaEffectRange_Global_Unit,		// (unit attached version of the above)
	
	kAreaEffectRange_HeroArmyOwnAll,		// affects all units in the army that this hero unit owns (including heroes)
	kAreaEffectRange_HeroArmyOwnSame,		// affects units OF THE SAME HERO CLASS in the army that this hero unit OWNS (no heroes)
	kAreaEffectRange_HeroArmyOwnDifferent,	// affects units OF A DIFFERENT HERO CLASS in the army that this hero unit OWNS (no heroes)
	kAreaEffectRange_HeroArmyOtherSame,		// affects units OF THE SAME HERO CLASS in the army that this hero unit BELONGS TO, BUT DOES NOT OWN (no heroes)

	kAreaEffectRange_UnitsInArmies,			// affects all units in armies belonging to the player to which the effect is attached

	kAreaEffectRange_TechTree,			//affects the tech tree, not units!
	kAreaEffectRange_PopCap,			//affects the population cap, not units!
	kAreaEffectRange_SpaceTime,			//does not directly affect units, but somehow changes gameplay mechanics.  basically 'global' but not unit-specific.

	kNumAreaEffectTargetTypes,
};

//So this isn't strictly necessary for the ddfs, which won't use this enum,
//but for internal reasons there MUST be a one-to-one correspondence between
//members of this enum and the DATACLASSes that inherit from SubEffect.
//Also, it MUST follow the form of
//  kEffectType_FOO <=> DATACLASS_INHERIT(EffectFOO, SubEffect)
//because there's a table of dataclasses built automatically through string
//manipulation.
ENUM eEffectType {
	//up through kEffectType_LastUnitEffect are effects that affect Units.
	//not the techtree or the popcap or whatever.
	kEffectType_ResourceDropoff,
	kEffectType_ResourceTrade,
	kEffectType_ConstructionAdvance,
	kEffectType_SpecialPowerRechargeTime,
	kEffectType_BuildRepairRate,
	kEffectType_ResourceGatherRate,
	kEffectType_NoConversion,
	kEffectType_AreaDamage,
	kEffectType_Damage,
	kEffectType_Attack,
	kEffectType_AttackSpeed,
	kEffectType_AttackReplaceAmmo,
	kEffectType_PreventAttack,
	kEffectType_MaxHitPoints,
	kEffectType_ConstructionCost,
	kEffectType_ConstructionTime,
	kEffectType_TerritoryConstructionTime,
	kEffectType_ProductionCost,
	kEffectType_ProductionTime,
	kEffectType_TowerUpgradeTime,
	kEffectType_Speed,
	kEffectType_WeatherSpeed, // this is to modify unit speed due to weather, DOES NOT CHANGE SPEED OF WEATHER 
	kEffectType_ConversionRange,
	kEffectType_HealRate,
	kEffectType_AddLOS,
	kEffectType_LOS,
	kEffectType_GiveLOS,
	kEffectType_MarketStability,
	kEffectType_ConversionTime,
	kEffectType_CaptureTime,
	kEffectType_Range,
	kEffectType_IncredibleDeath,
	kEffectType_ActivateForageAbility,
	kEffectType_Heal,			// heal affected units over time
	kEffectType_Spawn,			// spawn units over time
	kEffectType_Infect,			// attach specified area effect to affected unit
	kEffectType_Repeat,			// 
	kEffectType_AttachAndDetach,// Attach another effect to other units and then detach it.
	kEffectType_KillPayment,	// when units with this effect kill another unit, they get a % of the victims resource cost
	kEffectType_TradePayment,	// when trade occurs specified amounts of specified resources get credited
	kEffectType_TradeTime,		// @EE2X -- time taken to trade
	kEffectType_ShotSuccessRate,			// make projectiles miss from time to time (when shot at target with this effect)
	kEffectType_ActivateAttackAbility,		// make latent attack abilities active!
	kEffectType_CaptureResourceYield,		// modulate amount of resources yielded when captured (effect operates on capture target)
	kEffectType_ConvertOverTime,
	kEffectType_PreventDeletion,	// For some scenarios, prevent target units from being deleted by player input
	
	// the following are "active" "area effect"
	kEffectType_Shield,			// spawn a force field around the affected units
	kEffectType_Diversion,		// spawn a "phantom" formation near selected location
	kEffectType_PurchaseUnit,
	kEffectType_GatherIntel,
	kEffectType_MassConvert,
	kEffectType_MassConvertOverTime,
	kEffectType_Proselytizing,
	kEffectType_DamageCapturers,
	kEffectType_MassHeal,
	kEffectType_CauseDamageOverTime,
	kEffectType_Visual,
	kEffectType_StateChange,
	kEffectType_ReplaceConversionVisual,
	kEffectType_Extraction,
	kEffectType_RapidDeployment,	// Pretty specific.  It's for the pentagon.  It moves units around the map.
	kEffectType_VisualGlow,
	kEffectType_ColorChange,
	kEffectType_Contaminate,
	kEffectType_Sabotage,
	kEffectType_Bless,
	kEffectType_IsACrown,
	kEffectType_VisualShimmer,
	kEffectType_StartPlayerEffect,	// Start an area effect and attach it to a player.
	kEffectType_Cloning,			// every unit conversion results in instantiation of an exact duplicate
	kEffectType_Cloak,				// units affected by Cloak are effectiely disguised (see UnitInfo::IsUnitDisguised())
	kEffectType_Immobilize,			// units affected by immobilize are kept stationary
	kEffectType_Button,				// Adds a button to a unit.  Kind of like special power, except it doesn't
									// necessarily require special power.
	kEffectType_Explode,			// trigger a visual explosion
	kEffectType_PropagateWhenGarrisoned,	// Propogate one or more area effects while the unit is garrisoned.
	kEffectType_SupremeLeader,		// Indicate that this unit is a supreme leader
	
	//These must be the LAST TWO of the sequence that affect units!
	//If you want to add another unit effect type, add it BEFORE
	//these two, or make sure you change kEffectType_LastUnitEffect
	//to point to the last effect!
	kEffectType_Capacity,
	kEffectType_LastUnitEffect = kEffectType_Capacity,
	
	kEffectType_BlackMarket,		// Steal a little money on each trade transaction
	kEffectType_Population,
	kEffectType_PopulationAdditive,
	kEffectType_TechCost,
	kEffectType_TechDiscoveryTime,
	kEffectType_TechButtonFlash,
	kEffectType_RegionPowerRechargeRate,	// @EE2X Daniel
	kEffectType_TerritoryResourceDropoff,	// @EE2X Daniel @HACK
	kEffectType_MaxMoraleFervor,	// @EE2X @MRC Player's get max morale and fervor bonuses in territories
	kEffectType_TechnologyTrance,	// @EE2X @MRC Makes player steal tech when sabotaging
	kEffectType_Duration, // modify a specific super-effect's duration
	kNumEffectTypes,
};

ENUM ePlayerEffectNotify {
	kPlayerEffectNotify_None,
	kPlayerEffectNotify_Tech,	//Notify the player this effect effects a tech related thing, and something special needs to happen
};

//returns true iff in_eRange is for a SubEffect that is attached to a unit.
inline bool IsUnitAttachedEffect(eAreaEffectRange in_eRange)
{
	ASSERT( in_eRange >= 0 && in_eRange < kNumAreaEffectTargetTypes );
	return
		in_eRange == kAreaEffectRange_Unit ||
		in_eRange == kAreaEffectRange_RadiusFromUnit ||
		in_eRange == kAreaEffectRange_RadiusFromUnitExcludingSelf ||
		in_eRange == kAreaEffectRange_CityUnitIsIn ||
		in_eRange == kAreaEffectRange_SelfCityUnitIsIn ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritory_Unit ||
		in_eRange == kAreaEffectRange_OtherClaimedTerritory_Unit ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritoryUnitIsIn ||
		in_eRange == kAreaEffectRange_Global_Unit ||
		in_eRange == kAreaEffectRange_AllSelfCities_Unit ||
		in_eRange == kAreaEffectRange_HeroArmyOwnAll ||
		in_eRange == kAreaEffectRange_HeroArmyOwnSame ||
		in_eRange == kAreaEffectRange_HeroArmyOwnDifferent ||
		in_eRange == kAreaEffectRange_HeroArmyOtherSame;
}

//returns true iff in_eRange is for a SubEffect that is attached to a player.
inline bool IsPlayerAttachedEffect(eAreaEffectRange in_eRange)
{
	ASSERT( in_eRange >= 0 && in_eRange < kNumAreaEffectTargetTypes );
	return
		in_eRange == kAreaEffectRange_SelfClaimedTerritory ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritoryIncludeDisputed ||
		in_eRange == kAreaEffectRange_OtherClaimedTerritory ||
		in_eRange == kAreaEffectRange_OtherClaimedTerritoryIncludeDisputed ||
		in_eRange == kAreaEffectRange_UnclaimedTerritory ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritoryWithTemple ||
		in_eRange == kAreaEffectRange_AllSelfCities ||
		in_eRange == kAreaEffectRange_AllEnemyCities || 
		in_eRange == kAreaEffectRange_Global ||
		in_eRange == kAreaEffectRange_TechTree ||
		in_eRange == kAreaEffectRange_PopCap ||
		in_eRange == kAreaEffectRange_RadiusFromLocation ||
		in_eRange == kAreaEffectRange_SpaceTime ||
		in_eRange == kAreaEffectRange_UnitsInArmies;
}

//Returns true iff in_eRange is for a SubEffect that AFFECTS units.
//It might be ATTACHED to a player, but if it AFFECTS units, this
//is true.
inline bool IsUnitAffectingEffect(eAreaEffectRange in_eRange)
{
	ASSERT( in_eRange >= 0 && in_eRange < kNumAreaEffectTargetTypes );
	return
		in_eRange == kAreaEffectRange_Unit ||
		in_eRange == kAreaEffectRange_RadiusFromUnit ||
		in_eRange == kAreaEffectRange_RadiusFromUnitExcludingSelf ||
		in_eRange == kAreaEffectRange_RadiusFromLocation ||
		in_eRange == kAreaEffectRange_CityUnitIsIn ||
		in_eRange == kAreaEffectRange_SelfCityUnitIsIn ||
		in_eRange == kAreaEffectRange_AllSelfCities ||
		in_eRange == kAreaEffectRange_AllSelfCities_Unit ||
		in_eRange == kAreaEffectRange_AllEnemyCities ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritory ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritoryIncludeDisputed ||
		in_eRange == kAreaEffectRange_OtherClaimedTerritory ||
		in_eRange == kAreaEffectRange_OtherClaimedTerritoryIncludeDisputed ||
		in_eRange == kAreaEffectRange_UnclaimedTerritory ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritoryWithTemple ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritory_Unit ||
		in_eRange == kAreaEffectRange_OtherClaimedTerritory_Unit ||
		in_eRange == kAreaEffectRange_SelfClaimedTerritoryUnitIsIn ||
		in_eRange == kAreaEffectRange_Global ||
		in_eRange == kAreaEffectRange_Global_Unit ||
		in_eRange == kAreaEffectRange_HeroArmyOwnAll ||
		in_eRange == kAreaEffectRange_HeroArmyOwnSame ||
		in_eRange == kAreaEffectRange_HeroArmyOwnDifferent ||
		in_eRange == kAreaEffectRange_HeroArmyOtherSame ||
		in_eRange == kAreaEffectRange_UnitsInArmies;
}

inline bool IsGlobalEffectRange(eAreaEffectRange in_eRange)
{
	return (in_eRange == kAreaEffectRange_Global ||
			in_eRange == kAreaEffectRange_Global_Unit);
}

//This is the parent dataclass for subeffects.  It determines their scope.
DATACLASS(SubEffect)
	enum eAreaEffectRange range;		//the scope of what is affected by this effect

	//if range is a type that affects units, these are the units that are
	//affected within that area.
	// @NOTE player mode is also used for selected other effects
	// (in PlayerAppliedEffectIterator::GetAndStep()), but by no means is it used
	// consistently across the board...
	DBINDEX(DbUnitTypeAttribute) mask;
	enum ePlayerMode player;

	// if greater than zero,
	// then this sub-effect is updated at specified period,
	// else sub-effect is updated with period = 1 second
	float period;

	//if range is radius from leader, this is the radius
	float radius;

	bool instant;	// is this an instant effect
	
	bool updateOnce;	// update unit list only once at the beginning of the effect

	// if this area effect is upgradable,
	// how to get the upgraded value from the Unit it is attached to
	// (or from city center unit in containing city, see below)
	enum eDbUpgradeUnitTypeFactor upgradeFactor;	// default to 0 (kDbUpgradeUnitTypeFactor_None)

	// if true, then will get upgradeable value from affected unit,
	// rather than letting the effect range dictate that choice.
	// NOTE:  this is useful only in very esoteric cases and should be avoided,
	//        much like your daddy's dentures...
	bool forceUpgradeFromAffectedUnit;
ENDCLASS

//An effect contains a number of these subeffects.
DATACLASS(DbAreaEffectInfo)
	DBINDEX(DbText) m_name;				//the (human english, not DB) name of the effect, for UI display.
	DBINDEX(DbText) m_desc;				//the effect description, for UI display.

	bool m_disableDuringCeasefire;		// should we disable this power during ceasefire?
	const char *button;					//name of widget used for action button, if any

	float m_duration;					// The duration of the effect in seconds. <= 0 means it never expires.

	// These two values are used to specify a range of epochs in which this power may be used.
	// This is being put in place for the crown effects, but can really be used for anything.
	// The area effect manager is dumb about these values for now; it won't do anything with them.
	// You probably need to implement something if you want to use them (apart from crown effects).
	int	m_EpochRangeLow;	// The low end epoch restriction
	int m_EpochRangeHigh;	// The high end epoch restriction

	enum eSelectionType m_selectionType;	// does this effect require selecting a unit/location?
	int m_MouseRadius;						// when selecting a target with the mouse, this is the radius of the circle.

	DBINDEX(DbCursor) m_mouseCursor;		// when selecting with the mouse, this is the cursor to use
	DBINDEX(DbCursor) m_mouseCursorInvalid;	// and another cursor if target not valid

	// if requireSelection,
	// then maskSelection and playerSelection should also be specified
	// they are used to determine who valid targets of this super effect are
	DBINDEX(DbUnitTypeAttribute) m_maskSelection;
	enum ePlayerMode m_playerSelection;
	
	bool m_maskSelectionForConstructionSite;// if true, then selection mask looks to construction ability's UTA

	// @HACK @HACK
	bool m_bSkipKingOfTheHillUnit;	// if true, this effect _cannot_ act upon the KOTH unit (a distinct unit type)

	const char* m_HighlightAreaEffect;		// An index to another area effect to highlight units 
											// while doing mouse movements.
	USER int m_HighlightAreaEffectIndex;	// Index for the above string.
	
	enum ePlayerEffectNotify m_playerEffectNotify;		//Some effects need to have a notification sent to a have a special
												//notification sent.  This is a flag for handling that.

	LSizedArray<VARDC> effects;			//the various subeffects that this effect contains.
ENDCLASS

///////////////////////////////////////////////////////////////////////////////
//////////////////////////Effects that apply to Units//////////////////////////
///////////////////////////////////////////////////////////////////////////////

//This subeffect just kills units.  It's mostly for a test, but maybe we'll
//want it someday.
DATACLASS_INHERIT(EffectIncredibleDeath, SubEffect)
ENDCLASS

// heal the affected units over time
DATACLASS_INHERIT(EffectHeal, SubEffect)
	// do we want to look for EffectHealRate effects on the unit we are attached to?
	bool applyEffectHealRateModifier;
	float healRate;		// how many hit points to heal per second
ENDCLASS

// spawn units at the affected at a specified rate 
DATACLASS_INHERIT(EffectSpawn, SubEffect)
	float delay;	// how many seconds until next spawn time.
	int minCount;	// how many units (minimum) to spawn when the time comes
	int maxCount;	// how many units (maximum) to spawn when the time comes
	LSizedArray<const char*> unitTypes;	// Randomly pick a unit type from the list to spawn.

	// if true, a message relating to immigration will be printed when units are spawned
	bool showImmigrationMsg;

	// @EE2X
	// @JCD 03/11/2005
	// if true, use owning player's civilization when spawning units
	bool usePlayersCivilization;
	// if true, units are not spawned over the pop cap amount, otherwise disregards the natural laws of the pop cap.
	bool restrictToPopCap;
	
ENDCLASS

// attach specified area effect to affected units
DATACLASS_INHERIT(EffectInfect, SubEffect)
	// what effect to infect with (attach)
	const char* m_effectName;
	// if inserIntoThisSuperEffect
	// then the sub-effects of the super effect indicated by m_effectName
	// will be filed under the super effect that owns this EffectInfect.
	// otherwise m_effectName will be instantiated as a standalone super effect.
	// 
	// this flag is particularly useful if the infection needs to go away
	// (timeout) when the super effect that spawned them does.
	bool m_insertIntoThisSuperEffect; 
ENDCLASS

DATACLASS_INHERIT(EffectRepeat, SubEffect)
	// repeats specified effect onto all affected units
	const char* m_effectName;
ENDCLASS

// When a unit is initially affected by this effect, there is a percent chance
// that another effect will be attached to the unit.  When the unit becomes unaffected
// by this effect, the other effect will be detached from the unit.
DATACLASS_INHERIT(EffectAttachAndDetach, SubEffect)
	float m_fChanceToFire;		// Percent chance to activate on new units
	const char* m_effectName;	// Effect to attach to new units.
ENDCLASS

// a kill payment is composed of a number of KillPaymentComponents
// each component specifies:
DATACLASS(KillPaymentComponent)
	enum eResourceType m_resource;	// which resource type
	float m_scale;					// what to scale resource type by
	float m_bonus;					// what amount to add onto the scaled payment
ENDCLASS

DATACLASS_INHERIT(EffectKillPayment, SubEffect)
	LSizedArray<DC(KillPaymentComponent)*> m_payment;
ENDCLASS

// If a unit has this effect, AND he has the correct GatherFarm ability, then
// he can use that ability.
DATACLASS_INHERIT(EffectActivateForageAbility, SubEffect)
ENDCLASS

// when you capture a building it may yield resources to you,
// this effect operates on the capture target and modulates the resource amount yielded.
DATACLASS_INHERIT(EffectCaptureResourceYield, SubEffect)
	float m_scale;	// what to scale resource yield by
ENDCLASS

//This subeffect affects units that can accept resource dropoff, and when
//resources are dropped off, it scales them by a fixed amount.
DATACLASS_INHERIT(EffectResourceDropoff, SubEffect)
	LSizedArray<enum eResourceType> affected;	//which resource types are affected
	float scale;		//what to scale dropped-off resources by
ENDCLASS

// @EE2X Daniel
// horrible @HACK modifies the resource dropoff granted by houses in player-owned territories
DATACLASS_INHERIT(EffectTerritoryResourceDropoff, SubEffect)
	float scale;		//what to scale dropped-off resources by
ENDCLASS

//This subeffect affects units that gain resources by trade.  When
//resources come in via a trade route, it scales them by a fixed amount.
DATACLASS_INHERIT(EffectResourceTrade, SubEffect)
	LSizedArray<enum eResourceType> affected;	//which resource types are affected
	float scale;		//what to scale resources gained from trade by
ENDCLASS

// This subeffect affects units that are gaining resources through traide
// When resources com in via a trade route, the resource types (and amounts)
// specified here will be creditied also.
DATACLASS_INHERIT(EffectTradePayment, SubEffect)
	LSizedArray<enum eResourceType> m_types;	//which resource types are affected
	LSizedArray<int> m_amounts;	//which resource types are affected
ENDCLASS

// time taken for a unit to trade (time spent garrisonned) modified by 'scale'
// (bigger = takes longer)
DATACLASS_INHERIT(EffectTradeTime, SubEffect)
	float m_scale;
ENDCLASS


// make projectiles miss from time to time (when shot at target with this effect)
DATACLASS_INHERIT(EffectShotSuccessRate, SubEffect)
	// what kinds of projectile movement types are affected?
	LSizedArray<enum eProjectileMoveType> m_affectedProjectileMoveTypes;

	// what percentage of shots succeed?
	float m_successRate;
ENDCLASS

// temporarily activate a latent attack ability
DATACLASS_INHERIT(EffectActivateAttackAbility, SubEffect)
ENDCLASS


// spawn a force field around the affected units
DATACLASS_INHERIT(EffectShield, SubEffect)
	// what visual should be used for the shield?
	const char* m_visualName;

	// the missile system may only protect against projectile attacks
	bool m_onlyBlocksProjectiles;
			
	// zero HP indicates the shield can withstand unlimited damage
	float m_hitPoints;

	// zero duration indicates the shield has no time limit
	float m_duration;
ENDCLASS


// a unit type / unit count pair
// used for defining the components of a diversion
DATACLASS(TypeCount)
	int m_startEpoch;	// first epoch to use this set in the formation
	int m_endEpoch;		// last epoch to use this set in the formation
	
	const char* m_name; // internal type name
	int m_count;		// how many of this type?
ENDCLASS

DATACLASS_INHERIT(EffectDiversion, SubEffect)
	// name of formation to use,
	// must be compatible with units defined in m_units
	const char* m_formation;

	// zero duration indicates the diversion has no time limit
	float m_duration;
	
	// the units that comprise this formation (diversion)
	LSizedArray<DC(TypeCount)*> m_units;
ENDCLASS

//This subeffect targets a unit under construction, and immediately contributes
//a fraction (0.0-1.0) of the total construction time.  If the unit is already
//half constructed, and the fraction is 0.5, it will bring it to full
//completion (i.e. the fraction refers to total construction time, not
//remaining construction time).
DATACLASS_INHERIT(EffectConstructionAdvance, SubEffect)
	//how much of the construction should be completed
	//(0.0=nothing, 1.0=full completion)
	float fractionToAdvance;
ENDCLASS

//Units affected by EffectSpecialPowerRechargeTime take 'scale' times their
//normal time to recharge any special powers they might have.
DATACLASS_INHERIT(EffectSpecialPowerRechargeTime, SubEffect)
	float scale;		//what to scale the recharge time by (smaller = faster)
ENDCLASS

//Units affected by EffectBuildRepairRate take 'scale' times their
//normal rate to build or repair whatever they're working on.
DATACLASS_INHERIT(EffectBuildRepairRate, SubEffect)
	float scale;		//what to scale construction time by (bigger = faster)
ENDCLASS

//Units affected by EffectResourceGatherRate take 'scale' times their
//normal rate to gather any resources.
DATACLASS_INHERIT(EffectResourceGatherRate, SubEffect)
	LSizedArray<enum eResourceType> affectedResourceTypes;	//which resource types are affected
	DBINDEX(DbUnitTypeAttribute) affectedResourceSources;	//what resource units does this refer to (farms, patches, ?)
	float scale;		//what to scale resource gather rate by (bigger = faster)
ENDCLASS

//Units subject to morale bonus for being in a city have that morale
//bonus scaled by 'scale'.
DATACLASS_INHERIT(EffectMoraleBonus, SubEffect)
	float scale;		//what to scale the morale bonus in the city by
ENDCLASS

//Units subject to fervor bonus for being in a city have that fervor
//bonus scaled by 'scale'.
DATACLASS_INHERIT(EffectFervorBonus, SubEffect)
	float scale;		//what to scale the fervor bonus in the city by
ENDCLASS

//Units affected by EffectNoConversion can't be converted.  Period.  This
//takes precedence over conversion-for-twice-of-resource-cost and other
//auto-converting things.
DATACLASS_INHERIT(EffectNoConversion, SubEffect)
ENDCLASS

//Units affected by EffectAreaDamage have the damage that they take
//from area attacks (nukes?) scaled by 'scale'.
DATACLASS_INHERIT(EffectAreaDamage, SubEffect)
	float scale;		//what to scale area damage by.
	enum eWeaponType	type;	// what type of damage are we scaling.
ENDCLASS

//Units affected by EffectDamage have the damage that they take from
//any/all attacks scaled by 'scale'.
DATACLASS_INHERIT(EffectDamage, SubEffect)
	float scale;		//what to scale damage by.
	enum eWeaponType	type;	// what type of damage are we scaling.
ENDCLASS

//Units affected by EffectAttack have their attack ratings scaled by
//'scale'.
DATACLASS_INHERIT(EffectAttack, SubEffect)
	float scale;	// what to scale attack by.
	bool  bless;	// is this effect a blessing (see Priest's "Bless" power)?
ENDCLASS

//Units affected by EffectAttackSpeed have their attack speed scaled by
//'scale'.
DATACLASS_INHERIT(EffectAttackSpeed, SubEffect)
	float scale;		//what to scale attack speed by.
ENDCLASS

// Units affected by EffectAttackReplaceAmmo have the ammo for any missile
// attacks replaced by the specified ammo.
DATACLASS_INHERIT(EffectAttackReplaceAmmo, SubEffect)
	const char* m_NewAmmo;	// The name of the new ammo to use.
ENDCLASS

// Prevent a unit from being able to attack.  This stops the unit from accepting
// any new attack goals, and should suspend any existing attack goals.
DATACLASS_INHERIT(EffectPreventAttack, SubEffect)
ENDCLASS

//Units affected by EffectMaxHitPoints have their max hit points scaled by
//'scale'.
DATACLASS_INHERIT(EffectMaxHitPoints, SubEffect)
	float scale;		//what to scale max HP by.
ENDCLASS

// Units affected by EffectConstructionCost have the resource cost
// associated with thier construction / repair modulated by 'scale'
DATACLASS_INHERIT(EffectConstructionCost, SubEffect)
	DBINDEX(DbUnitTypeAttribute) affected;	//what unit types will be constructed cheaper/expensiver
	float m_scale;
ENDCLASS

//Unit types affected by EffectConstructionTime have the time it takes for
//them to be constructed scaled by 'scale'.  This is for building buildings
//or wonders faster/slower.
DATACLASS_INHERIT(EffectConstructionTime, SubEffect)
	float scale;		//what to scale time by. (smaller = faster)
ENDCLASS

// same deal as EffectConstructionTime - this effect always excludes CityCenters
DATACLASS_INHERIT(EffectTerritoryConstructionTime, EffectConstructionTime)
	// no additional data necessary
ENDCLASS

//Unit types affected by EffectProductionCost have the cost for
//them to produce other units matching 'affected' scaled by 'scale'.
DATACLASS_INHERIT(EffectProductionCost, SubEffect)
	DBINDEX(DbUnitTypeAttribute) affected;	//what unit types will be produced cheaper/expensiver
	float scale;		//what to scale cost by. (smaller = cheaper)
ENDCLASS

//Unit types affected by EffectProductionTime have the time it takes for
//them to produce other units matching 'affected' scaled by 'scale'.
DATACLASS_INHERIT(EffectProductionTime, SubEffect)
	DBINDEX(DbUnitTypeAttribute) affected;	//what unit types will be produced faster/slower
	float scale;		//what to scale time by. (smaller = faster)
ENDCLASS

// @EE2X Daniel
// Unit types affected by EffectTowerUpgradeTime (presumably wall connectors) have the time it takes for
// them to upgrade to wall towers scaled by 'scale'
DATACLASS_INHERIT(EffectTowerUpgradeTime, SubEffect)
	float scale;		//what to scale time by. (smaller = faster)
ENDCLASS

//Unit types affected by EffectSpeed have their speed scaled by 'scale'.
DATACLASS_INHERIT(EffectSpeed, SubEffect)
	float scale;		//what to scale speed by. (smaller = slower)
ENDCLASS

//Unit types affected by EffectWeatherSpeed have their speed scaled by 'scale'.
// @NOTE:  meant to be used by weather sim only, please
DATACLASS_INHERIT(EffectWeatherSpeed, SubEffect)
	float scale;		//what to scale speed by. (smaller = slower)
ENDCLASS

//Unit types affected by EffectConversionRange have their conversion
//range scaled by 'scale'.
DATACLASS_INHERIT(EffectConversionRange, SubEffect)
	float scale;		//what to scale range by. (smaller = closer)
ENDCLASS

//Unit types affected by EffectHealRate have their heal rate scaled by
//'scale'.  NOTE!  This affects units who HAVE the Heal ability, NOT
//units who are _being_ healed.
DATACLASS_INHERIT(EffectHealRate, SubEffect)
	float scale;	// what to rate time by. (larger = faster)
ENDCLASS

//Unit types affected by EffectAddLOS have additionalLOS added to their LOS.
DATACLASS_INHERIT(EffectAddLOS, SubEffect)
	float additionalLOS;		//what to add to LOS (smaller = shorter)
ENDCLASS

// Units affected by EffectGiveLOS will be visible to the
// player that cast the effect.
DATACLASS_INHERIT(EffectGiveLOS, SubEffect)
	bool m_OverrideUTAMask;		// If true, it will programmatically generate a UTA on the fly.
ENDCLASS

//Unit types affected by EffectLOS have their LOS scaled by scale.
DATACLASS_INHERIT(EffectLOS, SubEffect)
	float scale;		//what to scale LOS by. (smaller = shorter)
ENDCLASS

// players affected by EffectMarketStability have
// their market "inflation" and "deflation" rates modified by the specified factors
DATACLASS_INHERIT(EffectMarketStability, SubEffect)
	float m_inflationFactor;	// what to scale inflation rate by
	float m_deflationFactor;	// what to scale deflation rate by
ENDCLASS

//Units affected by EffectConversionTime have the time it takes for them
//to convert units scaled by scale.
DATACLASS_INHERIT(EffectConversionTime, SubEffect)
float scale;		//what to scale conversion time by. (smaller = faster)
ENDCLASS

//Units affected by EffectCaptureTime have the time it takes for them
//to capture buildings scaled by scale.
DATACLASS_INHERIT(EffectCaptureTime, SubEffect)
float scale;		//what to scale conversion time by. (smaller = faster)
ENDCLASS

//Units affected by EffectRange have the range of their ranged attack scaled
//by 'scale'.
DATACLASS_INHERIT(EffectRange, SubEffect)
	float scale;		//what to scale range by (larger = further)
ENDCLASS

//Units affected by EffectCapacity can carry 'scale' times as many units
//as they could before.
DATACLASS_INHERIT(EffectCapacity, SubEffect)
	float scale;		//what to scale capacity (larger = can carry more)
ENDCLASS

// damage any unit trying to capture this unit
DATACLASS_INHERIT(EffectDamageCapturers, SubEffect)
	float scale;		// damage equals 'scale' times the max health 
ENDCLASS

// convert a whole bunch of units in the targeted area
DATACLASS_INHERIT(EffectMassHeal, SubEffect)
	float hitpointsHealed;		//how many hit points to heal for each unit in range, or what percentage to add
	bool m_usePercentage;			// If this is true, then hitpointsHealed is a percentage
									// of the unit's max HP to add.  
	const char* m_effectName;	// Name of the visual effect to play on units that get healed.
ENDCLASS

DATACLASS_INHERIT(EffectCauseDamageOverTime, SubEffect)
	float m_DamageAmount;			// How much damage to do per second.
	bool  m_NoDamageSource;			// There should be no source unit when applying damage.
	enum eWeaponType m_weaponType;	// Specify a weapon type to be used for this damage.  (like "Nuke")
ENDCLASS

// Create a "extraction" point so that a unit can walk over there and get back to his own city/capital
DATACLASS_INHERIT(EffectExtraction, SubEffect)
	float m_Distance;		// distance of extraction point from the 
	const char *m_effectName;	// name of visual effect to play at the extraction point
	const char* m_timerEffectName; // The name of the timer to be used with the effect.
	float m_ExtractionRadius;			// How close to you need to be to the extraction point?
ENDCLASS

// For rapid deployment
DATACLASS_INHERIT(EffectRapidDeployment, SubEffect)
	const char* m_overallEffectName;	// What visual to play for deployment.
ENDCLASS

///////////////////////////////////////////////////////////////////////////////
///////////////////////Effects that cause visual effects///////////////////////
///////////////////////////////////////////////////////////////////////////////

// Play a visual effect on the specified units.
DATACLASS_INHERIT(EffectVisual, SubEffect)
	const char* m_visualEffect;
	// @EE2X @MRC 
	// Force the visual to attach even when the target parent has been culled.
	bool m_AttachWhenCulled;
	// @EE2X @MRC
	// Only attach the visual for the owning player
	bool m_OnlyForOwner;
ENDCLASS

DATACLASS_INHERIT(EffectVisualShimmer, EffectVisual)
	// @NOTE:  times here are relative to time shimmer was instantiated

	// what point in time does the city become totally invisible
	float m_in;
	// what point in time does the city flicker back
	float m_out;
ENDCLASS


// This is using Shanti's new super-cool AddStateLayer, which lets us layer
// states and animations on a single object.
DATACLASS_INHERIT(EffectStateChange, SubEffect)
	DBINDEX(DbVisualState) m_stateName;	// The state to add.  Can be empty, no state will be added.
								// This state will be removed when the area effect is canceled.
	bool m_loopAnim;			// Should we loop the animation?
	DBINDEX(DbVisualState) m_outStateName; // A state to add when the area effect is removed.  Kind of a
								// delayed effect kind of thing.  THIS STATE WILL NOT BE REMOVED.
								// So, if you make this loop, it will probably loop forever and ever.
	bool m_loopOutAnim;

	bool m_setVisualState;		// if true, then *DO NOT* add state layer, but rather *SET* the unit's visual state
ENDCLASS

// Replace the visual effect for conversions.
DATACLASS_INHERIT(EffectReplaceConversionVisual, SubEffect)
	DBINDEX(DbVisualState) m_newPriestState;	// Name of the alternate priest attack state to use.
	const char*			   m_newTargetVisual;	// Name of the alternate target effect to play
ENDCLASS

// <blink> Make the tech buttons flash! </blink>
DATACLASS_INHERIT(EffectTechButtonFlash, SubEffect)
	// Hmm... We don't even need any data.
ENDCLASS

// @EE2X Daniel
// player's region power recharge rate is scaled by 'scale' (bigger = faster)
DATACLASS_INHERIT(EffectRegionPowerRechargeRate, SubEffect)
	float m_scale;
ENDCLASS

// @EE2X @MRC
// Player gets max morale and fervor in territories he controls, as if there were the max number
// of houses in the territory.
DATACLASS_INHERIT(EffectMaxMoraleFervor, SubEffect)
ENDCLASS

// @EE2X @MRC
// If a player has this area effect, then she steals technology when sabotaging temples and
// universities.
DATACLASS_INHERIT(EffectTechnologyTrance, SubEffect)
ENDCLASS


DATACLASS_INHERIT(EffectDuration, SubEffect)
	const char *m_effect;				// name of super effect whose duration we are scaling
	USER int m_effectIndex;				// super effect DB index (resolved on post load)
	float m_scale;						// duration scaling factor
ENDCLASS

// Increment or decrement the glow counter.  It can be a good glow, or it can
// be a bad glow.
DATACLASS_INHERIT(EffectVisualGlow, SubEffect)
	bool m_SuppressGlow;			// should the glow be supressed (leaving icon & tooltip)
	enum eGlowType m_GlowType;
	bool m_OwnerOnly;			// Should this glow appear to the owner of the unit only?

	// For the Unit Info Panel
	DBINDEX(DbSprite)	m_Icon;			// icon
	DBINDEX(DbText)		m_Tooltip;		// tooltip
	DBINDEX(DbText)		m_VTooltip;		// verbose tooltip
	
	// @MRC This is a complete one-off hack.  If this is true, the glow
	// should use a special verbose tooltip
	bool m_UseResistanceVTooltip;
ENDCLASS

// Change the color of the affected units.
DATACLASS_INHERIT(EffectColorChange, SubEffect)
	LRGBA m_Color;	// What color should the units be changed to?
ENDCLASS

DATACLASS_INHERIT(TimedSubEffect, SubEffect)
	// how long does the (de)contamination process take?
	float m_time;

	// name of visual state to invoke for m_time on SOURCE UNIT
	DBINDEX(DbVisualState) m_stateName;
ENDCLASS

// convert a whole bunch of units in the targeted area
DATACLASS_INHERIT(EffectMassConvert, TimedSubEffect)
	float chance;		//base chance of success 
ENDCLASS

// Create a "conversion area" in which units may be converted.   This area
// can last for an extended period of time.
DATACLASS_INHERIT(EffectMassConvertOverTime, SubEffect)
	float chance;		//base chance of success 
ENDCLASS

DATACLASS_INHERIT(EffectConvertOverTime, SubEffect)
	float m_timeToConvert;		//base chance of success 
ENDCLASS

// Allow a unit to be protected from deletion.
DATACLASS_INHERIT(EffectPreventDeletion, SubEffect)
ENDCLASS

DATACLASS_INHERIT(EffectProselytizing, SubEffect)
	float chance;								//base chance of success 
	DBINDEX(DbUnitTypeAttribute) targetMask;	
	enum ePlayerMode targetPlayer;
ENDCLASS

DATACLASS_INHERIT(EffectPurchaseUnit, TimedSubEffect)
	// which resource types are included in cost
	LSizedArray<enum eResourceType> m_affectedResourceTypes;
	
	// what to scale cost by (bigger = more expensive)	
	float scale;		
	
	// should we sum unit cost for all resource types,
	// then scale by 'scale', then charge the capitalist that amount in gold?
	bool m_isCapitalism; 
ENDCLASS

// gather intelligence from selected unit,
// will attach m_playerEffectName to player that owns unit it is attached to,
DATACLASS_INHERIT(EffectGatherIntel, TimedSubEffect)
	const char* m_playerEffectName;

	// how long will target player's
	// crown data be visible to source player?
	int m_intelSourceDuration;
ENDCLASS

DATACLASS_INHERIT(EffectTimedUndoable, TimedSubEffect)
	bool m_undo;	// true if DEcontamination

	// name of visual state to use if m_undo,
	// else uses m_statename from TimedSubEffect
	DBINDEX(DbVisualState) m_undoStateName;
ENDCLASS

// contaminate/cleanup selected unit
DATACLASS_INHERIT(EffectContaminate, EffectTimedUndoable)
ENDCLASS

// sabotage/restore selected unit
DATACLASS_INHERIT(EffectSabotage, EffectTimedUndoable)
ENDCLASS

// sabotage selected unit
DATACLASS_INHERIT(EffectBless, TimedSubEffect)
ENDCLASS

// This is added to every power that is a crown power.
// Note: this is player attached but affects units.
DATACLASS_INHERIT(EffectIsACrown, SubEffect)
	enum eCrownType	m_crownType;
ENDCLASS

// Start the specified area effect and attach it to a player.
DATACLASS_INHERIT(EffectStartPlayerEffect, SubEffect)
	const char* m_playerEffectName;
ENDCLASS

// affected units that are converted are graced
// with an exact duplicate of themselves.
DATACLASS_INHERIT(EffectCloning, SubEffect)
ENDCLASS

// affected units are treated as if they were disguised (ala Spy)
DATACLASS_INHERIT(EffectCloak, SubEffect)
ENDCLASS

// affected units are not allowed to move
DATACLASS_INHERIT(EffectImmobilize, SubEffect)
ENDCLASS

// Attach this effect to players.  If a player has this effect, that player
// will receive a little bit of each transaction performed at all trade buildings
// in the world.
DATACLASS_INHERIT(EffectBlackMarket, SubEffect)
	enum eResourceType m_TypeToSteal;		// What type of resource to steal
	float m_AmountPerTransactionFixed;		// Fixed amount of resource to get per transaction
	float m_AmountPerTransactionPercent;	// Percent amount of resource to get per transaction
	bool m_AffectSelf;						// True if you get something for your own transactions,
											// false otherwise.
ENDCLASS

// Adds a button to a unit.  Not the same as the button in DbAreaEffectInfo.
// This is for using the area effect system to add special, temporary buttons
// to units.  Each button presumably needs a fair amount of special code, but
// I leave that to you.
DATACLASS_INHERIT(EffectButton, SubEffect)
	const char* m_buttonName;
	bool m_limitToOneUnit;		// If this is true, the button will appear disabled
								// if the selection contains more than one unit.  Be aware
								// that the GUI will work OK, but the hotkey might need some
								// custom support.
ENDCLASS


DATACLASS_INHERIT(EffectExplode, SubEffect)
	// name of the explosion we are going to trigger
	const char* m_explosionName;

	// if hitRadius > 0, then we well select live units
	// using the hitMask and hitPlayerMode given,
	// this unit list will then be sent as a "hitList" to the explosion visuals
	// (needed for EMP spark effect for example)
	float m_hitRadius;
	// UTA and corresponding player mode to use
	// when selecting units to populate the 'hit list' that's sent to the explosion
	DBINDEX(DbUnitTypeAttribute) m_hitMask;
	enum ePlayerMode m_hitPlayerMode;
ENDCLASS

// @EE2X @MRC
// When the recipient of this effect is garrisoned, maybe propagate one or more area effects.
DATACLASS_INHERIT(EffectPropagateWhenGarrisoned, SubEffect)
	// UTA defining which types of hosts will allow the effects to be propagated.
	// For example, you could restrict this subeffect so that the effects are only
	// propagated if the unit is in a City Center.
	DBINDEX(DbUnitTypeAttribute) m_HostMask;

	// If true, attach the specified effects to the garrison host.  If false,
	// the subeffects will be attached to the player.
	bool m_AttachToGarrisonHost;

	// The name of the effects to propagate
	LSizedArray<const char*> m_EffectsToPropagate;
ENDCLASS

// @EE2X @MRC
// If a unit has this effect, it is a supreme leader.
DATACLASS_INHERIT(EffectSupremeLeader, SubEffect)
	DBINDEX(DbUnitTypeAttribute)	m_GarrisonVisualMask;	// Mask to define which buildings get the special
															// garrison visual for this supreme leader.
	const char* m_GarrisonVisualName;	// The name of a visual to put on a building when the unit is
										// garrisoned
ENDCLASS
///////////////////////////////////////////////////////////////////////////////
///////////////////////Effects that don't apply to Units///////////////////////
///////////////////////////////////////////////////////////////////////////////

//Players affected by EffectPopulation have their population scaled by
//scale.
DATACLASS_INHERIT(EffectPopulation, SubEffect)
	const char* m_UnitType;	// What unittype will this change the pop capacity for?
							// Because it only modifies the population capacity one
							// type at a time.
	float scale;			//what to scale population by. (larger = more populous)
ENDCLASS


DATACLASS_INHERIT(EffectPopulationAdditive, SubEffect)
	// amount to *ADD* to population cap
	// (applied after multiplication, see EffectPopulation)
	float amount;
ENDCLASS

//This affects how much a tech costs a player.
DATACLASS_INHERIT(EffectTechCost, SubEffect)
	float scale;		//what to scale cost by. (smaller = cheaper)
ENDCLASS

//This affects how fast a player can research a tech.
DATACLASS_INHERIT(EffectTechDiscoveryTime, SubEffect)
	float scale;		//what to scale time by. (smaller = faster)
ENDCLASS


#endif // DBAREAEFFECTDEFS_H