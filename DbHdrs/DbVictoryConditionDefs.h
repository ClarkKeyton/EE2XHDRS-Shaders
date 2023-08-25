//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbVictoryConditionDefs.h 8     6/07/05 10:47a Tteich $
//
// DESCRIPTION:   victory condition types
//					(just moved from VictoryConditions.h to expose to parser)
//
// AUTHOR:        Daniel Sproul
//
//===========================================================================

#ifndef DB_VICTORYCONDITIONDEFS_H
#define DB_VICTORYCONDITIONDEFS_H
#pragma once

#include "HdrMacros.h"


// Each eVictoryCondType represents a different way to win the game.
// KEEP THIS SYNCHRONIZED with s_aszVictoryConditions in UIVCondPicker.cpp!
// KEEP THIS SYNCHRONIZED with g_aszGRKey_GameType in GameSpy.cpp!
ENUM eVictoryCondType {
	// the player (or player's team) wins if all meaningful units of the other player (other team)
	// are eliminated
	kVictoryCondType_Conquest,
		
	// a player wins after he has achieved a specified number of (different) crowns
	kVictoryCondType_CrownsNumber,
	
	// a playw wins if he can hold the specified combination of the crowns for a specified duration
	kVictoryCondType_CrownsTime,
	
	//A ScriptSaySo clause is satisfied by the script library.  In a script,
	//if you do a 'SetWinner(N)' call, then this clause will be true.
	//Notice that you need script support AND this clause for this type of
	//goal to work!
	kVictoryCondType_ScriptSaySo,
	
	// the first player to capture the neutral city-state and hold if for a specified amount of time wins
	kVictoryCondType_KingOfTheHill,
	
	// A player is knocked out if he lost his capital (first city) until only 1 player is left
	kVictoryCondType_Capitols,
	
	// A player is turned into observer if his captal is lost, he can be brought back if his capitol was
	// captured and his teammates recapture it for him
	kVictoryCondType_AlliedCapitols,
	
	// a player is knocked out if he lost his military leader (given to him at the beginning of the game)
	kVictoryCondType_Regicide,
	
	// a number of hot spots will be revealed during the course of the game, the player can claim a hot spot
	// by building a fortress on it. the player that claimed the most hot spots wins the game (ties are possible)
	kVictoryCondType_HotSpots,
	
	// a player wins after he has gained control
	// of a specified percentage of territories
	kVictoryCondType_TerritoryControl,
		
	// like hotspots, but instead of points, the hotspots are territories
	kVictoryCondType_HotSpots_Terr,
	
	// this is NOT really a victory condition, but we pretend it is for game
	// setup purposes
	kVictoryCondType_TugOfWar,
	
	kNumVictoryCondTypes,
};



#endif // DB_VICTORYCONDITIONDEFS_H
