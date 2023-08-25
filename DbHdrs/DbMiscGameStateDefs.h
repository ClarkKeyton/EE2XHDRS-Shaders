//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbMiscGameStateDefs.h 11    10/04/05 12:48p Dsproul $
//
// DESCRIPTION:	DbMiscGameStateDefs.h defines dataclass for some game state that
//				must be saved from game to game
//
// AUTHOR:		Jason Dunlop
//
//===========================================================================

#ifndef DBMISCGAMESTATEDEFS_H
#define DBMISCGAMESTATEDEFS_H
#pragma once

#include "hdrmacros.h"

ENUM eDifficultyMode {
	kDifficultyMode_notChosen = -1,
	kDifficultyMode_Easy,
	kDifficultyMode_Medium,
	kDifficultyMode_Hard,
};

//
//	IMPORTANT NOTE:  if you change this data class, you must also update AudioSettings.cpp:
//						MiscGameState::LoadSettings()
//						MiscGameState::SaveSettings()
//	
DATACLASS(DbMiscGameStateDef)
	// @OBSOLETE
	int		m_lastUserLoggedIn;

	// now we do last user by DBindex
	DBINDEX(DbUser) m_lastUser;
	
	// these are really developer-only, but ifdef'ing them out would cause parse
	// errors on load when using mixed builds...
	char	*m_lastScenarioLoaded;			// the most recently loaded scenario (filename)
	int		 m_lastScenarioLoadedDbIndex;	// the most recently loaded scenario (db index)
											// @NOTE done as int and not DBINDEX to fix a bug
	char	*m_lastSavegameLoaded;			// the most recently loaded savegame
	
	enum eDifficultyMode m_eDiffModeSelection;	// user's current difficulty mode
	
	bool	m_bSuppressFirewallWarning;		// show user firewall warning?
	
	bool	m_bSuppressESRBWarning;			// show ESRB warning?
	
	bool	m_bSuppressSlowComputerWarning;	// warn the user about TGRTSE! sometimes not being insanely fast?
	
	// When starting a QS game and choosing your forces, should the player be
	// asked to create a starting force?
	bool	m_bSuppressCreateQSOption;		
	
	bool	m_bSuppressEditorNotSupportedWarning; // Warn the user that our Map Editor might DESTROY THE UNIVERSE, and it's not our fault if it does.
	
	bool	m_bSuppressAskAboutProfanityFilter;	// ask if the user wants to turn on the chat profanity filter?
ENDCLASS


#endif // DBMISCGAMESTATEDEFS_H
