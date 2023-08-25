//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbFrontEndDefs.h 35    9/20/05 12:57p Dsproul $
//
// DESCRIPTION:   miscellaneous front-end definitions
//
// AUTHOR:        Daniel Sproul
//
//===========================================================================

#ifndef DB_FRONTENDDEFS_H
#define DB_FRONTENDDEFS_H
#pragma once

#include "HdrMacros.h"



////////////////////////////////////////////
//
// game settings
//

ENUM eGameSpeed {
	kGameSpeed_Slow,
	kGameSpeed_Normal,
	kGameSpeed_Fast,
	kGameSpeed_VeryFast,
	kNumGameSpeedTypes,
};

ENUM eMapRevealedLevel{
	kMapRevealedLevel_Unrevealed,
	kMapRevealedLevel_Explored,
	kMapRevealedLevel_Revealed,
};

ENUM eCeaseFireTime{
	kCeaseFireTime_None,
	kCeaseFireTime_min2,
	kCeaseFireTime_min5,
	kCeaseFireTime_min10,
	kCeaseFireTime_min15,
};

// territory population cap
ENUM eTerrPopCap{
	kTerrPopCap_p20,
	kTerrPopCap_p30,
	kTerrPopCap_p40,
	kTerrPopCap_p50,
	kTerrPopCap_p60,
};

// tournament mode
ENUM eTournamentMode{
	kTournamentMode_Slow,
	kTournamentMode_Medium,	// default setting
	kTournamentMode_Fast,
	kTournamentMode_Custom,
};

// Max Population for the whole game
ENUM eMaxPopulation{
	kMaxPopulation_p100 = 100,
	kMaxPopulation_p200 = 200,
	kMaxPopulation_p400 = 400,
	kMaxPopulation_p600 = 600,
	kMaxPopulation_p800 = 800,
	kMaxPopulation_p1000 = 1000,
	kMaxPopulation_p1200 = 1200,
	kMaxPopulation_p1600 = 1600,
	kMaxPopulation_p2000 = 2000,
        kMaxPopulation_p2600 = 2600,
	kMaxPopulation_p3000 = 3000,
	kMaxPopulation_p3400 = 3400,
	kMaxPopulation_p3800 = 3800,
	kMaxPopulation_p4000 = 4000,
        kMaxPopulation_p10000 = 10000,
};

// The minimum is used for some comparisons when loading old files.
const eMaxPopulation kMaxPopulationMinimum = kMaxPopulation_p100;
// The default is the default that gets used when we're not loading or fail
// to load a good value.
const eMaxPopulation kMaxPopulationDefault = kMaxPopulation_p1600;

// starting citizens (for basic starting forces)
// value should be the actual num citizens
ENUM eQuickStartCit{
	kQuickStartCit_n1	= 1,
	kQuickStartCit_n5	= 5,
	kQuickStartCit_n10	= 10,
	kQuickStartCit_n15	= 15,
	kQuickStartCit_n20	= 20,
	
};

// @EE2X -- Daniel 04/15/05
// Native Tribes stuff
ENUM eNativeTribesAmount {
	kNativeTribesAmount_None,
	kNativeTribesAmount_Some,
	kNativeTribesAmount_Many,
};

// @EE2X
// combining sole survivor and locked teams into one option box
// since they're mutually exclusive with fealty
ENUM eTeamState {
	kTeamState_Normal,
	kTeamState_Locked,
	kTeamState_SoleSurvivor,
	kTeamState_Fealty,
	kNumTeamStates,
};

////////////////////////////////////////////
//
// map settings
//

ENUM eElevation {
	kElevation_Lowlands,
	kElevation_Hills,
	kElevation_Mountains,
	kNumMapElevationTypes,
	
	kElevation_Invalid = -1,
	kElevation_Random = -2,
};

ENUM eRiverLevel {
	kRiverLevel_None,
	kRiverLevel_Some,
	kRiverLevel_Many,
	kNumRiverLevels,

	kRiverLevel_Invalid = -1,
	kRiverLevel_Random = -2,
};

ENUM eResLayout {
	kResLayout_Uniform,
	kResLayout_NonUniform,
	kResLayout_Asymmetrical,
};



///////////////////////////////////////////
//
// environmental settings
//

ENUM eSeason {
	kSeason_Winter, 
	kSeason_Spring,
	kSeason_Summer, 
	kSeason_Fall, 
	kNumSeasons,

	kSeason_Invalid = -1,
	kSeason_Random = -2,
};

ENUM eTimeOfDay {
	kTimeOfDay_Dawn,
	kTimeOfDay_Afternoon,
	kTimeOfDay_Sunset,
	kTimeOfDay_Night,
	kNumTimeOfDays,
	
	kTimeOfDay_Invalid = -1,
	kTimeOfDay_Random = -2,
};

ENUM eMinutesPerSeason {
	kMinutesPerSeason_1		= 1,
	kMinutesPerSeason_5		= 5,
	kMinutesPerSeason_10	= 10,
	kMinutesPerSeason_20	= 20,
	kMinutesPerSeason_30	= 30,
};



//////////////////////////////////////////////
//
// player info settings
//

//
// player type (with cpu difficulty rolled in)
//
ENUM eFePlayerType {
	kFePlayerType_Human,
	kFePlayerType_Observer,
	kFePlayerType_OpenHuman,
	kFePlayerType_OpenObserver,
	kFePlayerType_ComputerEasiest,
	kFePlayerType_ComputerEasier,
	kFePlayerType_ComputerEasy,
	kFePlayerType_ComputerNormal,
	kFePlayerType_ComputerHard,
	kFePlayerType_ComputerHardest,
};

//
// teams
//
ENUM eTeam {
	kTeam_0,
	kTeam_1,	
	kTeam_2,	
	kTeam_3,	
	kTeam_4,
	kTeam_5,	
	kTeam_6,	
	kTeam_7,	
	kTeam_8,
	kTeam_9,	
	kNumTeams,
};

ENUM eFePlayerHandicap {
	kFePlayerHandicap_Newbie,
	kFePlayerHandicap_Average,
	kFePlayerHandicap_Good,
	kFePlayerHandicap_Expert,
	kFePlayerHandicap_GameGod,
};


//////////////////////////////////////////////
//
// victory conditions

// duration for timed crowns
ENUM eVCCrownsDuration {
	kVCCrownsDuration_10	= 10,
	kVCCrownsDuration_15	= 15,
	kVCCrownsDuration_20	= 20,
	kVCCrownsDuration_25	= 25,
	kVCCrownsDuration_30	= 30,
	kVCCrownsDuration_60	= 60,
	kVCCrownsDuration_120	= 120,
	kVCCrownsDuration_180	= 180,
};

// duration for capitols or allied capitols
ENUM eVCCapitolsDuration {
	kVCCapitolsDuration_2	= 2,
	kVCCapitolsDuration_5	= 5,
	kVCCapitolsDuration_10	= 10,
	kVCCapitolsDuration_20	= 20,
	kVCCapitolsDuration_30	= 30,
	kVCCapitolsDuration_300	= 300,
	kVCCapitolsDuration_600	= 600,
	kVCCapitolsDuration_1800	= 1800,
};

// duration for king of the hill
ENUM eVCKingOfHillDuration {
	kVCKingOfHillDuration_2		= 2,
	kVCKingOfHillDuration_5		= 3,
	kVCKingOfHillDuration_10	= 4,
	kVCKingOfHillDuration_20	= 5,
	kVCKingOfHillDuration_30	= 10,
	kVCKingOfHillDuration_40	= 30,
};


//////////////////////////////////////////////
//
// misc multiplayer settings
//

// constants used for MP game type (see EE2EnumTableManager.cpp...)
// these should be distinct and less than zero
const int kMPGameType_LoadSavedGame = -1;
const int kMPGameType_LoadScenario = -2;

// load a tug of war gaem
const int kMPGameType_LoadTugofWar = -7;

//
// num human players for MP game
//
ENUM eMPNumHumanPlayers {
	kMPNumHumanPlayers_2 = 2,
	kMPNumHumanPlayers_3,
	kMPNumHumanPlayers_4,
	kMPNumHumanPlayers_5,
	kMPNumHumanPlayers_6,
	kMPNumHumanPlayers_7,
	kMPNumHumanPlayers_8,
	kMPNumHumanPlayers_9,
	kMPNumHumanPlayers_10,
};


//
// modes governing what happens when a node player quits the game
//
ENUM eMPDestroyPlayerMode {
	kMPDestroyPlayerMode_Remove,	// completely remove the player (and all units)
	kMPDestroyPlayerMode_NoAI,		// leave the player as type human (no AI)
	kMPDestroyPlayerMode_CreateAI,	// change player type to computer and create an AI
};

//
// destroyed player mode (with AI difficulty rolled in)
//
ENUM eMPDestroyPlyrAIDiff {
	kMPDestroyPlyrAIDiff_Remove,
	kMPDestroyPlyrAIDiff_NoAI,
	kMPDestroyPlyrAIDiff_AIEasiest,
	kMPDestroyPlyrAIDiff_AIEasier,
	kMPDestroyPlyrAIDiff_AIEasy,
	kMPDestroyPlyrAIDiff_AINormal,
	kMPDestroyPlyrAIDiff_AIHard,
	kMPDestroyPlyrAIDiff_AIHardest,
};


//
// rating type for a GameSpy game
//
// @IMPORTANT keep up-to-date with:
//		GameSpy::aszRatingTypes[]
//		MPUtils::s_aszLocalizedRatingTypeSuffixes[]
//		MPUtils::GetEnglishGameDescriptor::s_aszEnglishRatingTypes[]
//		MPScreenGameSpyLobby::GetRowEntriesForServer::s_aszAbbrevRatingTypes[]
//
ENUM eGameSpyRating {
	kGameSpyRating_Unrated,
	kGameSpyRating_Tournament,
	kGameSpyRating_Skirmish,
	kNumGameSpyRatingTypes,

	kGameSpyRating_Invalid = -1,
};

//
// privacy type for a GameSpy game
//
ENUM eGameSpyPrivacy {
	kGameSpyPrivacy_Open,
	kGameSpyPrivacy_Password,
};


#endif // DB_FRONTENDDEFS_H
