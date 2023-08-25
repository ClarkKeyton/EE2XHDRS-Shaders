//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbSoundDefs.h 9     5/23/05 3:39p Mcorthell $
//
// DESCRIPTION:	DbSound.h contains database header info for the sound system.
//
// AUTHOR:		Rex Bradford
//
//===========================================================================

#ifndef DBSOUNDDEFS_H
#define DBSOUNDDEFS_H
#pragma once

#include "hdrmacros.h"

class LSoundData;		// forward ref

DATACLASS(DbSoundInfo)
	char *m_filename;			// sound filename
	float m_volume;				// base volume
	bool m_loop;				// looping?
	int m_maxInstances;			// max number of instances of this sound
	float m_pitchVariation;		// variation to introduce into playback
	// @EE2X @MRC
	// For EAX, each sound can specify the "dry" and "wet" components of the sound.
	// Dry is the amount of unmodified sound, and wet is the sound after reverb is applied.
	// Both range from 0 to 1
	float m_amountDry;
	float m_amountWet;


	USERPTR(LSoundData) m_pSoundData;	// used by sound manager to hold data entry ptr
	USER int m_currInstances;	// current number of instances of this sound
	USER int m_instancesThisUpdate; // the number of instances for this update
ENDCLASS


#endif // DBSOUNDDEFS_H
