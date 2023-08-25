//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbUserDefs.h 10    7/14/05 2:58p Dsproul $
//
// DESCRIPTION:   DbUserDefs.h holds dataclasses for the User database.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBUSERDEFS_H
#define DBUSERDEFS_H
#pragma once

#include "HdrMacros.h"
#include "LSizedArray.h"
#include "DbCampaignDefs.h"

DATACLASS(DbUserScenarioState)
	char				*m_scenarioName;	// scenario name
	char				*m_saveGameName;	// save game set if scenario is in progress
	enum eDifficultySetting m_SaveGameDifficulty; // save game difficulty setting
	enum eDifficultySetting	m_HighestDifficulty;	// highest difficulty this was beat at
	bool					m_completed;	// true if scenario has been completed
	// @EE2X - Josh - Reinforcement Screen - added m_numSecondaryObj and m_heroes
	int					m_numSecondaryObj;	// number of secondary objectives the user completed
	LSizedArray< DBINDEX(DbUnit) > m_heroes;	// list of heroes the player had at the end of the scenario
												// (some of these may be carried over into the next scenario)
ENDCLASS

DATACLASS(DbUserCampaignState)
	char *m_campaignName;			// name of campaign
	LSizedArray<DC(DbUserScenarioState)*> m_scenarios;	// state of this campaign's scenarios
	// @TODO: LOCK KEY TO AVOID JUST EDITING THIS ENTRY AND UNLOCKING SCENARIOS?
ENDCLASS

DATACLASS(DbUserDef)
	char *m_userName;									// name of user
	char *m_scenarioName;								// name of the last scen played
	char *m_campaignName;								// campaign the scenario is found in
	enum eDifficultySetting m_difficulty;				// default diff setting user chose
	LSizedArray<DC(DbUserCampaignState)*> m_campaigns;	// state of campaigns
ENDCLASS


// basically unrelated class for remembering gamespy login info
DATACLASS(DbGameSpyUserDef)
	char *m_email;			// email address
	char *m_nickname;		// profile nickname (not unique nickname)
	char *m_password;		// password (@TODO find a way to encrypt when writing to text file)
	bool  m_rememberLogin;	// should we remember login attempts?
	int	  m_groupID;		// last used group ID (so we can re-join last group room)
	LSizedArray<char*> m_ignoredPatches; // list of optional patches we've indicated that we don't want.
ENDCLASS


#endif // DBUSERDEFS_H
