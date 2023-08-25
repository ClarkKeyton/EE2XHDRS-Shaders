//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/lib/LDbHdrs/LDbColorDefs.h 2     11/19/03 10:36a Rbradford $
//
// DESCRIPTION:   LDbColorDefs.h has the definitions for the color database.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef LDBCOLORDEFS_H
#define LDBCOLORDEFS_H
#pragma once

#include "HdrMacros.h"
#include "LRGBA.h"
#include "NiColor.h"

DATACLASS(LDbColorDef)
	LRGBA m_color;			// color in LRGBA format
	USER float m_floats[4];	// this is really an NiColorA, but the parser is too lame
ENDVARS

	// GetNiColor from this record
	void GetNiColor(NiColor *out_pNiColor)
	{
		*out_pNiColor = *(NiColor *) m_floats;
	}

	// GetNiColorA from this record
	void GetNiColorA(NiColorA *out_pNiColor)
	{
		*out_pNiColor = *(NiColorA *) m_floats;
	}
ENDCLASS

#endif // LDBCOLORDEFS_H
