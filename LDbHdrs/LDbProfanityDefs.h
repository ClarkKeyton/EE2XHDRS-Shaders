//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/lib/LDbHdrs/LDbProfanityDefs.h 2     9/19/05 6:00p Dsproul $
//
// DESCRIPTION:		
//
// AUTHOR:			Daniel Sproul
//
//===========================================================================

#ifndef LDBPROFANITYDEFS_H
#define LDBPROFANITYDEFS_H
#pragma once

#include "HdrMacros.h"


DATACLASS(LDbProfanityDef)

	// the terrible, horrible, profane word (utf8)
	char *m_text;

	// if true, word is filtered out only if it occurs as an entire word
	// (and not part of another word)
	// this way, "Passed" is okay but "Ass" is not
	bool m_bOnlyEntireWord;

ENDCLASS


// @HACK special DC so we can add CRC to the profanity DB
DATACLASS(LDbProfanityCRCDef)
	uint32 m_crc;
ENDCLASS


#endif // LDBPROFANITYDEFS_H
