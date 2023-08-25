//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbUnitTypeAttributeDefs.h 12    9/29/05 4:26p Dsproul $
//
// DESCRIPTION:		The UnitTypeAttribute class has a few enums that control
//					its matching behavior.  They are contained here.
//
// AUTHOR:			Ben Morse
//
//===========================================================================

#ifndef DBUNITTYPEATTRIBUTEDEFS_H
#define DBUNITTYPEATTRIBUTEDEFS_H
#pragma once

#include "HdrMacros.h"
#include "LSizedArray.h"

//wow, sure hope this works
class UnitTypeAttribute;

// Player mode enumeration - each UnitTypeAttribute has a player mode, which
// is used to determine whether units are contained in the set described by a
// UnitTypeAttribute depending on their ownership.  For a unit, its mode will
// be kPlayerMode_Self, which is the default for all UnitTypeAttributes.
ENUM ePlayerMode {
	kPlayerMode_Anybody,		//all players (including the world player)
	kPlayerMode_Self,			//only units that belong to me.
	kPlayerMode_Allies,			//only units that belong to my allies
	kPlayerMode_SelfAndAllies,	//units that belong to me OR my allies
	kPlayerMode_SelfAndLiege,	//units that belong to me OR my liege lord
	kPlayerMode_Enemies,		//units that belong to my declared enemies
	kPlayerMode_NonSelf,		//enemies and allies, just not me
	kPlayerMode_World,			//the world player only (resources, animals)
	kPlayerMode_NotTheWorld,	//anybody who is not the world player
	kPlayerMode_NonAlliedPlayers,	// non-allied, non-world players.  legitimate targets for the AI.
	kNumPlayerModes,
};

// Mask mode enumeration - each UnitTypeAttribute has a mask mode, which is
// used to distinguish cases where we want our set to only include units
// with ALL or ANY of the abilities asserted in the bit-array.
// the defualt mode is kMaskMode_All.
// kMaskMode_NotAny selects only unit WITHOUT the selected ability
ENUM eMaskMode {
	kMaskMode_All,
	kMaskMode_Any,
	kMaskMode_NotAny,
	kNumMaskModes,
};

// This is an adapter dataclass that allows UnitTypeAttributes to be defined
// in a .ddf file, named, and loaded into a database, then referred to using
// a DBINDEX in other DATACLASSes.
DATACLASS(DbUnitTypeAttributeDef)
	enum eMaskMode m_MaskMode;
	LSizedArray<enum eUnitAbilityType> m_AbilityMask;
	LSizedArray<enum eUnitMoveType> m_MovementMask;
	LSizedArray<enum eUnitRPS> m_RPSMask;
	LSizedArray<enum eUnitTypeAttr> m_ExtraMask;
	LSizedArray<const char *> m_UnitTypeInstances;
	LSizedArray<const char *> m_UnitTypeFamilies;
ENDCLASS

#endif // DBUNITTYPEATTRIBUTEDEFS_H
