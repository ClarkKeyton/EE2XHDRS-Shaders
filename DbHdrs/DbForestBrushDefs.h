//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbForestBrushDefs.h 4     10/03/03 10:31a Bmorse $
//
// DESCRIPTION:   
//
// AUTHOR:        Ben Morse
//
//===========================================================================

#ifndef DBFORESTBRUSHDEFS_H
#define DBFORESTBRUSHDEFS_H
#pragma once

#include "hdrmacros.h"
#include "LSizedArray.h"

class LRand;
class UnitType;

DATACLASS(DbForestTreeWeightPair)
	DBINDEX(DbUnit) tree;
	int weight;
ENDCLASS

DATACLASS(DbForestBrushDef)
	//The list of tree/weight pairs that this brush contains.
	LSizedArray<DC(DbForestTreeWeightPair)*> trees;

	//the sum of all the weights, for generating a random number
	//later to pick a treetype.
	USER int m_normalizer;
ENDVARS

	//get the DBINDEX(DbUnit) of a random tree type, picked by
	//weight from this brush, using in_rand as yer PRNG.  Defined
	//in DbForestBrush.cpp.
	USER int GetRandomTreeType(LRand &in_rand);
ENDCLASS

//for a climate, an array of forest brushes that it's allowed to use.
DATACLASS(DbClimateForestDef)
	LSizedArray<DBINDEX(DbForestBrush)> brushes;
ENDCLASS


#endif // DBFORESTBRUSHDEFS_H
