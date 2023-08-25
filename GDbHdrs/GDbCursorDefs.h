//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbCursorDefs.h 2     12/06/04 9:08p Dsproul $
//
// DESCRIPTION:		dataclass definition for a mouse cursor
//
// AUTHOR:			Dan Sproul
//
//===========================================================================

#ifndef GDBCURSORDEFS_H
#define GDBCURSORDEFS_H
#pragma once


#include "HdrMacros.h"


DATACLASS(GDbCursorDef)
	DBINDEX(DbSprite)	m_sprite;	// sprite
	int16				m_hotX;		// hot x (pixels from left to hotspot)
	int16				m_hotY;		// hot y (pixels from top to hotspot)
ENDCLASS


#endif // GDBCURSORDEFS_H
