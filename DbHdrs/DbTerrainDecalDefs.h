//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbTerrainDecalDefs.h 2     1/16/04 4:22p Kwasserman $
//
// DESCRIPTION:   
//
// AUTHOR:        Kevin Wasserman
//
//===========================================================================

#ifndef DBTERRAINDECALDEFS_H
#define DBTERRAINDECALDEFS_H
#pragma once

#include "HdrMacros.h"

DATACLASS(DbTerrainDecalInfo)
	DBINDEX(DbSprite) m_spriteIndex;
	float m_width;
	float m_height;
	float m_duration;		// lifetime for decal before fade start?
	float m_fadeDuration;	// how long does it take to fade out?
ENDCLASS

#endif // DBTERRAINDECAL_H
