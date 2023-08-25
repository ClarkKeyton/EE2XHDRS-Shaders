//===========================================================================
// Copyright 2005 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbDiplomacyDefs.h 3     8/10/05 12:25p Mcorthell $
//
// DESCRIPTION:		holds the enums related to the diplomacy system
//
// AUTHOR:			Jason Dunlop
//
//===========================================================================

#ifndef DBDIPLOMACYDEFS_H
#define DBDIPLOMACYDEFS_H
#pragma once

#include "HdrMacros.h"

ENUM eDiplomaticState {
	//If player X is hostile toward player Y, player X automatically gets
	//the 'attack' cursor when mousing over Y's units.  These enemy units
	//will also be considered valid targets of opportunity (based on the
	//players unit AI settings).  This is a nonreflexive state - X's
	//hostility toward Y doesn't necessarily imply Y's hostility toward X.	
	kDiplomaticState_Hostile,

	//Player's who have a neutral diplomatic stance don't get the attack
	//cursor by default, but can use a keyboard modifier key to initiate
	//attack.  Trading is allowed between neutral players.
	kDiplomaticState_Neutral,

	//When two players are allied, all kinds of stuff can happen depending
	//on the scope of their alliance.  This is a reflexive relationship -
	//'X allied with Y' implies 'Y allied with X' in the exactly symmetric
	//fashion.
	kDiplomaticState_Allied,

	kNumDiplomaticStates,
};

ENUM eAllianceDuration {
	//The alliance will only last until war is declared by either party.
	kAllianceDuration_UntilWar,

	//The alliance has a specific time duration and cannot be broken
	//until then.
	kAllianceDuration_Timed,

	kNumAllianceDurations,
};

ENUM eAllianceLOSState {
	//Each party gets full shared LOS from the other's units.
	kAllianceLOSState_Full,

	//Each party only gets shared LOS from the other's buildings.
	kAllianceLOSState_Buildings,

	//Each party only gets shared LOS from the other's mobile units
	kAllianceLOSState_MobileUnits,

	//Neither party gets any LOS from the other.
	kAllianceLOSState_None,

	kNumAllianceLOSStates,
};


ENUM eAllianceBorderPerm {
	//Each player has full access to the other player's empire, regardless of
	//borders.
	kAllianceBorderPerm_Full,

	//Only civilian units may pass through the other player's borders.
	kAllianceBorderPerm_Civilian,
	
	// only trade units may pass through the other player's borders.
	kAllianceBorderPerm_Trade,

	//No units may pass through the other player's borders.
	kAllianceBorderPerm_None,

	kNumAllianceBorderPerms,
};

ENUM eAllianceResRight {
	//Other player may freely harvest from any resource located within
	//the other player's borders.  (UI note: this should automatically
	//set the Borders option to no military (assuming it isn't at
	//'full' already).
	kAllianceResRight_Full,

	//The player individually specifies the resources that can be
	//harvested by the other player.  The player also specifies a 'Tariff'
	//associated with the resource rights.  This is a percentage that the
	//player harvesting pays in the resource being harvested.  Valid
	//percentages range from 1 to 99% (default is 0).
	kAllianceResRight_Specified,

	//Other player may not harvest any resource located within the other
	//player's borders.  
	kAllianceResRight_None,
	
	kNumAllianceResRights,
};

// Information about resistance, when one player refuses an offer of fealty from
// another player.
DATACLASS(DbResistanceInfo)
	// How long does the resistance last, in seconds.
	float m_Duration;

	// What attack bonus does the resisting player get against players that
	// she is resisting?  0.5 would cause her units to do 50% more damage.
	float m_AttackBonus;
	// What units get the attack bonus
	const char* m_AttackUnitMask;
	
	// What defense bonus does the resisting player get against players that
	// she is resisting?  -0.5 woulc cause her units to take 50% less damage
	float m_DefenseBonus;
	// What units get the defense bonus
	const char* m_DefenseUnitMask;
	
	// What glow effect should we apply?
	const char* m_GlowEffect;

ENDCLASS

#endif // DBDIPLOMACYDEFS_H
