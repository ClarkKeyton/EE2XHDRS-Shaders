//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbMovementDefs.h 4     6/02/04 4:37p Xkan $
//
// DESCRIPTION:	DbMovementDef.h describes the layout of rows in the
//				movement table.
//
// AUTHOR:      Rex E. Bradford
//
//===========================================================================

#ifndef DBMOVEMENTDEFS_H
#define DBMOVEMENTDEFS_H
#pragma once

#include "DbTerrainDefs.h"	// to get enum for num terrain move types

DATACLASS(DbMovementDef)
	// We basically just have an array of numbers, each elem is a terrain move type
	// The value 100 means "normal" cost, 0 means impassable
	int16 m_speed[ENUMVAL(eMovementSpeedType,kNumMovementSpeedType)];
ENDCLASS

#endif // DBMOVEMENTDEFS_H
