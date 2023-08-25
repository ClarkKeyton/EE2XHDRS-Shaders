//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbAudioSettingsDefs.h 10    8/08/05 4:46p Mcorthell $
//
// DESCRIPTION:   DbAudioSettingsDefs.h defines the dataclass for audio settings.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBAUDIOSETTINGSDEFS_H
#define DBAUDIOSETTINGSDEFS_H
#pragma once

#include "hdrmacros.h"

//
//	IMPORTANT NOTE:  if you change this data class, you must also update AudioSettings.cpp:
//						AudioSettings::LoadSettings()
//						AudioSettings::SaveSettings()
//					 

DATACLASS(DbAudioSettingsDef)
	bool m_musicOn;			// music on or off?
	bool m_ambientOn;		// ambient on or off?
	float m_musicVolume;	// music volume 0 - 1
	float m_soundVolume;	// sound volume 0 - 1

	// @EE2X @MRC
	// EAX enabled or not
	bool m_bEAXEnabled;
	
	// @EE2X @MRC
	// Voice chat enabled or not
	bool m_bVoiceChatEnabled;
	// Whether automute is enabled
	bool m_bVChatAutoMuteEnabled;
	// Voice chat volume and gain. 0-1
	float m_voiceChatVolume;
	float m_voiceChatGain;

	// optional directory for user-specified music
	bool  m_EnableUserMusic;
	bool  m_UserMusicPlayOnStartup;
	bool  m_UserMusicChat;
	char *m_UserMusicDirectory;
ENDCLASS


#endif // DBAUDIOSETTINGSDEFS_H
