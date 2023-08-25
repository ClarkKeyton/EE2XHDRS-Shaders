//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbAbilityDefs.h 20    3/11/05 9:09a Dfielding $
//
// DESCRIPTION:   Enumeration of types of ability
//
// AUTHOR:        Xinbo Kan
//
//===========================================================================

#ifndef DBABILITYDEFS_H
#define DBABILITYDEFS_H
#pragma once

#include "HdrMacros.h"

// each ability has one of the following types.
// subclasses of one basic ability should share the same type (it basicly serves the purpose of RTTI)
// for example, different kinds of movement abilities (that subclass UnitAbilityMove) should all have 
// type kUnitAbilityType_Movement. A unit type, however, should have ONLY ONE instance of the ability of
// the any type (i.e. it can not have 2 different abilities of kUnitAbilityType_Movement

// WARNING: don't change the order/value of these constants unless you don't care about screwing up old map loading

ENUM eUnitAbilityType {
	kUnitAbilityType_Movement,			// move (or rotate)
	kUnitAbilityType_Attack,			// Attack enemy
	kUnitAbilityType_LOS,				// Line-Of-Sight
	kUnitAbilityType_Build,				// citizen can build something
	kUnitAbilityType_Construction,		// construction: from foundation to the eventual building, the passive
								// receiving end of eUABT_Build
	kUnitAbilityType_Produce,			// buildings produce units
	kUnitAbilityType_Connect,			// composite units (roads + walls) need info about inter-unit connections
	kUnitAbilityType_GatherFarm,		// gather resources and work on farm to gather resource
	kUnitAbilityType_Resource,			// contain resource
	kUnitAbilityType_ResourceDropoff,	// is a resource drop-off unit
//	kUnitAbilityType_TerrainOverlay,	// for roads and other units that generate overlays
	kUnitAbilityType_Research,			// ability to research
	kUnitAbilityType_Heal,				// healing ability of medic unit, etc.
	kUnitAbilityType_Garrison,			// certain units (usually buildings) can be garrisoned.
	kUnitAbilityType_Convertable,		// some units can be converted to/from enemy side by priests
	kUnitAbilityType_Gate,				// basicly, ability specific to wall gate
	kUnitAbilityType_PowerReserve,		// certain units need power to perform special abilities
	kUnitAbilityType_AreaEffect,		// some units (leaders) have persistent area effects attached
	kUnitAbilityType_SpecialPower,		// units use power (reserve) to do special things
	kUnitAbilityType_ConvertAttack,		// convert/capture
	
	kUnitAbilityType_Trade,				// trade with other players to generate wealth

	kUnitAbilityType_TemporaryAnimation,	// unit plays a temporary animation in response to a "play animation" goal
	
	kUnitAbilityType_TargetingList,		// unit maintains a list of units currently targeting it with certain goals
	
	kUnitAbilityType_PlaySound,			// unit has sounds associated with them
	kUnitAbilityType_Garrisonable,		// some units can garrison inside others (those with Garrison ability)
	kUnitAbilityType_Hero,				// ability for hero units -- @EE2X Daniel 03/09/05
	
	kNumUnitAbilityType,
};

USER extern const char *GetStringForAbilType(eUnitAbilityType abilType);	// for debugging purpose, etc.

// WARNING: don't change the order/value of these constants unless you don't care about screwing up old map loading

#endif // DBABILITYDEFS_H
