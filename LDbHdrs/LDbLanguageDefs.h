//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/lib/LDbHdrs/LDbLanguageDefs.h 3     5/10/04 11:59a Rbradford $
//
// DESCRIPTION:   LDbLanguageDefs.h has the interface for the language database.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef LDBLANGUAGEDEFS_H
#define LDBLANGUAGEDEFS_H
#pragma once

#include "HdrMacros.h"

class LArgSet;		// forward refs

DATACLASS(LDbLanguageDef)
	bool m_isAsian;				// is this an Asian language (thus needing Arial Unicode MS font?)
	const char *m_pArgString;	// arguments based in string
	USERPTR(LArgSet) m_pArgSet;	// use ptr to arg set
ENDVARS
	void BuildArgSet();			// build argument set from string
	void FreeArgSet();			// free argument set
ENDCLASS

#endif // LDBLANGUAGEDEFS_H
