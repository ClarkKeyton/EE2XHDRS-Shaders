//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbGameSettingsDefs.h 45    10/04/05 12:53p Dsproul $
//
// DESCRIPTION:   DbGameSettingsDefs.h holds game user settings.
//
// AUTHOR:        Jason Dunlop
//
//===========================================================================

#ifndef DBGAMESETTINGSDEFS_H
#define DBGAMESETTINGSDEFS_H
#pragma once

#include "hdrmacros.h"

//
//	IMPORTANT NOTE:  if you change any of these data classes, you must also update UserGameSettings.cpp:
//						UserGameSettings::LoadSettings()
//						UserGameSettings::SaveSettings()
//

//
// dataclass for player info (should loosely correspond to class PlayerInfo)
//
DATACLASS(DbPlayerInfoDef)
	char					   *m_name;			// custom display name
	DBINDEX(DbText)				m_nameIndex;	// localized display name
	enum ePlayerType			m_type;
	enum eDifficultySetting		m_difficulty;
	enum ePlayerCivilization	m_civ;
	char					   *m_customCiv;	// custom civ!
	enum ePlayerColor			m_color;
	int							m_epoch;	// override range-specified epoch (if 0, overall start epoch is used)
	enum eFePlayerHandicap		m_handicap;
	bool						m_active;
	DBINDEX(DbNativeTribes)		m_tribe;
	DBINDEX(DbAreaEffects)		m_nativePower;
ENDCLASS

//
// dataclass for tournament mode (game pace) settings
//
DATACLASS(DbTournamentModeDef)
	// ------- advanced settings (tournament mode) ---------- //
	float m_fBuildTimeProduceMod;	// build speed modifier for produceables
	float m_fBuildTimeConstructMod;	// build/repair speed modifier for constructables
	float m_fHitPointMod;			// unit/building hit points modifier
	float m_fResGatherRateMod;		// resource gather rate modifier
	float m_fBuildCostMod;			// build cost modifier
	float m_fEpochUpCostMod;		// epoch up cost modifier
	float m_fTechPtGatherRateMod;	// tech point gather rate modifier
	float m_fCaptureResMod;			// capture resistance modifier
	float m_fConversionResMod;		// conversion resistance modifier
	float m_fTechResTimeMod;		// tech research time modifier
	float m_fMovementSpdMod;		// movement speed modifier
	float m_fDamageMod;				// total damage modifier
	float m_fStaticDefense;			// strength of outposts, fortresses, etc.
ENDCLASS

//
// dataclass for all game settings (should loosely correspond to class GameInfo)
//
DATACLASS(DbGameSettingsDef)
	// victory condition
	enum eVictoryCondType m_victoryCondition;
	int						m_victoryConditionParameter;
	int						m_victoryConditionSecondaryParameter;

	// game settings
	int						m_startEpoch;
	bool					m_startEpochRandom;
	int						m_endEpoch;
	bool					m_endEpochRandom;
	enum eMapRevealedLevel	m_revealMap;
	enum eTeamState				m_eTeamState;
	bool					m_enableCheats;
	bool					m_lockSpeed;
	bool					m_teamPlacement;
	enum eGameSpeed			m_gameSpeed;
	enum eResourceLevels	m_resources;
	enum eCeaseFireTime		m_initialCeaseFire;
	enum eTerrPopCap		m_eTerrPopCap;
	enum eTournamentMode	m_eTournamentMode;
	enum eMaxPopulation		m_eMaxPopulation;
	bool					m_playerMaxPopCapStaysSameForGame;

	// @EE2X -- Daniel 04/15/05
	// Native Tribes stuff
	enum eNativeTribesAmount m_NativeTribesAmount;
	int						 m_NativeTribesExactAmount;
	enum eDifficultySetting	 m_NativeTribesDifficulty;
	enum eQuickStartArmySize m_NativeTribesArmySize;

	bool					m_startingForcesAdvanced;
	enum eQuickStartCit		m_staringForcesBasic_CitCount;
	enum eQuickStartArmySize m_staringForcesAdvanced_ArmySize;


	// map settings
	DBINDEX(DbMapSize)		m_mapSize;
	enum eRiverLevel		m_riverAmount;
	enum eForestation		m_forestation;
	enum eElevation			m_elevation;
	DBINDEX(DbMapGeography)	m_geography;
	DBINDEX(DbRandomMapGeography) m_randomGeographyType;
	bool					m_geographyRandom;	// @HACK we write this extra bool primarily to help make the settings a bit more legible...
	DBINDEX(DbClimate)      m_climate;
	bool					m_climateRandom;
	enum eResLayout			m_resourceLayout;

	// @TEMP developer map settings
	bool					m_flatMap;
	int						m_mapWidth;
	int						m_mapHeight;
	
	// environmental settings
	bool					m_enableSeasons;
	int						m_minutesPerSeason;
	enum eSeason			m_startingSeason;
	enum eTimeOfDay			m_timeOfDay;
	bool					m_enableWeather;
	bool					m_enableWind;

	// tournament mode (game pace) settings.  use this instead of the values below.
	DC(DbTournamentModeDef)* m_pTournamentMode;

	/// @HACK AHACK HAKC AHCK AHCKA HAKC!!!
	// THESE ARE HERE PURELY TO ALLOW FOR BACKWARD COMPATABILITY OF SETTINGS.CFG
	// DO NOT USE THESE FOR ANY REASON AT ALL.
	//
	//	THESE _SHOULD_ BE REMOVED AFTER THE PATCH IS ACCEPTED
	//
	// ------- advanced settings (tournament mode) ---------- //
	float m_fBuildTimeProduceMod;	// DO NOT USE! OBSELETE!
	float m_fBuildTimeConstructMod;	// DO NOT USE! OBSELETE!
	float m_fHitPointMod;			// DO NOT USE! OBSELETE!
	float m_fResGatherRateMod;		// DO NOT USE! OBSELETE!
	float m_fBuildCostMod;			// DO NOT USE! OBSELETE!
	float m_fEpochUpCostMod;		// DO NOT USE! OBSELETE!
	float m_fTechPtGatherRateMod;	// DO NOT USE! OBSELETE!
	float m_fCaptureResMod;			// DO NOT USE! OBSELETE!
	float m_fConversionResMod;		// DO NOT USE! OBSELETE!
	float m_fTechResTimeMod;		// DO NOT USE! OBSELETE!
	float m_fMovementSpdMod;		// DO NOT USE! OBSELETE!
	float m_fDamageMod;				// DO NOT USE! OBSELETE!
	float m_fStaticDefense;			// DO NOT USE! OBSELETE!
	// @END HACK

	bool					m_bUnbreakableTreaties;
	bool					m_bLockedHandicaps;

	// EE2X allow custom civs?
	bool m_bAllowCustomCivs;
	
	// MP settings
	enum eMPDestroyPlayerMode m_eMPDestroyPlayerMode;
	enum eDifficultySetting	 m_eMPDestroyPlayerAIDifficulty;

	// gamespy settings
	enum eGameSpyRating		m_eGameSpyRatingType;
	
	// player info
	LSizedArray<DC(DbPlayerInfoDef)*> m_Players;
ENDCLASS


#endif // DBGAMESETTINGSDEFS_H
