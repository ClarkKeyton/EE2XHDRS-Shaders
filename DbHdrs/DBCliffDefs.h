//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DBCliffDefs.h 3     6/27/03 5:39p Kwasserman $
//
// DESCRIPTION:   
//
// AUTHOR:        Kevin Wasserman
//
//===========================================================================

#ifndef DBCLIFFDEFS_H
#define DBCLIFFDEFS_H
#pragma once

#include "HdrMacros.h"

DATACLASS(DbCliffInfo)
	char *m_filename;			// name of .nif
	int m_bottom;
	int m_right;
	int m_top;
	int m_left;
	int m_split;
ENDCLASS

#endif // DBCLIFFDEFS_H
