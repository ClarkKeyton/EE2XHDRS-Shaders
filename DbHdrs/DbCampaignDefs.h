//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbCampaignDefs.h 12    2/14/05 4:08p Dsproul $
//
// DESCRIPTION:   Dataclasses used by the campaign .ddf files.
//
// AUTHOR:        Ben Morse
//
//===========================================================================

#ifndef DBCAMPAIGNDEFS_H
#define DBCAMPAIGNDEFS_H
#pragma once

#include "HdrMacros.h"

// @NOTE - these need to be in ascending order of difficulty
// @IMPORTANT - please keep this in sync with eMPDestroyPlyrAIDiff in DbFrontEndDefs.h
// (and the related SettingsUtils functions)
ENUM eDifficultySetting {
	kDifficultySetting_Easiest,
	kDifficultySetting_Easier,
	kDifficultySetting_Easy,
	kDifficultySetting_Normal,
	kDifficultySetting_Hard,
	kDifficultySetting_Hardest,
	kDifficultySetting_Num,
};

DATACLASS(DbCampaignInfo)
	DBINDEX(DbText)	m_name;					//the human-visible name of the campaign...
	LSizedArray<const char *> m_scenarios;	//the names of the scenarios that show up in this campaign.
	DBINDEX(DbText)	m_description;			// human-visible description of the campaign
	bool m_lockedScenarios;					// scenarios in this campaign must be progressed
											// through linearly as they are unlocked?
	bool m_useTimeline;						// should the scenarios be shown on the timeline?
											// otherwise will use a list.
ENDCLASS

#endif // DBCAMPAIGNDEFS_H
