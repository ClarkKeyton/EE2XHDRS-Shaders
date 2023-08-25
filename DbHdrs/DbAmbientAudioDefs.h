//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbAmbientAudioDefs.h 4     3/25/04 6:01p Rbradford $
//
// DESCRIPTION:   DbAmbientAudioDefs.h has dataclasses for the ambient
//				  audio system.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBAMBIENTAUDIODEFS_H
#define DBAMBIENTAUDIODEFS_H
#pragma once

#include "HdrMacros.h"

enum eWeatherState;			// forward refs

//	--------------------------------------------------------------------
//		DATACLASSES TO DESCRIBE INDIVIDUAL SOUNDS INCLUDED IN SOUND SETS
//	--------------------------------------------------------------------

// Flags to be applied to individual sound records to determine if they can be
// used in the current context or not.  If more than one flag is specified in
// a given sound, then all these context bits must be set for the sound to be
// selectable.
FLAGS(kAmbientSoundFlag)
	const uint32 kAmbientSoundFlag_None = 0x0000;
	const uint32 kAmbientSoundFlag_LowWind = 0x0001;	// play this in low wind only
	const uint32 kAmbientSoundFlag_HighWind = 0x0002;	// play this in high wind only
	// Remaining bits reserved for future expansion
ENDFLAGS

// All ambient sound records have this as a base
DATACLASS(DbAmbientSound)
	DBINDEX(DbSound) m_sound;	// index into sound database
	int m_priority;				// relative priority (1 = min, scaled off lowest)
	FLAGS(kAmbientSoundFlag) uint32 m_context;	// only play if all the bits in this mask are set
ENDCLASS

//	-------------------------------------------------------------------
//		SOUND SETS
//	-------------------------------------------------------------------

// Here is a soundset, which gives the set of looping and one-shot sounds to
// be played under a given condition.
DATACLASS(DbAmbientSoundSet)
	LSizedArray<DC(DbAmbientSound)*> m_loopingSounds;	// array of looping sounds (one playing at a time)
	LSizedArray<DC(DbAmbientSound)*> m_sounds;			// array of one-shot sounds
	float m_oneShotFreq;				// overall frequency expressed as one-shots per minute
	float m_cutoffPriority;				// minimum priority (0 to 1.0) at which soundset is activated
	float m_minVolume;					// volume to play sounds at when at cutoff priority
										// (volume rises to 1.0 at max priority of 1.0)
ENDCLASS

// Here is a "weather sound set" for a given weather condition
DATACLASS_INHERIT(DbAmbientWeatherSoundSet, DbAmbientSoundSet)
	enum eWeatherState m_weather;		// which weather
ENDCLASS

// This is the master sound set table for a given climate (each climate
// has a dbindex to one of these guys)
DATACLASS(DbAmbientMasterSoundSet)
	LSizedArray<DBINDEX(DbAmbientAudio)> m_weatherSoundSets; // sound sets to use in different weathers
	DBINDEX(DbAmbientAudio) m_landSoundSet;		// sound set to use over basic land areas
	DBINDEX(DbAmbientAudio) m_waterSoundSet;	// sound set to use over water
	DBINDEX(DbAmbientAudio) m_forestSoundSet;	// sound set to use over forests
ENDCLASS

#endif // DBAMBIENTAUDIODEFS_H
