//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbForestGenDefs.h 3     9/20/05 12:24p Dsproul $
//
// DESCRIPTION:   Forest generation database classes and enums
//
// AUTHOR:        Kevin Wasserman
//
//===========================================================================

#ifndef DBFORESTGENDEFS_H
#define DBFORESTGENDEFS_H
#pragma once

#include "hdrmacros.h"
#include "LSizedArray.h"

class LRand;
class UnitType;

ENUM eForestation {
	kForestation_Light,
	kForestation_Medium,
	kForestation_Heavy,
	kNumForestationTypes,
	
	kForestation_Invalid = -1,
	kForestation_Random = -2,
};


//
// We one one of these for each forestation level and climate to select forest generation parameters to pass to the forest generation code.
//
DATACLASS(DbForestGenDef)
	float m_density;		// # trees pre square tile, roughly
	float m_scale;			// rough size of forest patches (tile units)
	float m_coverage;		// fraction of map to be covered by forest (0..1)
	float m_roughness;      // 0..1
	DBINDEX(DbForestBrush) m_brush;  // index into forest brush db
ENDCLASS

//
// We want one of these objects per climate to specify which forest brush to use for a (climate, forestation level) pair
//
DATACLASS(DbClimateForestGenDef)
	DBINDEX(DbForestGen) m_forestGen[ENUMVAL(eForestation,kNumForestationTypes)];	// index into forest gen db
ENDCLASS


#endif // DBFORESTGENDEFS_H
