//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/lib/LDbHdrs/LDbTextDefs.h 3     1/07/05 5:46p Rbradford $
//
// DESCRIPTION:   LDbTextDefs.h has the defs for the text database.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef LDBTEXTDEFS_H
#define LDBTEXTDEFS_H
#pragma once

#include "HdrMacros.h"

DATACLASS(LDbTextDef)
	const char *m_text;		// ptr to text string
ENDCLASS

#endif // LDBTEXTDEFS_H
