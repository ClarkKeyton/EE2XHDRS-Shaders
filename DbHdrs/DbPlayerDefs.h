//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbPlayerDefs.h 22    7/01/05 3:42p Dsproul $
//
// DESCRIPTION:   DbPlayerDefs.h has parser-readable player definitions.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBPLAYERDEFS_H
#define DBPLAYERDEFS_H
#pragma once

#include "HdrMacros.h"


//	Player types

ENUM ePlayerType {
	kPlayerType_Human,		// human-controlled player
	kPlayerType_Computer,	// AI-controlled player
	kPlayerType_Observer,	// just watching a game @NOTE this is just a hack to facilitate
							// setup of MP games with observers and is distinct from the
							// game ui being in observer mode
							
	kPlayerType_Invalid = -1,	// invalid player type
};

//	Player civilizations
//  @NOTE: IF THIS CHANGES IN SOME WAY, MAKE THE CORRESPONDING CHANGE IN THE CIV ENUM
//  OF  DbTechTreeDefs.h!!!!!  Also there is a routine called CivilizationToRegion in
//	PlayerDefs which would need to be updated.
ENUM ePlayerCivilization {
	// West region
	kPlayerCivilization_German = 0,	//0
	kPlayerCivilization_English,	//1
	kPlayerCivilization_Roman,		//2
	kPlayerCivilization_American,	//3
	kPlayerCivilization_Greek,		//4
	
	// FarEast region
	kPlayerCivilization_Chinese,	//5
	kPlayerCivilization_Korean,		//6
	kPlayerCivilization_Japanese,	//7	@NOTE: IF CHANGING THIS, SEE NOTE ABOVE!!!

	// MiddleEast region
	kPlayerCivilization_Egyptian,	//8
	kPlayerCivilization_Turkish,	//9
	kPlayerCivilization_Babylonian,	//10

	// MesoAmerican region
	kPlayerCivilization_Inca,		//11
	kPlayerCivilization_Aztec,		//12
	kPlayerCivilization_Mayan,		//13

	// African Region
	kPlayerCivilization_Maasai,		//14
	kPlayerCivilization_Zulu,		//15

	//@EE2X part of the West region.  cannot be stuck with the rest of the west region because EE2 would not be correct anymore
	kPlayerCivilization_French,		//16
	kPlayerCivilization_Russian,	//17

	kNumPlayerCivilization,
	kPlayerCivilization_Random = -1,	// random; list before unused for settings.cfg readability
	kPlayerCivilization_Unused = -1,

	// @EE2X custom civs are marked thusly
	kPlayerCivilization_Custom = -2,

	//Enumerations to mark the first/last civs in each region:
	
	// western
	// @NOTE be careful when iterating, not all civs are contiguous in EE2X!
	kPlayerCivilization_FirstWestern = kPlayerCivilization_German,
	kPlayerCivilization_LastWestern = kPlayerCivilization_Russian,
	
	// FarEast
	// @NOTE be careful when iterating, not all civs are contiguous in EE2X!
	kPlayerCivilization_FirstFarEast = kPlayerCivilization_Chinese,
	kPlayerCivilization_LastFarEast = kPlayerCivilization_Japanese,
	
	// MiddleEast
	// @NOTE be careful when iterating, not all civs are contiguous in EE2X!
	kPlayerCivilization_FirstMiddleEast = kPlayerCivilization_Egyptian,
	kPlayerCivilization_LastMiddleEast = kPlayerCivilization_Babylonian,
	
	// Meso american
	// @NOTE be careful when iterating, not all civs are contiguous in EE2X!
	kPlayerCivilization_FirstMesoAmer = kPlayerCivilization_Inca,
	kPlayerCivilization_LastMesoAmer = kPlayerCivilization_Mayan,

	// African 
	// @NOTE be careful when iterating, not all civs are contiguous in EE2X!
	kPlayerCivilization_FirstAfrican = kPlayerCivilization_Maasai,
	kPlayerCivilization_LastAfrican = kPlayerCivilization_Zulu,

}; // enum PlayerCivilizatio...

// @EE2X not all civs in a region are contiguous, doh!
// how many civs in each region?
static const int kNumWesternCivs = 7;
static const int kNumFarEastCivs = 3;
static const int kNumMiddleEastCivs = 3;
static const int kNumMesoAmericanCivs = 3;
static const int kNumAfricanCivs = 2;


//---------------------------------------------------------------------------------------------
//@NOTE if someone add a region, do not forget to add a initial for that particular region in:
// SRC\EE2\PLAYER\PlayerCivilisation.h under the function GetRegionalPostFix()
//
ENUM eCivilizationRegion {
	kCivilizationRegion_West = 0,
	kCivilizationRegion_FarEast,
	kCivilizationRegion_MiddleEast,
	kCivilizationRegion_MesoAmerican,
	kCivilizationRegion_African,

	kNumCivilizationRegion,

	// invalid region!
	// putting this last so we don't screw things up
	kCivilizationRegion_Invalid = -1,
};

//	Player colors

ENUM ePlayerColor {
	kPlayerColor_Blue,
	kPlayerColor_Red,
	kPlayerColor_Green,
	kPlayerColor_Orange,
	kPlayerColor_Magenta,
	kPlayerColor_Cyan,
	kPlayerColor_Yellow,
	kPlayerColor_Lavender,
	kPlayerColor_Purple,
	kPlayerColor_Gold,

	kPlayerColor_LastAvailableToNonWorldPlayer = 9,		// should be same as previous entry

	kPlayerColor_Grey,
	kPlayerColor_WorldPlayerColor = 10,		// should be same as previous entry
	
	kPlayerColor_NativeTribePlayerColor = 10,

	kPlayerColor_Num,
};



#endif // DBPLAYERDEFS_H
