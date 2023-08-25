//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbMusicDefs.h 4     5/20/04 12:11p Rbradford $
//
// DESCRIPTION:   DbMusicDefs.h holds music data definitions.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBMUSICDEFS_H
#define DBMUSICDEFS_H
#pragma once

#include "hdrmacros.h"
#include "DbPlayerDefs.h"
#include "DbTechTreeDefs.h"

// DbMusicCtrlLoopSetData is an array of filenames to be looped through

DATACLASS(DbMusicCtrlLoopSetDef)
	LSizedArray<const char *> m_filenames;	// set of sound filenames
ENDCLASS

// DbMusicCtrlGameData is the data used by the in-game music AI

DATACLASS(DbMusicCtrlRegionSet)
	enum eCivilizationRegion m_region;		// region these pieces belong to
	LSizedArray<const char *> m_filenames;	// music theme filenames
ENDCLASS

DATACLASS(DbMusicCtrlEpochSet)
	enum eTechTreeEpoch m_epochFirst;		// first epoch in which this music can play
	enum eTechTreeEpoch m_epochLast;		// last epoch in which this music can play
	LSizedArray<const char *> m_filenames;	// music theme filenames
ENDCLASS

DATACLASS(DbMusicCtrlGameAmbientDef)
	LSizedArray<DC(DbMusicCtrlRegionSet)*> m_regionSets;	// sets of music based on region
	LSizedArray<DC(DbMusicCtrlEpochSet)*> m_epochSets;	// sets of music based on epoch range
	float m_fracSilentPieces;				// fraction of time to play silence
	float m_timeSilenceLow;					// low end of random time for silence
	float m_timeSilenceHigh;				// high end of random time for silence
	int m_numLoopsLow;						// low end of random num of times to play each loop
	int m_numLoopsHigh;						// high end of random num of times to play each loop
ENDCLASS

#endif // DBMUSICDEFS_H
